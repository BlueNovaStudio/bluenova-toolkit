# Instalar y actualizar cpp-printer con vcpkg

Esta es la forma recomendada de instalar `cpp-printer` cuando utilizas el fork de vcpkg de BlueNovaStudio.

Repositorio de vcpkg:

`https://github.com/BlueNovaStudio/vcpkg`

Repositorio de la biblioteca:

`https://github.com/BlueNovaStudio/cpp-printer`

## 1. Instalación global automática

No clones `cpp-printer` dentro de un proyecto consumidor. Los scripts del
repositorio instalan el fork de vcpkg en una ubicación estable, descargan el
port publicado e instalan `cpp-printer`. Si vcpkg ya existe en esa ubicación,
lo actualizan con `git pull --ff-only` antes de instalar.

En Linux, el directorio predeterminado es `~/.local/vcpkg`:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/scripts/install-vcpkg.sh | bash
```

En Windows, el directorio predeterminado es `C:\vcpkg`:

```powershell
Set-ExecutionPolicy -Scope Process Bypass
irm https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/scripts/install-vcpkg.ps1 | iex
```

Ambas ubicaciones están fuera de los proyectos consumidores. Para actualizar la
biblioteca más adelante, repite el mismo comando.

## 2. Instalar cpp-printer

Después de ejecutar el script, la instalación equivalente es:

```bash
~/.local/vcpkg/vcpkg install cpp-printer
```

En Linux x64 puedes especificar el triplet explícitamente:

```bash
~/.local/vcpkg/vcpkg install cpp-printer:x64-linux
```

En Windows, el ejecutable instalado globalmente es `C:\vcpkg\vcpkg.exe` y el
triplet predeterminado es `x64-windows`:

```powershell
C:\vcpkg\vcpkg.exe install cpp-printer:x64-windows
```

vcpkg resolverá la versión definida por el baseline de tu árbol de ports.

## 3. Actualizar cpp-printer

Para recibir una nueva versión publicada en este fork:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/scripts/install-vcpkg.sh | bash
```

En Windows, repite el instalador de PowerShell:

```powershell
irm https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/scripts/install-vcpkg.ps1 | iex
```

No es necesario descargar manualmente los headers, clonar esta biblioteca ni
ejecutar `install.sh`.

Si quieres reconstruir explícitamente el paquete desde cero:

```bash
~/.local/vcpkg/vcpkg remove cpp-printer
~/.local/vcpkg/vcpkg install cpp-printer
```

Normalmente no necesitas hacerlo: el instalador actualiza el checkout global y
ejecuta `vcpkg install` con el baseline actualizado.

## 4. Usarlo desde CMake

Configura tu proyecto para utilizar el toolchain de vcpkg.

Por ejemplo:

```bash
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE="$HOME/.local/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

Después compila:

```bash
cmake --build build
```

En el código C++ puedes incluir la biblioteca normalmente:

```cpp
#include <cpp_printer.hpp>
```

El paquete exporta el target CMake:

```text
cpp_printer::cpp_printer
```

Por ejemplo:

```cmake
find_package(cpp_printer CONFIG REQUIRED)

target_link_libraries(mi_programa PRIVATE cpp_printer::cpp_printer)
```

En Windows, el toolchain global es:

```powershell
cmake -S . -B build -A x64 `
  -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
```

## 5. Importante: este tutorial usa el fork de BlueNovaStudio

El comando:

```bash
~/.local/vcpkg/vcpkg install cpp-printer
```

funciona con el árbol de ports que contiene el port `cpp-printer` de BlueNovaStudio.

Para publicar esta entrega, actualiza el port y su baseline a `cpp-printer`
**1.0.4**. La versión anterior publicada por el proyecto fue **1.0.3**.

Si utilizas otra instalación de vcpkg que no tenga este port, el comando puede indicar que no existe el paquete. En ese caso, utiliza este fork o un registro de vcpkg que contenga el port.

## 6. Publicar una nueva versión de cpp-printer

Cuando se publique una nueva versión de la biblioteca, el mantenimiento del port se realiza en el repositorio de vcpkg.

Después de actualizar el código de `cpp-printer`, desde el checkout de vcpkg se puede generar la nueva entrada de versión con:

```bash
./vcpkg x-add-version cpp-printer --overwrite-version
```

Comprueba los cambios:

```bash
git diff -- versions/c-/cpp-printer.json versions/baseline.json
```

Después prueba la instalación:

```bash
./vcpkg install cpp-printer
```

Si todo está correcto, haz commit y push de los archivos de versiones:

```bash
git add versions/c-/cpp-printer.json versions/baseline.json
git commit -m "Update cpp-printer to X.Y.Z"
git push origin master
```

Los usuarios podrán recibir la nueva versión después de actualizar su checkout de vcpkg:

```bash
git pull
./vcpkg install cpp-printer
```

## 7. Flujo recomendado

Para un usuario que solo quiere instalar la biblioteca:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/scripts/install-vcpkg.sh | bash
```

Para desarrollar un proyecto CMake:

```bash
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE="$HOME/.local/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build build
```

A partir de ahora, este flujo sustituye a la instalación manual como método principal.

## Requisitos

- C++17 o superior.
- CMake 3.20 o superior si utilizas la integración CMake del proyecto.
- Una instalación de vcpkg que contenga el port `cpp-printer` de BlueNovaStudio.
