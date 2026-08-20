#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    template <typename Container, typename Target>
    void cout_search(const std::string& name_structure, const Container& container, const Target& target)
    {
        detail::print_name(std::cout, name_structure);
        detail::print_syntax(std::cout, " = {");

        auto it = std::begin(container);
        auto end = std::end(container);

        bool first = true;
        std::size_t index = 0;
        std::size_t match_count = 0;

        for (; it != end; ++it, ++index)
        {
            if (!first)
                detail::print_syntax(std::cout, ", ");

            // Comparación de elementos
            if (*it == target)
            {
                detail::print_highlight_value(std::cout, *it);
                ++match_count;
            }
            else
            {
                detail::print_value(std::cout, *it);
            }

            first = false;
        }

        detail::print_syntax(std::cout, "}\n");

        // Resumen de búsqueda
        if (match_count == 0)
        {
            detail::print_syntax(std::cout, "  └─ Elemento ");
            detail::print_highlight_value(std::cout, target);
            detail::print_syntax(std::cout, " no encontrado.\n");
        }
        else
        {
            detail::print_syntax(std::cout, "  └─ Encontrado en índice(s): [");
            bool first_match = true;
            index = 0;
            for (auto match_it = std::begin(container); match_it != std::end(container);
                 ++match_it, ++index)
            {
                if (*match_it == target) {
                    if (!first_match) detail::print_syntax(std::cout, ", ");
                    std::cout << index;
                    first_match = false;
                }
            }
            std::cout << "]\n";
        }
    }

    // Sobrecarga opcional para llamar sin nombre de estructura
    template <typename Container, typename Target>
    void cout_search(const Container& container, const Target& target)
    {
        cout_search("container", container, target);
    }
}
