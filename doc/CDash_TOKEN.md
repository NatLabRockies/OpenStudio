**CDash Token — How to obtain and use**

- **Purpose:** CDash requires an API token to accept test submissions. The CI workflow will try to submit test results to `https://my.cdash.org` for the `OpenStudio` project when a valid token is available.

- **Get a token:**
  - Sign in to your CDash instance at `https://my.cdash.org` with an account that has permission to submit to the `OpenStudio` project.
  - From the web UI, go to your user settings or API token page and create a new token. Copy it to a secure place.

- **Add token to GitHub Secrets:**
  - In the repository settings on GitHub, go to `Settings → Secrets and variables → Actions → New repository secret`.
  - Set the name to `CDASH_TOKEN` and paste the token value.
  - Save the secret.

- **Local testing:**
  - Copy the saved `Testing` tree into your build dir (example below assumes `OS-build-release-v2`):

```bash
cp -a logs/Testing-ubuntu/Testing-Ubuntu-2204/20251120-0816 OS-build-release-v2/Testing
```

  - Run a local submission (you will be prompted to paste the token):

```bash
read -s -p "CDASH token: " CDASH_SUBMIT_TOKEN; echo
export CDASH_SUBMIT_TOKEN
pushd OS-build-release-v2
ctest -D Experimental -DCDASH_SUBMIT_TOKEN="$CDASH_SUBMIT_TOKEN" > ../cdash_submission_output.txt 2>&1 || true
popd
tail -200 cdash_submission_output.txt
```

  - If you get an error like `{"status":1,"description":"Invalid Token"}`, verify you created the token for the correct CDash instance and project.

- **CI usage:**
  - The workflow file `/.github/workflows/test-ubuntu-only.yml` will attempt to submit results only when the `CDASH_TOKEN` secret exists or when you explicitly allow submission.
  - You can manually skip CDash submission when triggering the workflow using the `skip_cdash_submission` input set to `true`.

- **If you don't have a token:**
  - Use the `skip_cdash_submission` workflow input to avoid failed submission attempts during CI runs.

If you want, I can also add a small GitHub Actions job that validates the presence of `CDASH_TOKEN` and prints a helpful message when missing.
