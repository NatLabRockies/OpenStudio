# Code Signing Setup for OpenStudio Windows Builds

## Overview

The OpenStudio workflow uses **AWS Code Signing Service (Amazon Signer)** via a custom Node.js client. This document explains how to set up code signing for GitHub Actions.

## Current Setup (Identified)

✅ **Service:** AWS Code Signing (Amazon Signer)  
✅ **Client Location:** `C:/code-signing-client/code-signing.js` (on Jenkins)  
✅ **Authentication:** Uses `ACCESS_KEY` and `SECRET_KEY` from `.env` file  
✅ **Process:**
1. Compresses `.exe` files into a zip archive
2. Uses Node.js script to send archive to AWS signing service
3. Receives back a signed zip file
4. Extracts signed executables

## Migration to GitHub Actions

The signing client needs to be moved from the Jenkins server to your GitHub repository, and credentials need to be stored as GitHub secrets.

## GitHub Actions Setup (AWS Signer)

### Required Steps

**1. Copy Signing Client from Jenkins to Repository**

On your Jenkins Windows runner:
```powershell
cd C:\code-signing-client

# Remove sensitive files and dependencies
Remove-Item node_modules -Recurse -Force -ErrorAction SilentlyContinue
Remove-Item .env -Force -ErrorAction SilentlyContinue

# List files to verify
Get-ChildItem

# Create archive with essential files
Compress-Archive -Path *.js,package.json,package-lock.json -DestinationPath code-signing-client.zip
```

In your OpenStudio repository:
```bash
# Create directory for signing client
mkdir -p .github/signing-client

# Extract the zip contents here
# Should include: code-signing.js, package.json, package-lock.json

# Add to git
git add .github/signing-client/
git commit -m "Add AWS code signing client"
```

**2. Configure GitHub Secrets**

Go to: Repository Settings → Secrets and variables → Actions → New repository secret

Add these secrets from your Jenkins `.env` file:
- `AWS_SIGNING_ACCESS_KEY` - Value from `ACCESS_KEY` in `.env`
- `AWS_SIGNING_SECRET_KEY` - Value from `SECRET_KEY` in `.env`

**3. Workflow Implementation (Already Included)**

The `full-build-github-hosted.yml` workflow includes these steps:

```yaml
- name: Setup Node.js
  uses: actions/setup-node@v4
  with:
    node-version: '18'

- name: Install Signing Client Dependencies
  run: npm install
  working-directory: ./.github/signing-client

- name: Create .env file for Signing
  run: |
    echo "ACCESS_KEY=${{ secrets.AWS_SIGNING_ACCESS_KEY }}" > .env
    echo "SECRET_KEY=${{ secrets.AWS_SIGNING_SECRET_KEY }}" >> .env
  shell: pwsh
  working-directory: ./.github/signing-client

- name: Code sign installer
  shell: pwsh
  working-directory: ${{ github.workspace }}/${{ env.OPENSTUDIO_BUILD }}
  run: |
    # Sign build executables
    Compress-Archive -Path *.exe -DestinationPath build-${{ github.run_id }}.zip -Force
    node "${{ github.workspace }}/.github/signing-client/code-signing.js" "${{ github.workspace }}/${{ env.OPENSTUDIO_BUILD }}/build-${{ github.run_id }}.zip" -t 4800000
    Expand-Archive -Path build-${{ github.run_id }}.signed.zip -Force
    
    # Re-package with signed binaries
    cpack -B .
    
    # Sign installer
    Compress-Archive -Path OpenStudio*.exe -DestinationPath OpenStudio-Installer-${{ github.run_id }}.zip -Force
    node "${{ github.workspace }}/.github/signing-client/code-signing.js" "${{ github.workspace }}/${{ env.OPENSTUDIO_BUILD }}/OpenStudio-Installer-${{ github.run_id }}.zip" -t 4800000
    
    # Extract signed installer
    if (-not (Test-Path signed)) { New-Item -ItemType Directory -Path signed | Out-Null }
    Expand-Archive -Path OpenStudio-Installer-${{ github.run_id }}.signed.zip -DestinationPath signed -Force
```

### Alternative: Use SignPath.io (If Switching Services)

SignPath offers free code signing for open source projects.

**Steps:**
1. Sign up at https://signpath.io
2. Submit your project for OSS approval
3. Get your API token
4. Use their GitHub Action

**Workflow Implementation:**
```yaml
- name: Sign Windows executable
  uses: signpath/github-action-submit-signing-request@v0.3
  with:
    api-token: ${{ secrets.SIGNPATH_API_TOKEN }}
    organization-id: 'your-org-id'
    project-slug: 'OpenStudio'
    signing-policy-slug: 'release-signing'
    artifact-configuration-slug: 'windows-installer'
    input-artifact-path: 'OpenStudio-*.exe'
    output-artifact-path: 'signed/OpenStudio-*.exe'
```

### Option 3: Use Azure Code Signing (Trusted Signing)

**Requirements:**
- Azure subscription
- Azure Key Vault
- Code signing certificate stored in Key Vault

**Workflow Implementation:**
```yaml
- name: Azure Login
  uses: azure/login@v1
  with:
    creds: ${{ secrets.AZURE_CREDENTIALS }}

- name: Sign with Azure Code Signing
  uses: azure/trusted-signing-action@v0.3.16
  with:
    azure-tenant-id: ${{ secrets.AZURE_TENANT_ID }}
    azure-client-id: ${{ secrets.AZURE_CLIENT_ID }}
    azure-client-secret: ${{ secrets.AZURE_CLIENT_SECRET }}
    endpoint: https://xxx.codesigning.azure.net/
    code-signing-account-name: YourAccountName
    certificate-profile-name: YourProfileName
    files-folder: ${{ github.workspace }}/build
    files-folder-filter: exe
    file-digest: SHA256
    timestamp-rfc3161: http://timestamp.digicert.com
    timestamp-digest: SHA256
```

