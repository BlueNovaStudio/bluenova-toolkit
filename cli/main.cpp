#include "executable_path.hpp"

#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

void show_message()
{
    std::cout
        << "cpp_printer\n\n"
        << "Estas funciones son atajos para ahorrar tiempo al trabajar "
           "con contenedores de la STL.\n\n"
        << "Recuerda: estas herramientas no reemplazan el aprendizaje.\n"
        << "Debes comprender la logica que existe detras de cada estructura "
           "y de cada operacion.\n\n"
        << "Una herramienta puede ayudarte a trabajar mas rapido, "
           "pero tambien puede convertirse en un arma de doble filo "
           "si dependes de ella sin entender lo que hace.\n\n"
        << "Usa cpp_printer como un atajo, no como un sustituto "
           "del conocimiento.\n";
}

void show_helpme()
{
    const fs::path executable = get_executable_path();
    if (executable.empty())
    {
        std::cerr
            << "No se pudo determinar la ruta del ejecutable.\n";
        return;
    }

    const fs::path installed_documentation =
        executable.parent_path()
        / ".."
        / "share"
        / "cpp_printer"
        / "CPP_PRINTER.md";

    const fs::path development_documentation =
        executable.parent_path()
        / ".."
        / "docs"
        / "CPP_PRINTER.md";

    const fs::path source = fs::exists(installed_documentation)
        ? installed_documentation
        : development_documentation;

    const fs::path destination =
        fs::current_path() / "CPP_PRINTER.md";

    if (!fs::exists(source))
    {
        std::cerr
            << "No se pudo encontrar la documentacion de cpp_printer.\n"
            << "Rutas buscadas:\n"
            << fs::weakly_canonical(installed_documentation) << '\n'
            << fs::weakly_canonical(development_documentation) << '\n';

        return;
    }

    try
    {
        fs::copy_file(
            source,
            destination,
            fs::copy_options::overwrite_existing
        );

        std::cout
            << "Documentacion copiada correctamente.\n"
            << "Archivo: "
            << destination
            << '\n';
    }
    catch (const fs::filesystem_error& error)
    {
        std::cerr
            << "No se pudo copiar la documentacion.\n"
            << error.what()
            << '\n';
    }
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        show_message();
        return 0;
    }

    std::string command = argv[1];

    if (command == "helpme")
    {
        show_helpme();
        return 0;
    }

    std::cout << "Comando desconocido: " << command << '\n';
    return 1;
}