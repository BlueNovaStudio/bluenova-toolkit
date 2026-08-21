#!/usr/bin/env bash
set -euo pipefail

VCPKG_REPOSITORY="${CPP_PRINTER_VCPKG_REPOSITORY:-https://github.com/BlueNovaStudio/vcpkg.git}"
VCPKG_ROOT="${VCPKG_ROOT:-${HOME}/.local/vcpkg}"
TRIPLET="${VCPKG_DEFAULT_TRIPLET:-x64-linux}"

if ! command -v git >/dev/null 2>&1; then
    printf 'Error: git es necesario para instalar vcpkg.\n' >&2
    exit 1
fi

if [[ -d "${VCPKG_ROOT}/.git" ]]; then
    printf 'Actualizando vcpkg en %s...\n' "${VCPKG_ROOT}"
    git -C "${VCPKG_ROOT}" pull --ff-only
elif [[ -e "${VCPKG_ROOT}" ]]; then
    printf 'Error: %s existe, pero no es un checkout de vcpkg.\n' "${VCPKG_ROOT}" >&2
    exit 1
else
    printf 'Instalando vcpkg en %s...\n' "${VCPKG_ROOT}"
    git clone --depth 1 "${VCPKG_REPOSITORY}" "${VCPKG_ROOT}"
fi

VCPKG_BIN="${VCPKG_ROOT}/vcpkg"
if [[ ! -x "${VCPKG_BIN}" ]]; then
    "${VCPKG_ROOT}/bootstrap-vcpkg.sh" -disableMetrics
fi

"${VCPKG_BIN}" install "cpp-printer:${TRIPLET}"

printf '\ncpp-printer está disponible globalmente mediante vcpkg.\n'
printf 'Toolchain CMake: %s/scripts/buildsystems/vcpkg.cmake\n' "${VCPKG_ROOT}"
