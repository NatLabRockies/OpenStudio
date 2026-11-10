# Windows code signing

`full-build.yml` signs Windows binaries and the installer through a signing service outside GitHub.
This directory holds the CI side of it.

## How it works

1. The Windows job zips `bin/` and `Products/` and runs `Invoke-SigningWithRetry.ps1`, which calls `code-signing.js` (a bundled Node client).
2. The client uploads the zip to the `ci-code-signing` S3 bucket under `input/`. While a job is waiting, a root-level `<name>.lock` sits in the bucket.
3. The signing server polls the bucket every few seconds. It signs the zip's executables with the DigiCert EV certificate on a SafeNet eToken (using `osslsigncode`), then writes `output/<name>` and `output/<name>.status.json`. Signing the binaries takes about 3.5 minutes.
4. The client polls for the status file, downloads `<name>.signed.zip`, and the job runs `Assert-AuthenticodeSigned.ps1` over the result.
5. After `cpack`, the installer `.exe` goes through the same steps.

Signing runs only on develop, master, `v*` tags and runs with `publish_to_s3` set. Pull request runs skip it, so a green PR doesn't prove a signing change works.

The service keys jobs by zip file name. A reused name can pick up an earlier job's output, so `Invoke-SigningWithRetry.ps1` gives each run and attempt its own name. A 7-day lifecycle rule clears old `input/` and `output/` objects.

## Signing server

- **Hardware:** a QNAP NAS with the SafeNet eToken plugged in. It runs a Node service, likely under Container Station.
- **Owner / contact:** Alex Swindler
- **Location:** Off-site; ask Alex Swindler
- **Restart steps:** Contact Alex Swindler
- **Credentials:** it reads the bucket with the same AWS access key CI stores as `AWS_SIGNING_ACCESS_KEY` / `AWS_SIGNING_SECRET_KEY`. **Rotating that key breaks signing until the key on the NAS is updated too.**

## When signing fails

The job fails instead of publishing unsigned files. Common signs:

| Symptom | Likely cause |
|---|---|
| `No signed result from the signing service after 3 attempts`, and `.lock` files left at the bucket root | The server is down or not polling. Check the NAS, the service and the eToken. |
| `Not validly signed (...)` from `Assert-AuthenticodeSigned.ps1` | The service returned files without a valid signature, for example an expired or missing certificate, or a file it skipped. |
| `AWS_SIGNING_ACCESS_KEY secret not configured` | The repository secret is missing or the run can't see it. |

After fixing the server, re-run the failed jobs. Each attempt uses a new zip name, so leftovers from failed runs don't interfere.

## Certificate

DigiCert EV code-signing certificate, issued to "National Renewable Energy Laboratory", **expires 2027-10-14**. The key can't be exported from the eToken. Moving to a cloud HSM (for example Azure Key Vault Premium) means asking DigiCert to reissue the certificate to a new key. EV matters because some users require it. Azure Artifact Signing doesn't issue EV certificates.

## Tests

`Test-SigningWithRetry.ps1` and `Test-AssertAuthenticodeSigned.ps1` run in the `Test signing scripts` step of the `windows-build` job in `full-build.yml`, on every run including PRs.
