# cpp_printer

Biblioteca **header-only** para imprimir contenedores STL de C++17 con formato
legible y colores ANSI. No requiere dependencias externas.

> Versión actual: **v1.0.4**. La versión anterior publicada fue **v1.0.3**.
> Consulta el [registro de cambios](docs/CHANGELOG.md) y la
> [guía de arquitectura](docs/README.md) para el detalle de esta versión.

## Requisitos

- Compilador C++17 o superior.
- CMake 3.20 o superior para el build del proyecto.
- Una terminal compatible con UTF-8 y colores ANSI para ver la salida completa.

## Uso rápido

Incluye el agregador completo:

```cpp
#include "all.hpp"
#include <vector>

int main()
{
    std::vector<int> values{1, 2, 3};
    cpp_printer::cout_vector("values", values);
}
```

Compila el ejemplo incluido desde la raíz del repositorio:

```bash
g++ -std=c++17 -Iinclude examples/test_cpp_printer/main.cpp -o /tmp/cpp_printer_example
/tmp/cpp_printer_example
```

Si tu archivo está en otra carpeta, usa la misma opción `-Iinclude`:

```bash
g++ -std=c++17 -Iinclude examples/test_cpp_printer/main.cpp -o /tmp/cpp_printer_example
/tmp/cpp_printer_example
```

También puedes incluir solo el módulo necesario, por ejemplo:

```cpp
#include "cpp_printer/sequential/vector.hpp"
```

Las funciones de `tools` y `views` también pertenecen al namespace
`cpp_printer`:

```cpp
#include "tools/compare.hpp"
#include "tools/diff.hpp"
#include "tools/search.hpp"
#include "tools/stats.hpp"
#include "views/ascii.hpp"
#include "views/table.hpp"
#include "views/tree.hpp"
```

Ejemplos disponibles:

- `examples/test_cpp_printer/main.cpp`
- `examples/test_tools/test_stats.cpp`, `test_compare.cpp`, `test_diff.cpp` y
  `test_search.cpp`
- `examples/test_views/test_ascii.cpp`, `test_table.cpp` y `test_tree.cpp`

## Funciones

La API incluye:

- Secuenciales: `cout_array`, `cout_vector`, `cout_list` y `cout_deque`.
- Sets: `cout_set`, `cout_multiset` y `cout_unordered_set`.
- Maps: `cout_map`, `cout_multimap` y `cout_unordered_map`.
- Adaptadores: `cout_queue`, `cout_stack`, `cout_priority_queue` y `cout_pair`.
- Herramientas: `cout_stats`, `cout_search`, `cout_compare` y `cout_diff`.
- Vistas: `cout_ascii`, `cout_table` y `cout_tree`.

Todas se llaman como `cpp_printer::nombre(...)` y escriben en `std::cout`.

## Features

### `cout_stats()`

Muestra el tamaño de un contenedor y, cuando sus elementos son numéricos, suma,
promedio, mínimo y máximo. También admite mapas y sets.

### `cout_compare()`

Compara dos estructuras e informa valores distintos, elementos faltantes y
claves con cambios. Mantiene el orden natural de mapas y sets; para
contenedores unordered produce una comparación ordenada para que la salida sea
estable.

### `cout_diff()`

Presenta diferencias entre dos contenedores como eliminaciones (`-`) y
adiciones (`+`). Es útil para inspeccionar cambios de secuencias, sets y mapas.

### `cout_search()`

Busca un valor, resalta todas las coincidencias y lista los índices donde fue
encontrado.

### `cout_table()`

Imprime matrices y otras estructuras bidimensionales como una tabla ASCII. Las
filas pueden tener longitudes diferentes y las columnas se ajustan al valor más
ancho.

### `cout_tree()`

Representa contenedores y mapas anidados como un árbol. Es especialmente útil
para visualizar datos jerárquicos.

### `cout_ascii()`

Genera gráficos de barras horizontales para secuencias numéricas. Incluye
`cout_hbar()`, `cout_stacked_bar()` y `cout_custom_ascii()` para configuración
de ancho, presentación y escala.

### Impresores de contenedores STL

`cout_vector()`, `cout_list()`, `cout_deque()`, `cout_array()`,
`cout_set()`, `cout_multiset()`, `cout_unordered_set()`, `cout_map()`,
`cout_multimap()`, `cout_unordered_map()`, `cout_queue()`, `cout_stack()`,
`cout_priority_queue()` y `cout_pair()` imprimen sus tipos correspondientes
con formato y color consistentes.

## Compilar solo un archivo

El proyecto contiene varios targets de CMake, pero CMake no compila archivos de
ejemplo automáticamente. Para compilar un archivo concreto:

```bash
g++ -std=c++17 -Iinclude ruta/al/main.cpp -o app
./app
```

En VS Code, abre el archivo `.cpp` que quieras ejecutar y usa la tarea
**Build current C++ file** (`Ctrl+Shift+B`). La tarea está en
`.vscode/tasks.json` y compila únicamente `${file}`.

## CMake, CLI y tests

Configura y compila el proyecto completo:

```bash
cmake -S . -B build -DCPP_PRINTER_BUILD_TESTS=ON -DCPP_PRINTER_BUILD_EXAMPLES=ON
cmake --build build --parallel
```

Ejecuta los tests:

```bash
ctest --test-dir build --output-on-failure
```

Para mostrar la salida de cada ejecutable de test:

```bash
ctest --test-dir build -V
```

Compila solo la CLI:

```bash
cmake --build build --target cpp_printer
./build/cpp_printer
./build/cpp_printer helpme
```

La CLI `helpme` copia `docs/CPP_PRINTER.md` al directorio actual.

## Integración continua

El workflow [CI](.github/workflows/ci.yml) se ejecuta en cada `push`, pull
request o ejecución manual. Compila con GCC y Clang en Linux y con MSVC en
Windows; después ejecuta CTest y todos los ejemplos.

## Instalación manual

En Linux o WSL, instalación para el usuario actual:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh | bash
g++ -std=c++17 -I"$HOME/.local/include" main.cpp -o main
```

Para instalar en `/usr/local/include` se requieren permisos administrativos:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh | sudo bash
g++ -std=c++17 main.cpp -o main
```

En Windows con MSYS2 UCRT64, ejecuta el instalador desde PowerShell y compila
desde la terminal MSYS2:

```powershell
Set-ExecutionPolicy -Scope Process Bypass
irm https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.ps1 | iex
```

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

## vcpkg

El port de vcpkg se mantiene en el fork de BlueNovaStudio:

- https://github.com/BlueNovaStudio/vcpkg
- https://github.com/BlueNovaStudio/cpp-printer

Consulta [docs/VCPKG.md](docs/VCPKG.md) para la integración con CMake.

## Documentación

La guía de uso está en [docs/CPP_PRINTER.md](docs/CPP_PRINTER.md). Consulta
[docs/README.md](docs/README.md) para la estructura del proyecto y el papel de
`include/`. El proyecto se distribuye bajo la licencia incluida en
[LICENSE](LICENSE).
