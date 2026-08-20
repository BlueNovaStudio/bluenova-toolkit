# cpp_printer

Biblioteca **header-only** para imprimir contenedores STL de C++17 con formato
legible y colores ANSI. No requiere dependencias externas.

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
#include "tools/search.hpp"
#include "tools/stats.hpp"
#include "views/ascii.hpp"
#include "views/table.hpp"
#include "views/tree.hpp"
```

Ejemplos disponibles:

- `examples/test_cpp_printer/main.cpp`
- `examples/test_tools/main.cpp`
- `examples/test_views/main.cpp`

## Funciones

La API incluye:

- Secuenciales: `cout_array`, `cout_vector`, `cout_list` y `cout_deque`.
- Sets: `cout_set`, `cout_multiset` y `cout_unordered_set`.
- Maps: `cout_map`, `cout_multimap` y `cout_unordered_map`.
- Adaptadores: `cout_queue`, `cout_stack`, `cout_priority_queue` y `cout_pair`.
- Herramientas: `cout_stats`, `cout_search` y `cout_compare`.
- Vistas: `cout_ascii`, `cout_table` y `cout_tree`.

Todas se llaman como `cpp_printer::nombre(...)` y escriben en `std::cout`.

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
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
```

Ejecuta los tests:

```bash
ctest --test-dir build --output-on-failure
```

Compila solo la CLI:

```bash
cmake --build build --target cpp_printer
./build/cpp_printer
./build/cpp_printer helpme
```

La CLI `helpme` copia `docs/CPP_PRINTER.md` al directorio actual.

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

La guía detallada está en [docs/CPP_PRINTER.md](docs/CPP_PRINTER.md). El
proyecto se distribuye bajo la licencia incluida en [LICENSE](LICENSE).
