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

## Instalación rápida

En Linux o macOS puedes instalar los headers y la configuración de CMake en tu
directorio personal con una sola línea:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/bluenova-toolkit/main/install.sh | bash
```

Para compilar como una biblioteca del sistema, sin `-I` ni rutas adicionales,
instálala en `/usr/local/include`:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/bluenova-toolkit/main/install.sh | sudo bash
```

Después cualquier archivo puede usarla directamente:

```cpp
#include <cpp_printer/print.hpp>
```

Y compilarse con:

```bash
g++ -std=c++17 main.cpp -o app
```

Después, compila tu proyecto incluyendo los headers instalados:

```bash
c++ -std=c++17 -I"$HOME/.local/include" main.cpp -o app
```

La instalación anterior es global para tu usuario y queda disponible para todos
los proyectos. No existe un entorno virtual equivalente a `.venv` para headers
C++.

Si prefieres aislarla dentro de un solo proyecto, instala en una carpeta local:

```bash
mkdir -p .deps
CPP_PRINTER_PREFIX="$PWD/.deps" bash <(curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/bluenova-toolkit/main/install.sh)
```

Y compila ese proyecto con:

```bash
c++ -std=c++17 -I"$PWD/.deps/include" main.cpp -o app
```

También puedes inspeccionar el script antes de ejecutarlo o cambiar el destino:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/bluenova-toolkit/main/install.sh -o install.sh
CPP_PRINTER_PREFIX="$HOME/.local" bash install.sh
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
