# Sends a zip to the code-signing service through code-signing.js, retrying failed attempts.
# Exits 0 once <name>.signed<ext> has been downloaded next to the zip, 1 if every attempt failed.
param(
  [Parameter(Mandatory = $true)][string]$ZipPath,
  [string]$Client = (Join-Path $PSScriptRoot 'code-signing.js'),
  [int]$MaxAttempts = 3,
  [int]$RetryDelaySeconds = 60,
  [int]$TimeoutMs = 4800000
)

$ext = [IO.Path]::GetExtension($ZipPath)
$stem = $ZipPath.Substring(0, $ZipPath.Length - $ext.Length)
$signedZip = "$stem.signed$ext"
if (Test-Path $signedZip) { Remove-Item $signedZip -Force }

# The service keys jobs by file name and its output and status can land after the client has moved on,
# so a reused name picks up an older job's result. Give every run and attempt a name no earlier job used.
$runTag = if ($env:GITHUB_RUN_ID) { "$env:GITHUB_RUN_ID-$env:GITHUB_RUN_ATTEMPT" } else { 'local' }

for ($attempt = 1; $attempt -le $MaxAttempts; $attempt++) {
  $attemptZip = "$stem-$runTag-$attempt$ext"
  $attemptSigned = "$stem-$runTag-$attempt.signed$ext"
  Copy-Item $ZipPath $attemptZip -Force
  # The client creates the signed zip before downloading and leaves it partial on failure
  if (Test-Path $attemptSigned) { Remove-Item $attemptSigned -Force }
  node $Client $attemptZip -t $TimeoutMs
  $ok = $LASTEXITCODE -eq 0 -and (Test-Path $attemptSigned)
  Remove-Item $attemptZip -Force
  if ($ok) { Move-Item $attemptSigned $signedZip -Force; exit 0 }
  if (Test-Path $attemptSigned) { Remove-Item $attemptSigned -Force }
  if ($attempt -lt $MaxAttempts) {
    Write-Host "::warning::Signing attempt $attempt of $MaxAttempts failed, retrying in ${RetryDelaySeconds}s"
    Start-Sleep -Seconds $RetryDelaySeconds
  }
}
exit 1
