[CmdletBinding()]
param(
    [string]$Prefix = "C:\msys64\ucrt64"
)

$ErrorActionPreference = "Stop"
$repository = "https://github.com/BlueNovaStudio/cpp-printer/archive/refs/heads/main.zip"
$tempRoot = Join-Path ([System.IO.Path]::GetTempPath()) ("cpp-printer-" + [guid]::NewGuid())
$archive = Join-Path $tempRoot "cpp-printer.zip"
$extract = Join-Path $tempRoot "source"
$destination = Join-Path $Prefix "include\cpp_printer"

try {
    New-Item -ItemType Directory -Path $tempRoot -Force | Out-Null
    Invoke-WebRequest -Uri $repository -OutFile $archive
    Expand-Archive -Path $archive -DestinationPath $extract -Force

    $sourceRoot = Get-ChildItem -Path $extract -Directory | Select-Object -First 1
    $sourceInclude = Join-Path $sourceRoot.FullName "include\cpp_printer"

    if (-not (Test-Path $sourceInclude)) {
        throw "No se encontró la carpeta include\cpp_printer en la descarga."
    }

    New-Item -ItemType Directory -Path $destination -Force | Out-Null
    Copy-Item -Path (Join-Path $sourceInclude "*") -Destination $destination -Recurse -Force

    Write-Host "cpp_printer instalado en $destination"
    Write-Host "Compila con: g++ -std=c++17 main.cpp -o main.exe"
}
finally {
    if (Test-Path $tempRoot) {
        Remove-Item $tempRoot -Recurse -Force
    }
}
