# cpp_printer

`cpp_printer` es una biblioteca de headers para imprimir de forma rápida y legible
contenedores habituales de la STL de C++.

Las funciones escriben directamente en `std::cout`, muestran el nombre que se les
proporciona y aplican colores ANSI inspirados en el tema Dracula.

## Requisitos

- Compilador compatible con C++17 o superior.
- CMake 3.10 o superior para usar la configuración incluida.
- Una terminal compatible con colores ANSI truecolor para ver la paleta completa.

La biblioteca no necesita dependencias externas: solo utiliza la biblioteca estándar
de C++.

## Instalación y compilación

Incluye el directorio `include` en tu proyecto. Con CMake:

```bash
cmake -S . -B build -DBUILD_TESTING=OFF
cmake --build build
```

Para compilar los tests:

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

### Instalación rápida desde GitHub

En Linux o macOS puedes instalar los headers sin un gestor de paquetes:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh | bash
```

Por defecto se instala en `~/.local`. Compila incluyendo sus headers con:

```bash
c++ -std=c++17 -I"$HOME/.local/include" main.cpp -o app
```

Esta instalación es global para tu usuario. C++ no utiliza un entorno virtual
equivalente a `.venv`. Para aislar la biblioteca en un proyecto concreto:

```bash
mkdir -p .deps
CPP_PRINTER_PREFIX="$PWD/.deps" bash <(curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh)
c++ -std=c++17 -I"$PWD/.deps/include" main.cpp -o app
```

Si quieres usarla como un header del sistema y compilar sin `-I`, instala con
permisos administrativos:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh | sudo bash
```

Esto instala los headers en `/usr/local/include/cpp_printer`. Después puedes
compilar directamente:

```bash
g++ -std=c++17 main.cpp -o app
```

## Uso básico

La forma más sencilla de incluir todas las funciones es:

```cpp
#include "cpp_printer/print.hpp"
```

También puedes incluir un header concreto, por ejemplo:

```cpp
#include "cpp_printer/secuential/vector.hpp"
```

Ejemplo:

```cpp
#include "cpp_printer/print.hpp"
#include <vector>

int main()
{
		std::vector<int> values = {1, 2, 3};
		cpp_printer::cout_vector("values", values);
}
```

Salida visible:

```text
values = {1, 2, 3}
```

Los colores no aparecen en el bloque de texto anterior porque se representan en la
salida como códigos ANSI.

## Formato y colores

La salida utiliza esta convención:

| Elemento | Color Dracula | Código hex |
| --- | --- | --- |
| Números y booleanos | Purple | `#BD93F9` |
| Strings y `char` | Green | `#50FA7B` |
| Nombres de variables | Foreground | `#F8F8F2` |
| Símbolos, separadores y delimitadores | Foreground | `#F8F8F2` |
| Palabras clave reservadas | Pink | `#FF79C6` |
| Funciones y métodos | Cyan | `#8BE9FD` |
| Comentarios | Comment | `#6272A4` |
| Fondo de referencia | Background | `#282A36` |

La biblioteca imprime los strings con comillas dobles y los caracteres con comillas
simples:

```text
words = {"hello", "world"}
letters = {'a', 'b'}
```

## Funciones disponibles

Todas las funciones están en el namespace `cpp_printer` y siguen esta estructura:

```cpp
cpp_printer::funcion("nombre", contenedor);
```

El primer argumento es el nombre que aparecerá en la salida. El segundo argumento
debe ser una estructura compatible con la firma de la función.

### Contenedores secuenciales

#### `cout_array`

```cpp
template <typename T>
void cout_array(const std::string& name_array, const T* arr, std::size_t size);
```

Imprime un array tradicional mediante un puntero y su cantidad de elementos.

- `name_array`: nombre mostrado.
- `arr`: puntero al primer elemento.
- `size`: número de elementos válidos.
- Requisito: `arr` debe apuntar a una región válida de al menos `size` elementos.

```cpp
int values[] = {10, 20, 30};
cpp_printer::cout_array("values", values, 3);
```

#### `cout_vector`

```cpp
template <typename T>
void cout_vector(const std::string& name_vector,
								const std::vector<T>& container);
```

Requiere un `std::vector<T>`. Los elementos deben poder escribirse en un stream,
o ser tipos reconocidos por el formateador, como números, `bool`, `std::string` o
`char`.

#### `cout_list`

