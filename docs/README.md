# Documentación y mantenimiento de cpp_printer

Esta guía describe la estructura del repositorio y sirve como punto de entrada
para mantener la biblioteca. La versión actual es **v1.0.4**; la anterior fue
**v1.0.3**.

## Documentos

- [CPP_PRINTER.md](CPP_PRINTER.md): instalación, uso público y ejemplos.
- [CHANGELOG.md](CHANGELOG.md): cambios publicados por versión.
- [VCPKG.md](VCPKG.md): instalación y publicación mediante vcpkg.

## Estructura del repositorio

| Directorio | Responsabilidad |
| --- | --- |
| `include/` | API header-only y lógica principal de la biblioteca. |
| `include/cpp_printer/` | Impresores de contenedores STL y utilidades internas. |
| `include/tools/` | Análisis, búsqueda y comparación de contenedores. |
| `include/views/` | Representaciones ASCII, tabla y árbol. |
| `examples/` | Programas ejecutables que muestran el uso de cada módulo. |
| `tests/` | Tests automatizados de regresión. |
| `cli/` | Código fuente de la herramienta de línea de comandos. |
| `src/` | Implementación no header-only usada por la CLI. |
| `cmake/` | Configuración para que proyectos consumidores usen `find_package`. |
| `docs/` | Guías de uso, arquitectura, publicación e historial. |
| `build/` | Directorio generado por CMake; no forma parte del código fuente. |

## El corazón: `include/`

`include/` contiene toda la funcionalidad consumida por los usuarios. La
biblioteca es header-only: el consumidor solo necesita añadir esta carpeta a
su ruta de inclusión y compilar con C++17.

### Punto de entrada

- `all.hpp` incluye todos los módulos públicos, incluidos `compare` y `diff`.
  Es conveniente para prototipos o programas pequeños.
- Para minimizar tiempo de compilación, un consumidor debe incluir solo el
  header del módulo que utiliza, por ejemplo
  `cpp_printer/sequential/vector.hpp` o `views/table.hpp`.

### `include/cpp_printer/`

Contiene los impresores de contenedores estándar:

- `sequential/`: `array`, `vector`, `list` y `deque`.
- `sets/`: `set`, `multiset` y `unordered_set`.
- `maps/`: `map`, `multimap` y `unordered_map`.
- `adapters/`: `queue`, `stack`, `priority_queue` y `pair`.
- `detail/`: infraestructura interna que no debe usarse directamente desde
  aplicaciones consumidoras.

Dentro de `detail/` destacan:

- `print_format.hpp`: formato de valores, colores ANSI y soporte para
  `std::variant`.
- `print_range.hpp` y `print_pop_container.hpp`: recorrido reutilizable de
  rangos y adaptadores; reciben un `std::ostream&` para no acoplar la lógica a
  `std::cout`.
- `type_traits.hpp`: fuente única de traits para mapas, sets, secuencias y
  contenedores unordered. Todo trait nuevo compartido debe añadirse aquí, no
  duplicarse en un header de herramienta o vista.

### `include/tools/`

- `compare.hpp`: compara contenido y muestra diferencias.
- `diff.hpp`: muestra cambios con formato de adición/eliminación.
- `search.hpp`: localiza y resalta coincidencias.
- `stats.hpp`: calcula estadísticas para secuencias, mapas y sets.

Los mapas ordenados se recorren directamente. Para unordered containers se crea
una vista ordenada únicamente cuando hace falta una salida determinista.

### `include/views/`

- `ascii.hpp`: gráficos horizontales para secuencias numéricas.
- `table.hpp`: renderizado de estructuras bidimensionales.
- `tree.hpp`: representación jerárquica de contenedores y mapas anidados.

## Reglas para cambios futuros

1. Conserva la API pública `cout_*` salvo que exista una migración documentada.
2. Coloca lógica reutilizable en `cpp_printer/detail/`; evita duplicar traits,
   formato o recorridos entre módulos.
3. Evita copias y recorridos extra para contenedores ordenados; el coste de
   salida ya puede ser alto en colecciones grandes.
4. Mantén el soporte C++17. No introduzcas concepts ni APIs posteriores sin
   elevar y documentar el requisito mínimo.
5. Cada cambio de comportamiento debe incluir o actualizar un test en
   `tests/` y un ejemplo relevante en `examples/`.
6. Antes de publicar, ejecuta compilación, CTest, ejemplos y una comprobación
   de inclusión conjunta de `all.hpp`.

El workflow [CI](../.github/workflows/ci.yml) aplica ese flujo automáticamente
en cada push y pull request con GCC, Clang y MSVC.

## Validación de una entrega

```bash
cmake -S . -B build -DCPP_PRINTER_BUILD_TESTS=ON -DCPP_PRINTER_BUILD_EXAMPLES=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
ctest --test-dir build -V
```

La salida detallada (`-V`) sirve para inspeccionar cada test. Los ejemplos se
pueden ejecutar desde `build/` como `./build/example_compare` o
`./build/example_tree`.
