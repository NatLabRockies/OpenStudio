# Fails unless every given file has a valid Authenticode signature. Windows only.
# Exits 0 when all are Valid, 1 otherwise (including when no files are given).
param([Parameter(Mandatory = $true)][AllowEmptyCollection()][string[]]$Path)

if ($Path.Count -eq 0) { Write-Host "::error::No files to verify"; exit 1 }
$bad = 0
foreach ($p in $Path) {
  $sig = Get-AuthenticodeSignature -FilePath $p
  if ($sig.Status -ne 'Valid') {
    Write-Host "::error::Not validly signed ($($sig.Status)): $p"
    $bad++
  }
}
if ($bad) { Write-Host "::error::$bad of $($Path.Count) files are not validly signed"; exit 1 }
Write-Host "Verified Authenticode signatures on $($Path.Count) files"
exit 0
