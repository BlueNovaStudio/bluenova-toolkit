# cpp_printer

Biblioteca header-only para imprimir contenedores habituales de la STL de C++ con
un formato legible y colores inspirados en Dracula.

## Tutorial paso a paso

Este tutorial muestra cómo instalar `cpp_printer`, crear un archivo C++ y
compilarlo desde la terminal. La forma más sencilla es usar WSL/Linux con
`g++`; en Windows nativo consulta la sección [Windows nativo](#windows-nativo).

### 1. Abre el entorno de desarrollo

En WSL, abre una terminal Ubuntu y entra en la carpeta donde guardarás tu
archivo:

```bash
mkdir -p ~/cpp-printer-example
cd ~/cpp-printer-example
```

En Windows nativo, abre PowerShell o la terminal de MSYS2 y entra en una carpeta
equivalente. No mezcles esta terminal con WSL:

```powershell
mkdir C:\cpp-printer-example
cd C:\cpp-printer-example
```

### 2. Instala la biblioteca

En WSL/Linux instala los headers globalmente para tu usuario del sistema:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh | sudo bash
```

Comprueba que la instalación exista:

```bash
ls /usr/local/include/cpp_printer/print.hpp
```

En Windows nativo, descarga el ZIP desde GitHub y copia la carpeta `include` a:

```text
C:\cpp-libs\cpp_printer\include\cpp_printer\print.hpp
```

### 3. Crea `main.cpp`

Crea un archivo llamado `main.cpp` en la carpeta del ejemplo y pega:

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

### 4. Compila desde la terminal

En WSL/Linux, como los headers están en `/usr/local/include`, no necesitas
escribir una ruta adicional:

```bash
g++ -std=c++17 main.cpp -o main
```

En Windows nativo con MinGW desde PowerShell, indica dónde están los headers:

```bash
g++ -std=c++17 main.cpp -I C:/cpp-libs/cpp_printer/include -o main.exe
```

Desde MSYS2 usa la ruta `/c`:

```bash
g++ -std=c++17 main.cpp -I /c/cpp-libs/cpp_printer/include -o main.exe
./main.exe
```

Desde WSL usa la ruta `/mnt/c` para acceder al mismo archivo de Windows:

```bash
g++ -std=c++17 main.cpp -I /mnt/c/cpp-libs/cpp_printer/include -o main
./main
```

Usa esta tabla para elegir correctamente:

| Entorno y compilador | Ruta de headers | Ejecutable |
| --- | --- | --- |
| WSL + g++ de Ubuntu | `/mnt/c/cpp-libs/cpp_printer/include` | `main` |
| PowerShell + MinGW | `C:/cpp-libs/cpp_printer/include` | `main.exe` |
| MSYS2 + MinGW | `/c/cpp-libs/cpp_printer/include` | `main.exe` |

Comprueba que el header exista antes de compilar. En PowerShell:

```powershell
Test-Path C:\cpp-libs\cpp_printer\include\cpp_printer\print.hpp
```

En MSYS2:

```bash
ls /c/cpp-libs/cpp_printer/include/cpp_printer/print.hpp
```

En WSL:

```bash
ls /mnt/c/cpp-libs/cpp_printer/include/cpp_printer/print.hpp
```

El resultado debe ser `True` en PowerShell o mostrar el archivo en las otras
terminales. Si `g++ --version` muestra Ubuntu, usa las rutas WSL; si muestra
MinGW, usa las rutas Windows/MSYS2.

### 5. Ejecuta el programa

En WSL/Linux:

```bash
./main
```

En Windows:

```bash
./main.exe
```

La salida será similar a:

```text
values = {1, 2, 3}
```

### 6. Usa el CLI y la documentación

El comando `cpp_printer` muestra el mensaje inicial. Si instalaste el proyecto
completo con CMake, puedes ejecutar:

```bash
cpp_printer
cpp_printer helpme
```

`helpme` copia `CPP_PRINTER.md` al directorio actual. Si estás dentro del árbol
del proyecto, también puedes usar el ejecutable de desarrollo:

```bash
./build/cpp_printer
./build/cpp_printer helpme
```

### 7. Actualiza la biblioteca

Cuando se publique una actualización, reinstala los headers:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh | sudo bash
```

Después recompila tu programa:

```bash
g++ -std=c++17 main.cpp -o main
./main
```

La biblioteca no busca archivos automáticamente: el compilador debe conocer la
ruta de los headers. En WSL se usa `/usr/local/include`; en Windows nativo se
usa `-I C:/cpp-libs/cpp_printer/include` o la configuración de VS Code.

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

### Actualizar una instalación existente

Si ya instalaste `cpp_printer`, vuelve a ejecutar el instalador para descargar
los cambios más recientes de `main`.

En WSL o Linux, si la instalación está en `/usr/local/include`:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh | sudo bash
```

Si la instalaste para tu usuario en `~/.local`:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh | bash
```

Si quedaron archivos antiguos, limpia la carpeta y reinstala:

```bash
sudo rm -rf /usr/local/include/cpp_printer
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh | sudo bash
```

Comprueba la instalación con:

```bash
ls /usr/local/include/cpp_printer/print.hpp
```

Después recompila tu archivo normalmente:

```bash
g++ -std=c++17 main.cpp -o main
./main
```

En Windows nativo, vuelve a descargar el ZIP de GitHub y reemplaza la carpeta:

```text
C:\cpp-libs\cpp_printer\include\cpp_printer
```

Después vuelve a ejecutar la tarea **Build main.cpp** de VS Code.

### Windows nativo

Si usas Windows nativo con MSYS2/UCRT64, abre **PowerShell** para instalar los
headers directamente en el include de MinGW:

```powershell
Set-ExecutionPolicy -Scope Process Bypass
irm https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.ps1 | iex
```

Después abre la terminal **MSYS2 UCRT64**, entra en la carpeta de tu archivo y
compila sin `-I`:

```bash
cd /c/Users/paulo/OneDrive/Desktop/pruebaLIB
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

Si tu compilador está instalado en otra carpeta, pasa esa ruta desde PowerShell:

```powershell
& ([scriptblock]::Create((irm https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.ps1))) -Prefix "C:\ruta\de\tu\mingw"
```

El script instala por defecto en `C:\msys64\ucrt64\include\cpp_printer`.

En Windows nativo, descarga el repositorio como ZIP desde GitHub y extrae la
carpeta `include` en una ubicación estable, por ejemplo:

```text
C:\cpp-libs\cpp_printer\include\cpp_printer\print.hpp
```

Tu archivo puede estar en cualquier carpeta, por ejemplo:

```text
C:\Users\paulo\Desktop\mi-programa\main.cpp
```

Si usas MinGW/MSYS2, compílalo indicando esa carpeta:

```bash
g++ -std=c++17 main.cpp -I C:/cpp-libs/cpp_printer/include -o main.exe
./main.exe
```

En VS Code debes abrir la carpeta que contiene `main.cpp` y configurar el
include path en `.vscode/c_cpp_properties.json`:

```json
{
	"version": 4,
	"configurations": [
		{
			"name": "Windows",
			"compilerPath": "C:/msys64/ucrt64/bin/g++.exe",
			"intelliSenseMode": "windows-gcc-x64",
			"cppStandard": "c++17",
			"includePath": [
				"${workspaceFolder}/**",
				"C:/cpp-libs/cpp_printer/include"
			]
		}
	]
}
```

La biblioteca no detecta automáticamente las carpetas: el compilador necesita
conocer la ruta mediante `-I` o mediante la configuración de VS Code.

Para que el botón **Run Build Task** compile ese archivo desde VS Code, crea
`.vscode/tasks.json`:

```json
{
	"version": "2.0.0",
	"tasks": [
		{
			"label": "Build main.cpp",
			"type": "shell",
			"command": "C:/msys64/ucrt64/bin/g++.exe",
			"args": [
				"-std=c++17",
				"${file}",
				"-I",
				"C:/cpp-libs/cpp_printer/include",
				"-o",
				"${fileDirname}/${fileBasenameNoExtension}.exe"
			],
			"problemMatcher": ["$gcc"]
		}
	]
}
```

Ejecuta la tarea con `Ctrl+Shift+B` y selecciona **Build main.cpp**.

### WSL

En Linux o macOS puedes instalar los headers y la configuración de CMake en tu
directorio personal con una sola línea:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh | bash
```

Para compilar como una biblioteca del sistema, sin `-I` ni rutas adicionales,
instálala en `/usr/local/include`:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh | sudo bash
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
CPP_PRINTER_PREFIX="$PWD/.deps" bash <(curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh)
```

Y compila ese proyecto con:

```bash
c++ -std=c++17 -I"$PWD/.deps/include" main.cpp -o app
```

También puedes inspeccionar el script antes de ejecutarlo o cambiar el destino:

```bash
curl -fsSL https://raw.githubusercontent.com/BlueNovaStudio/cpp-printer/main/install.sh -o install.sh
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
