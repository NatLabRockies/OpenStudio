# Self-check for Invoke-SigningWithRetry.ps1 using a fake signing client. Run: pwsh -File Test-SigningWithRetry.ps1
$ErrorActionPreference = 'Stop'
$script = Join-Path $PSScriptRoot 'Invoke-SigningWithRetry.ps1'
$work = Join-Path ([IO.Path]::GetTempPath()) "signing-retry-test-$PID"
New-Item -ItemType Directory -Path $work -Force | Out-Null

# Fake client: each call takes the next outcome from FAKE_PLAN (ok | partial | nofile) and logs it.
#   ok: writes the signed zip, exits 0; partial: writes a signed zip, exits 1; nofile: exits 0 without writing it
$fake = Join-Path $work 'fake-client.js'
Set-Content -Path $fake -Value @'
const fs = require('fs'), path = require('path');
const zip = process.argv[2], log = zip + '.calls';
const n = fs.existsSync(log) ? fs.readFileSync(log, 'utf8').length : 0;
fs.appendFileSync(log, 'x');
const outcome = process.env.FAKE_PLAN.split(',')[n];
const signed = path.join(path.dirname(zip), path.basename(zip, '.zip') + '.signed.zip');
if (outcome !== 'nofile') fs.writeFileSync(signed, outcome);
process.exit(outcome === 'partial' ? 1 : 0);
'@

function Test-Case($name, $plan, $expectedExit, $expectedCalls) {
  $zip = Join-Path $work "$name.zip"
  Set-Content -Path $zip -Value 'zip'
  Remove-Item "$zip.calls" -ErrorAction SilentlyContinue
  $env:FAKE_PLAN = $plan
  & $script -ZipPath $zip -Client $fake -RetryDelaySeconds 0 *> $null
  $exit = $LASTEXITCODE
  $calls = (Get-Content "$zip.calls" -Raw).Length
  if ($exit -ne $expectedExit -or $calls -ne $expectedCalls) {
    throw "$name : expected exit $expectedExit after $expectedCalls attempts, got exit $exit after $calls"
  }
  if ($exit -eq 0 -and (Get-Content (Join-Path $work "$name.signed.zip") -Raw).Trim() -ne 'ok') {
    throw "$name : signed zip is not from the successful attempt"
  }
  Write-Host "PASS $name"
}

try {
  Test-Case 'first-attempt' 'ok' 0 1
  Test-Case 'partial-then-ok' 'partial,ok' 0 2
  Test-Case 'exit0-without-file' 'nofile,ok' 0 2
  Test-Case 'all-fail' 'partial,partial,partial' 1 3
} finally {
  Remove-Item $work -Recurse -Force
}