### Option 4: Use Windows SDK signtool with Certificate

If you have a traditional code signing certificate (not cloud-based):

**Workflow Implementation:**
```yaml
- name: Decode certificate
  shell: pwsh
  run: |
    $bytes = [Convert]::FromBase64String("${{ secrets.CERTIFICATE_BASE64 }}")
    [IO.File]::WriteAllBytes("${{ github.workspace }}/cert.pfx", $bytes)

- name: Sign executable
  shell: pwsh
  run: |
    $signtool = "C:\Program Files (x86)\Windows Kits\10\bin\10.0.22621.0\x64\signtool.exe"
    & $signtool sign /f "${{ github.workspace }}/cert.pfx" `
      /p "${{ secrets.CERTIFICATE_PASSWORD }}" `
      /tr http://timestamp.digicert.com `
      /td sha256 `
      /fd sha256 `
      "OpenStudio-*.exe"

- name: Cleanup
  if: always()
  shell: pwsh
  run: |
    Remove-Item "${{ github.workspace }}/cert.pfx" -ErrorAction SilentlyContinue
```

## Required GitHub Secrets

Configure these secrets in your repository (Settings → Secrets and variables → Actions):

### For AWS Code Signing (Current Setup):
- `AWS_SIGNING_ACCESS_KEY` - AWS Access Key ID for signing service (from Jenkins `.env` ACCESS_KEY)
- `AWS_SIGNING_SECRET_KEY` - AWS Secret Access Key for signing service (from Jenkins `.env` SECRET_KEY)

### Also Required (for S3 publishing):
- `AWS_ACCESS_KEY_ID` - For S3 artifact uploads
- `AWS_SECRET_ACCESS_KEY` - For S3 artifact uploads
- `AWS_REGION` - Optional, defaults to 'us-west-2'

### Alternative Services (if switching):
- **SignPath:** `SIGNPATH_API_TOKEN`
- **Azure:** `AZURE_TENANT_ID`, `AZURE_CLIENT_ID`, `AZURE_CLIENT_SECRET`
- **Traditional Certificate:** `CERTIFICATE_BASE64`, `CERTIFICATE_PASSWORD`

## Next Steps

1. ✅ **Service Identified:** AWS Code Signing (Amazon Signer)
2. **Copy signing client from Jenkins** to `.github/signing-client/` in repository
3. **Extract credentials from Jenkins `.env` file** (ACCESS_KEY and SECRET_KEY)
4. **Add GitHub secrets:** `AWS_SIGNING_ACCESS_KEY` and `AWS_SIGNING_SECRET_KEY`
5. **Test the signing process** in a test branch before deploying to production
6. **Verify signed executables** using `Get-AuthenticodeSignature`

## Testing Code Signing

After setting up the workflow, verify signatures with:

```powershell
# Download the signed installer from GitHub artifacts
# Then check if file is signed:
Get-AuthenticodeSignature "OpenStudio-*.exe" | Format-List

# Verify signature details
signtool verify /pa /v "OpenStudio-*.exe"

# Expected output should show:
# - Status: Valid
# - Signer: Your organization/certificate name
# - Timestamp: Valid timestamp
```

## Troubleshooting

### Common Issues:

1. **"code-signing-client not found" or "code-signing.js not found"**
   - Ensure `.github/signing-client/` directory exists in repository
   - Verify files were committed: `git ls-files .github/signing-client/`
   - Check file paths in workflow match actual location

2. **"ACCESS_KEY not found" or authentication failed**
   - Verify `AWS_SIGNING_ACCESS_KEY` secret is correctly set in GitHub
   - Verify `AWS_SIGNING_SECRET_KEY` secret is correctly set in GitHub
   - Check `.env` file is created properly in the workflow step
   - Verify credentials have not expired or been rotated

3. **"Timeout waiting for signed file"**
   - Increase timeout value (currently 4800000ms = 80 minutes)
   - Check AWS signing service status
   - Verify network connectivity from GitHub runners to AWS

4. **"npm install failed" in signing client**
   - Ensure `package.json` and `package-lock.json` are in repository
   - Check for Node.js version compatibility
   - Review npm install logs for specific dependency errors

5. **Signature verification fails**
   - Check that correct certificate is configured in AWS Signer
   - Verify certificate has not expired
   - Ensure proper signing profile is being used

## Additional Resources

- [GitHub Actions: Encrypted secrets](https://docs.github.com/en/actions/security-guides/encrypted-secrets)
- [Windows Code Signing Best Practices](https://docs.microsoft.com/en-us/windows-hardware/drivers/install/authenticode)
- [AWS Signer Documentation](https://docs.aws.amazon.com/signer/)
- [SignPath Documentation](https://signpath.io/documentation) - Alternative service
- [Azure Trusted Signing](https://learn.microsoft.com/en-us/azure/trusted-signing/) - Alternative service

## Summary

✅ **Service:** AWS Code Signing (Amazon Signer)  
✅ **Migration:** Copy signing client to `.github/signing-client/`  
✅ **Secrets:** `AWS_SIGNING_ACCESS_KEY` and `AWS_SIGNING_SECRET_KEY`  
✅ **Workflow:** Already configured in `full-build-github-hosted.yml`  
✅ **Testing:** Verify signatures with `Get-AuthenticodeSignature`