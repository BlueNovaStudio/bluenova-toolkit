#!/usr/bin/env bash
set -euo pipefail

REPOSITORY="${CPP_PRINTER_REPOSITORY:-https://github.com/BlueNovaStudio/cpp-printer.git}"
REF="${CPP_PRINTER_REF:-main}"

if [[ -n "${CPP_PRINTER_PREFIX:-}" ]]; then
    PREFIX="${CPP_PRINTER_PREFIX}"
elif [[ "${EUID}" -eq 0 ]]; then
    PREFIX="/usr/local"
else
    PREFIX="${HOME}/.local"
fi
TEMP_DIR="$(mktemp -d)"

cleanup()
{
    rm -rf "${TEMP_DIR}"
}
trap cleanup EXIT

command -v curl >/dev/null 2>&1 || {
    printf 'Error: curl es necesario para instalar cpp_printer.\n' >&2
    exit 1
}
command -v tar >/dev/null 2>&1 || {
    printf 'Error: tar es necesario para instalar cpp_printer.\n' >&2
    exit 1
}

ARCHIVE_URL="${REPOSITORY%.git}/archive/refs/heads/${REF}.tar.gz"
ARCHIVE="${TEMP_DIR}/cpp_printer.tar.gz"

printf 'Descargando cpp_printer (%s)...\n' "${REF}"
curl --fail --silent --show-error --location "${ARCHIVE_URL}" --output "${ARCHIVE}"
tar -xzf "${ARCHIVE}" -C "${TEMP_DIR}"
SOURCE_DIR="$(find "${TEMP_DIR}" -mindepth 1 -maxdepth 1 -type d | head -n 1)"

mkdir -p "${PREFIX}/include/cpp_printer"
cp -R "${SOURCE_DIR}/include/cpp_printer/." "${PREFIX}/include/cpp_printer/"

printf '\ncpp_printer instalado en %s\n' "${PREFIX}"
printf 'Incluye la biblioteca con: #include <cpp_printer/print.hpp>\n'
printf 'Compila con: -I%s/include\n' "${PREFIX}"
