# cpp_printer

Biblioteca header-only para imprimir contenedores habituales de la STL de C++ con
un formato legible y colores inspirados en Dracula.

## Requisitos

- C++17 o superior.
- CMake 3.20 o superior para usar la configuración incluida.

## Uso rápido

```cpp
#include "cpp_printer/print.hpp"
#include <vector>

int main()
{
	std::vector<int> values = {1, 2, 3};
	cpp_printer::cout_vector("values", values);
}
```

Compilación directa:

```bash
c++ -std=c++17 -Iinclude example.cpp -o example
```

Con CMake:

```bash
cmake -S . -B build -DBUILD_TESTING=OFF
cmake --build build --target cpp_printer
```

Para consultar el manual completo, revisa [docs/CPP_PRINTER.md](docs/CPP_PRINTER.md).

## Funciones

La biblioteca incluye impresores para:

- Secuenciales: `array`, `vector`, `forward_list` y `deque`.
- Sets: `set`, `multiset` y `unordered_set`.
- Maps: `map`, `multimap` y `unordered_map`.
- Adaptadores: `queue`, `stack`, `priority_queue` y `pair`.

Todas las funciones pertenecen al namespace `cpp_printer` y escriben en
`std::cout`.

## CLI

El ejecutable muestra un mensaje inicial sin argumentos y permite copiar la
documentación al directorio actual:

```bash
cpp_printer helpme
```

La instalación coloca el ejecutable en `bin` y el manual en
`share/cpp_printer/CPP_PRINTER.md`.

## Nota

Estas funciones son atajos para ahorrar tiempo. No sustituyen el aprendizaje de
la STL ni la comprensión de las estructuras de datos.

**Automatiza la tarea, no el conocimiento.**
