[CmdletBinding()]
param(
    [string]$VcpkgRoot = "C:\vcpkg",
    [string]$Triplet = "x64-windows"
)

$ErrorActionPreference = "Stop"
$repository = if ($env:CPP_PRINTER_VCPKG_REPOSITORY) {
    $env:CPP_PRINTER_VCPKG_REPOSITORY
} else {
    "https://github.com/BlueNovaStudio/vcpkg.git"
}

if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
    throw "git es necesario para instalar vcpkg."
}

$gitDirectory = Join-Path $VcpkgRoot ".git"
if (Test-Path $gitDirectory) {
    Write-Host "Actualizando vcpkg en $VcpkgRoot..."
    & git -C $VcpkgRoot pull --ff-only
    if ($LASTEXITCODE -ne 0) { throw "No se pudo actualizar vcpkg." }
} elseif (Test-Path $VcpkgRoot) {
    throw "$VcpkgRoot existe, pero no es un checkout de vcpkg."
} else {
    Write-Host "Instalando vcpkg en $VcpkgRoot..."
    & git clone --depth 1 $repository $VcpkgRoot
    if ($LASTEXITCODE -ne 0) { throw "No se pudo clonar vcpkg." }
}

$vcpkg = Join-Path $VcpkgRoot "vcpkg.exe"
if (-not (Test-Path $vcpkg)) {
    & (Join-Path $VcpkgRoot "bootstrap-vcpkg.bat") -disableMetrics
    if ($LASTEXITCODE -ne 0) { throw "No se pudo preparar vcpkg." }
}

& $vcpkg install "cpp-printer:$Triplet"
if ($LASTEXITCODE -ne 0) { throw "No se pudo instalar cpp-printer." }

Write-Host ""
Write-Host "cpp-printer está disponible globalmente mediante vcpkg."
Write-Host "Toolchain CMake: $VcpkgRoot\scripts\buildsystems\vcpkg.cmake"
