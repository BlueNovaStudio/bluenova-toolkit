#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    template <typename Container1, typename Container2>
    void cout_compare(const std::string& name1, const Container1& c1,
                      const std::string& name2, const Container2& c2)
    {
        // Reutilización de cabecera con tus helpers
        detail::print_name(std::cout, name1);
        detail::print_syntax(std::cout, " vs ");
        detail::print_name(std::cout, name2);
        detail::print_syntax(std::cout, ":\n");

        auto it1 = std::begin(c1);
        auto end1 = std::end(c1);
        auto it2 = std::begin(c2);
        auto end2 = std::end(c2);

        std::size_t index = 0;
        bool has_differences = false;

        while (it1 != end1 && it2 != end2)
        {
            if (*it1 != *it2)
            {
                has_differences = true;
                
                // Índice
                detail::print_syntax(std::cout, "  [");
                std::cout << detail::color::number << index << detail::color::reset;
                detail::print_syntax(std::cout, "] ");

                // Imprime valor 1 respetando su tipo (string, int, char)
                detail::print_value(std::cout, *it1);

                // Operador de desigualdad con color de error
                std::cout << detail::color::error << " != " << detail::color::reset;

                // Imprime valor 2
                detail::print_value(std::cout, *it2);
                std::cout << "\n";
            }
            ++it1;
            ++it2;
            ++index;
        }

        // Manejo de elementos sobrantes si tienen diferentes tamaños
        while (it1 != end1)
        {
            has_differences = true;
            detail::print_syntax(std::cout, "  [");
            std::cout << detail::color::number << index++ << detail::color::reset;
            detail::print_syntax(std::cout, "] ");
            detail::print_value(std::cout, *it1++);
            std::cout << detail::color::error << " != <ausente>\n" << detail::color::reset;
        }

        while (it2 != end2)
        {
            has_differences = true;
            detail::print_syntax(std::cout, "  [");
            std::cout << detail::color::number << index++ << detail::color::reset;
            detail::print_syntax(std::cout, "] ");
            std::cout << detail::color::error << "<ausente> != " << detail::color::reset;
            detail::print_value(std::cout, *it2++);
            std::cout << "\n";
        }

        if (!has_differences)
        {
            std::cout << "  " << detail::color::success << "Las estructuras son idénticas." 
                      << detail::color::reset << "\n";
        }
    }
}