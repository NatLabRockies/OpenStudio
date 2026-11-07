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
$signedZip = [IO.Path]::ChangeExtension($ZipPath, ".signed$ext")

# The signing service occasionally reports a failed job (e.g. "write EPIPE"; root cause unconfirmed); retry before failing the build
for ($attempt = 1; $attempt -le $MaxAttempts; $attempt++) {
  # The client creates the signed zip before downloading and leaves it partial on failure
  if (Test-Path $signedZip) { Remove-Item $signedZip -Force }
  node $Client $ZipPath -t $TimeoutMs
  if ($LASTEXITCODE -eq 0 -and (Test-Path $signedZip)) { exit 0 }
  if ($attempt -lt $MaxAttempts) {
    Write-Host "::warning::Signing attempt $attempt of $MaxAttempts failed, retrying in ${RetryDelaySeconds}s"
    Start-Sleep -Seconds $RetryDelaySeconds
  }
}
exit 1