```cpp
template <typename T>
void cout_list(const std::string& name_list,
							const std::forward_list<T>& container);
```

Requiere un `std::forward_list<T>` cuyos elementos puedan imprimirse.

#### `cout_deque`

```cpp
template <typename T>
void cout_deque(const std::string& name_deque,
							 const std::deque<T>& container);
```

Requiere un `std::deque<T>` cuyos elementos puedan imprimirse.

### Sets

#### `cout_set`

```cpp
template <typename T>
void cout_set(const std::string& name_set, const std::set<T>& container);
```

Imprime un `std::set<T>` en el orden definido por el contenedor.

#### `cout_multiset`

```cpp
template <typename T>
void cout_multiset(const std::string& name_multiset,
									const std::multiset<T> container);
```

Imprime un `std::multiset<T>`, incluyendo los valores repetidos y respetando su
orden ordenado.

#### `cout_unordered_set`

```cpp
template <typename T>
void cout_unordered_set(const std::string& name_unordered_set,
											 std::unordered_set<T> container);
```

Imprime un `std::unordered_set<T>`. El orden no está garantizado y puede cambiar.

### Maps

Los mapas se imprimen con el formato `clave: valor`.

#### `cout_map`

```cpp
template <typename Key, typename T>
void cout_map(const std::string& name_map,
						 const std::map<Key, T>& container);
```

Requiere un `std::map<Key, T>`. La clave y el valor deben poder imprimirse.

#### `cout_multimap`

```cpp
template <typename Key, typename T>
void cout_multimap(const std::string& name_multimap,
									const std::multimap<Key, T>& container);
```

Requiere un `std::multimap<Key, T>`. Puede contener varias entradas con la misma
clave.

#### `cout_unordered_map`

```cpp
template <typename Key, typename T>
void cout_unordered_map(const std::string& name_unordered_map,
												const std::unordered_map<Key, T>& container);
```

Requiere un `std::unordered_map<Key, T>`. El orden de impresión no está garantizado.

### Adaptadores de contenedores

#### `cout_queue`

```cpp
template <typename T, typename Container>
void cout_queue(const std::string& name_queue,
								std::queue<T, Container> container);
```

Imprime la cola desde el primer elemento insertado hasta el último. Se pasa por
valor para poder usar `front()` y `pop()` sobre una copia; la cola original no cambia.

#### `cout_stack`

```cpp
template <typename T, typename Container>
void cout_stack(const std::string& name_stack,
								std::stack<T, Container> container);
```

Imprime desde el elemento superior hacia abajo usando `top()` y `pop()`. La pila
original no cambia porque la función trabaja con una copia.

#### `cout_priority_queue`

```cpp
template <typename T,
					typename Container = std::vector<T>,
					typename Compare = std::less<T>>
void cout_priority_queue(
		const std::string& name_priority_queue,
		std::priority_queue<T, Container, Compare> container);
```

Imprime los elementos en el orden de prioridad, comenzando por el elemento que
`top()` considera prioritario. La cola original no cambia.

#### `cout_pair`

```cpp
template <typename Key, typename T>
void cout_pair(const std::string& name_pair,
							 const std::pair<Key, T>& container);
```

Imprime una pareja con el formato `clave: valor`. Tanto `Key` como `T` deben poder
imprimirse.

```cpp
std::pair<std::string, char> status = {"state", 'A'};
cpp_printer::cout_pair("status", status);
```

## Tipos compatibles

El formateador reconoce automáticamente:

- Tipos numéricos y `bool`.
- `std::string` y cadenas literales, con comillas dobles.
- `char`, con comillas simples.
- Otros tipos que implementen `operator<<` para `std::ostream`.

Si un tipo personalizado no tiene `operator<<`, debes definirlo antes de usarlo con
una función de `cpp_printer`.

## Limitaciones

- La biblioteca imprime en `std::cout`; no devuelve strings.
- Los colores requieren una terminal ANSI truecolor.
- Los contenedores unordered no tienen un orden de impresión estable.
- `cout_array` no valida el tamaño ni el puntero; esa responsabilidad pertenece al
	código que realiza la llamada.

## Importante

Estas funciones son atajos diseñados para ahorrar tiempo.

No sustituyen el aprendizaje de la STL ni la comprensión de las estructuras de
datos.

Aprende primero cómo funcionan las estructuras.

Después utiliza estas herramientas para trabajar más rápido.

**Automatiza la tarea, no el conocimiento.**
