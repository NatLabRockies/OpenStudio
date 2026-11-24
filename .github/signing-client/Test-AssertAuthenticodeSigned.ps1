# Self-check for Assert-AuthenticodeSigned.ps1. Windows only. Run: pwsh -File Test-AssertAuthenticodeSigned.ps1
$ErrorActionPreference = 'Stop'
$script = Join-Path $PSScriptRoot 'Assert-AuthenticodeSigned.ps1'
$work = Join-Path ([IO.Path]::GetTempPath()) "authenticode-test-$PID"
New-Item -ItemType Directory -Path $work -Force | Out-Null

$signed = Join-Path $PSHOME 'pwsh.exe'  # Microsoft signs pwsh.exe with an embedded signature
$unsigned = Join-Path $work 'unsigned.exe'
Set-Content -Path $unsigned -Value 'not a signed binary'

function Test-Case($name, $paths, $expectedExit) {
  & $script -Path $paths *> $null
  if ($LASTEXITCODE -ne $expectedExit) { throw "$name : expected exit $expectedExit, got $LASTEXITCODE" }
  Write-Host "PASS $name"
}

try {
  Test-Case 'signed' @($signed) 0
  Test-Case 'unsigned' @($unsigned) 1
  Test-Case 'one-unsigned-among-signed' @($signed, $unsigned) 1
  Test-Case 'no-files' @() 1
} finally {
  Remove-Item $work -Recurse -Force
}
exit 0
