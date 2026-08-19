# Instalar y actualizar cpp-printer con vcpkg

Esta es la forma recomendada de instalar `cpp-printer` cuando utilizas el fork de vcpkg de BlueNovaStudio.

Repositorio de vcpkg:

`https://github.com/BlueNovaStudio/vcpkg`

Repositorio de la biblioteca:

`https://github.com/BlueNovaStudio/cpp-printer`

## 1. Preparar vcpkg

Clona el fork de vcpkg si todavía no lo tienes:

```bash
git clone https://github.com/BlueNovaStudio/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
```

Si ya tienes el repositorio local, actualízalo antes de instalar o actualizar paquetes:

```bash
cd /ruta/a/vcpkg
git pull
```

Comprueba la versión:

```bash
./vcpkg version
```

## 2. Instalar cpp-printer

La instalación recomendada es simplemente:

```bash
./vcpkg install cpp-printer
```

En Linux x64 puedes especificar el triplet explícitamente:

```bash
./vcpkg install cpp-printer:x64-linux
```

Si el paquete ya está instalado y el port de vcpkg apunta a una versión nueva, vuelve a ejecutar el comando después de actualizar vcpkg:

```bash
git pull
./vcpkg install cpp-printer
```

vcpkg resolverá la versión definida por el baseline de tu árbol de ports.

## 3. Actualizar cpp-printer

Para recibir una nueva versión publicada en este fork:

```bash
cd /ruta/a/vcpkg
git pull
./vcpkg install cpp-printer
```

No es necesario descargar manualmente los headers ni ejecutar `install.sh`.

Si quieres reconstruir explícitamente el paquete desde cero:

```bash
./vcpkg remove cpp-printer
./vcpkg install cpp-printer
```

Normalmente no necesitas hacer esto: `git pull` seguido de `vcpkg install` es suficiente cuando el baseline ha cambiado.

## 4. Usarlo desde CMake

Configura tu proyecto para utilizar el toolchain de vcpkg.

Por ejemplo:

```bash
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE=/ruta/a/vcpkg/scripts/buildsystems/vcpkg.cmake
```

Después compila:

```bash
cmake --build build
```

En el código C++ puedes incluir la biblioteca normalmente:

```cpp
#include <cpp_printer/print.hpp>
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

## 5. Usarlo con manifest mode

En proyectos nuevos, también puedes crear un `vcpkg.json` en la raíz del proyecto consumidor:

```json
{
  "name": "mi-proyecto",
  "version-string": "0.1.0",
  "dependencies": [
    "cpp-printer"
  ]
}
```

Después configura CMake con el toolchain de vcpkg:

```bash
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE=/ruta/a/vcpkg/scripts/buildsystems/vcpkg.cmake
```

vcpkg instalará automáticamente `cpp-printer` como parte de la configuración del proyecto.

## 6. Importante: este tutorial usa el fork de BlueNovaStudio

El comando:

```bash
./vcpkg install cpp-printer
```

funciona con el árbol de ports que contiene el port `cpp-printer` de BlueNovaStudio.

Este fork ya contiene `cpp-printer` 1.0.2 y su baseline correspondiente.

Si utilizas otra instalación de vcpkg que no tenga este port, el comando puede indicar que no existe el paquete. En ese caso, utiliza este fork o un registro de vcpkg que contenga el port.

## 7. Publicar una nueva versión de cpp-printer

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

## 8. Flujo recomendado

Para un usuario que solo quiere instalar la biblioteca:

```bash
cd /ruta/a/vcpkg
git pull
./vcpkg install cpp-printer
```

Para desarrollar un proyecto CMake:

```bash
cd mi-proyecto
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE=/ruta/a/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

A partir de ahora, este flujo sustituye a la instalación manual como método principal.

## Requisitos

- C++17 o superior.
- CMake 3.20 o superior si utilizas la integración CMake del proyecto.
- Una instalación de vcpkg que contenga el port `cpp-printer` de BlueNovaStudio.
