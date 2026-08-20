#pragma once

#include <iostream>
#include <string>
#include <iterator>
#include <type_traits>
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    template <typename Container>
    void cout_stats(const std::string& name_structure, const Container& container)
    {
        detail::print_name(std::cout, name_structure);

        // Validación de contenedor vacío
        if (std::empty(container))
        {
            detail::print_syntax(std::cout, " [contenedor vacío]\n");
            return;
        }

        detail::print_syntax(std::cout, " (Estadísticas):\n");

        auto it = std::begin(container);
        auto end = std::end(container);

        using ElementType = std::remove_cv_t<std::remove_reference_t<decltype(*it)>>;

        // Inicializar min y max con el primer elemento mediante iteradores
        ElementType min_val = *it;
        ElementType max_val = *it;
        
        std::size_t size = 0;
        double suma = 0.0;

        // bucle para calcular todas las métricas
        for (; it != end; ++it)
        {
            const auto& elem = *it;

            if constexpr (std::is_arithmetic_v<ElementType>) {
                suma += static_cast<double>(elem);
            }

            if (elem < min_val) min_val = elem;
            if (elem > max_val) max_val = elem;
            ++size;
        }

        // Formateado con jerarquía usando tus helpers de color
        auto print_row = [](const char* label, const auto& val, bool is_last = false) {
            detail::print_syntax(std::cout, is_last ? "  └─ " : "  ├─ ");
            detail::print_syntax(std::cout, label);
            detail::print_syntax(std::cout, ": ");
            detail::print_value(std::cout, val);
            std::cout << "\n";
        };

        print_row("Tamaño  ", size);

        // Imprimir métricas numéricas solo si el tipo lo permite
        if constexpr (std::is_arithmetic_v<ElementType>)
        {
            double promedio = suma / static_cast<double>(size);
            print_row("Suma    ", suma);
            print_row("Promedio", promedio);
        }

        print_row("Mínimo  ", min_val);
        print_row("Máximo  ", max_val, true);
    }
}