# Guía de cpp_printer

**Versión documentada: v1.0.4** (anterior: v1.0.3).

Los cambios de esta versión están en el [registro de cambios](CHANGELOG.md).

## Modelo de inclusión

`cpp_printer` es una biblioteca header-only. Desde un proyecto consumidor,
añade el directorio `include` del proyecto a la línea de compilación:

```bash
c++ -std=c++17 -I/ruta/a/cpp-printer/include main.cpp -o app
```

Puedes incluir todos los módulos con la cabecera pública:

```cpp
#include <cpp_printer.hpp>
```

O incluir un header concreto:

```cpp
#include "cpp_printer/sequential/vector.hpp"
```

Los headers públicos usan el namespace `cpp_printer`, incluidos los módulos de
`tools` y `views`.

## Impresores STL

```cpp
#include <cpp_printer.hpp>
#include <map>
#include <string>
#include <vector>

int main()
{
    std::vector<int> values{1, 2, 3};
    std::map<std::string, int> scores{{"total", 42}};

    cpp_printer::cout_vector("values", values);
    cpp_printer::cout_map("scores", scores);
}
```

Están disponibles `array`, `vector`, `list`, `deque`, `set`, `multiset`,
`unordered_set`, `map`, `multimap`, `unordered_map`, `queue`, `stack`,
`priority_queue` y `pair`.

## Herramientas

```cpp
#include "tools/compare.hpp"
#include "tools/diff.hpp"
#include "tools/search.hpp"
#include "tools/stats.hpp"

cpp_printer::cout_compare("left", left, "right", right);
cpp_printer::cout_diff("left", left, "right", right);
cpp_printer::cout_search("values", values, 2);
cpp_printer::cout_stats("values", values);
```

`cout_compare` compara contenedores e informa las diferencias. `cout_diff`
presenta las diferencias como adiciones y eliminaciones. Para mapas y sets se
comparan las claves o valores en orden; para contenedores unordered se crea una
vista ordenada cuando es necesaria para obtener una salida estable. `cout_search`
resalta coincidencias y sus índices. `cout_stats` muestra tamaño, suma,
promedio, mínimo y máximo para elementos aritméticos.

## Vistas

```cpp
#include "views/ascii.hpp"
#include "views/table.hpp"
#include "views/tree.hpp"

cpp_printer::cout_ascii("values", values);
cpp_printer::cout_table("matrix", matrix);
cpp_printer::cout_tree("tree", values);
```

`cout_table` recibe una estructura bidimensional, como
`std::vector<std::vector<int>>`. `cout_ascii` recibe secuencias numéricas
(`vector`, `list`, `deque` o `array`) y `cout_tree` recibe un contenedor
iterable. En v1.0.4, `cout_custom_ascii` aplica los límites mínimo y máximo
indicados al normalizar la escala.

## Compilación del repositorio

Para compilar el CLI y los tests:

```bash
cmake -S . -B build -DCPP_PRINTER_BUILD_TESTS=ON -DCPP_PRINTER_BUILD_EXAMPLES=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

Para compilar solo el CLI:

```bash
cmake --build build --target cpp_printer
./build/cpp_printer
./build/cpp_printer helpme
```

Para compilar un ejemplo aislado no uses el build completo:

```bash
c++ -std=c++17 -Iinclude examples/test_tools/main.cpp -o /tmp/tools_example
/tmp/tools_example
```

La tarea **Build current C++ file** de VS Code compila el archivo `.cpp`
activo usando `-I${workspaceFolder}/include`.

Para inspeccionar la salida de cada test, usa:

```bash
ctest --test-dir build -V
```

## Colores y terminales

La salida usa secuencias ANSI truecolor. La comparación de tests elimina esas
secuencias antes de verificar el texto, por lo que los tests también funcionan
en terminales sin soporte de color.

## Mantenimiento

La estructura, los headers internos compartidos y las reglas para extender la
biblioteca están en [README.md](README.md) dentro de este directorio.
