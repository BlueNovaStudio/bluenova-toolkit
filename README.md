# cpp_printer

Biblioteca **header-only** para imprimir contenedores habituales de la STL de C++ con un formato legible y colores inspirados en Dracula.

## Instalación recomendada: vcpkg

La forma recomendada de instalar y actualizar `cpp-printer` es mediante **vcpkg**.

Este proyecto mantiene un port de `cpp-printer` en el fork de vcpkg de BlueNovaStudio:

- https://github.com/BlueNovaStudio/vcpkg
- https://github.com/BlueNovaStudio/cpp-printer

### 1. Instalar vcpkg

Si todavía no tienes el fork de vcpkg:

```bash
git clone https://github.com/BlueNovaStudio/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
```

Si ya lo tienes instalado, actualízalo:

```bash
cd /ruta/a/vcpkg
git pull
```

### 2. Instalar cpp-printer

```bash
./vcpkg install cpp-printer
```

En Linux x64 puedes especificar el triplet:

```bash
./vcpkg install cpp-printer:x64-linux
```

Una vez instalado, puedes incluir la biblioteca directamente:

```cpp
#include <cpp_printer/print.hpp>
```

### 3. Actualizar cpp-printer

Cuando se publique una nueva versión en el port de vcpkg, actualiza primero tu checkout de vcpkg:

```bash
cd /ruta/a/vcpkg
git pull
./vcpkg install cpp-printer
```

No necesitas descargar manualmente los headers ni ejecutar `install.sh` para actualizar una instalación administrada por vcpkg.

## Uso rápido

```cpp
#include <cpp_printer/print.hpp>
#include <vector>

int main()
{
    std::vector<int> values = {1, 2, 3};
    cpp_printer::cout_vector("values", values);
    return 0;
}
```

La salida será similar a:

```text
values = {1, 2, 3}
```

Declarar un contenedor no lo imprime automáticamente; debes llamar a una de las funciones de `cpp_printer`.

## Integración con CMake

El proyecto exporta el target CMake `cpp_printer::cpp_printer`.

Si tu proyecto utiliza vcpkg en modo manifest, crea un `vcpkg.json` en la raíz del proyecto consumidor:

```json
{
  "name": "mi-proyecto",
  "version-string": "0.1.0",
  "dependencies": [
    "cpp-printer"
  ]
}
```

Configura CMake usando el toolchain de vcpkg:

```bash
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE=/ruta/a/vcpkg/scripts/buildsystems/vcpkg.cmake
```

Y en `CMakeLists.txt`:

```cmake
find_package(cpp_printer CONFIG REQUIRED)

target_link_libraries(mi_programa PRIVATE cpp_printer::cpp_printer)
```

Después compila normalmente:

```bash
cmake --build build
```

Consulta el tutorial completo de vcpkg en [`docs/VCPKG.md`](docs/VCPKG.md).

## Instalación manual

vcpkg es el método recomendado, pero la instalación manual sigue disponible para usuarios que no utilicen vcpkg.

### Linux / WSL

Para instalar los headers en `/usr/local/include`:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh | sudo bash
```

Después:

```bash
g++ -std=c++17 main.cpp -o main
./main
```

También puedes instalar para tu usuario:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh | bash
```

### Windows / MSYS2 UCRT64

Desde PowerShell:

```powershell
Set-ExecutionPolicy -Scope Process Bypass
irm https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.ps1 | iex
```

Después abre **MSYS2 UCRT64** y compila:

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

Si utilizas una instalación manual en otra carpeta, indica la ruta de los headers mediante `-I`.

## Requisitos

- C++17 o superior.
- CMake 3.20 o superior para usar la configuración CMake.

## Funciones

La biblioteca incluye impresores para:

- Secuenciales: `array`, `vector`, `forward_list` y `deque`.
- Sets: `set`, `multiset` y `unordered_set`.
- Maps: `map`, `multimap` y `unordered_map`.
- Adaptadores: `queue`, `stack`, `priority_queue` y `pair`.

Todas las funciones pertenecen al namespace `cpp_printer` y escriben en `std::cout`.

## CLI

El ejecutable muestra un mensaje inicial sin argumentos y permite copiar la documentación al directorio actual:

```bash
cpp_printer helpme
```

Si estás dentro del árbol del proyecto y has compilado con CMake:

```bash
./build/cpp_printer
./build/cpp_printer helpme
```

## Desarrollo

Para configurar y compilar el proyecto:

```bash
cmake -S . -B build -DBUILD_TESTING=OFF
cmake --build build --target cpp_printer
```

## Nota

Estas funciones son atajos para ahorrar tiempo. No sustituyen el aprendizaje de la STL ni la comprensión de las estructuras de datos.

**Automatiza la tarea, no el conocimiento.**
