#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <type_traits>
#include "cpp_printer/detail/print_format.hpp"


// Nota: Asegúrate de incluir los helpers de formato/colores de tu proyecto
// #include "../detail/print_format.hpp"

namespace cpp_printer::detail {

    // Helper para obtener la longitud VISIBLE (sin contar secuencias de escape ANSI)
    template <typename T>
    std::size_t get_visible_length(const T& value) {
        using Value = std::remove_cv_t<std::remove_reference_t<T>>;

        if constexpr (std::is_same_v<Value, std::string>) {
            return value.length() + 2; // Incluye las comillas " " de la representación
        } else if constexpr (std::is_same_v<Value, const char*> || std::is_same_v<Value, char*>) {
            return (value ? std::strlen(value) : 0) + 2;
        } else if constexpr (std::is_array_v<Value> && std::is_same_v<std::remove_extent_t<Value>, char>) {
            return std::strlen(value) + 2;
        } else if constexpr (std::is_same_v<Value, char>) {
            return 3; // Incluye comillas simples ' '
        } else {
            std::ostringstream ss;
            ss << value;
            return ss.str().length();
        }
    }
}

namespace cpp_printer {

    /**
     * Imprime un contenedor 2D (matriz, vector de vectores, etc.) en formato de tabla ASCII.
     * 
     * @param output Stream de salida (por defecto std::cout)
     * @param name_structure Nombre de la variable a mostrar
     * @param matrix Estructura de datos bidimensional
     */
    template <typename Matrix>
    void print_table(std::ostream& output, const std::string& name_structure, const Matrix& matrix) {
        if (std::empty(matrix)) {
            detail::print_name(output, name_structure);
            detail::print_syntax(output, " [tabla vacía]\n");
            return;
        }

        // 1. Calcular el número total de columnas y el ancho máximo de cada una
        std::vector<std::size_t> col_widths;

        for (const auto& row : matrix) {
            std::size_t col_idx = 0;
            for (const auto& cell : row) {
                std::size_t cell_len = detail::get_visible_length(cell);
                if (col_idx >= col_widths.size()) {
                    col_widths.push_back(cell_len);
                } else {
                    col_widths[col_idx] = std::max(col_widths[col_idx], cell_len);
                }
                col_idx++;
            }
        }

        if (col_widths.empty()) {
            detail::print_name(output, name_structure);
            detail::print_syntax(output, " [tabla vacía]\n");
            return;
        }

        // Encabezado
        detail::print_name(output, name_structure);
        output << ":\n";

        // Helper para dibujar líneas de separación horizontales
        auto print_border = [&](const char* left, const char* mid, const char* right) {
            detail::print_syntax(output, left);
            for (std::size_t i = 0; i < col_widths.size(); ++i) {
                // Ancho de la columna + 2 de padding (1 espacio a cada lado)
                for (std::size_t w = 0; w < col_widths[i] + 2; ++w) {
                    detail::print_syntax(output, "─");
                }
                if (i + 1 < col_widths.size()) {
                    detail::print_syntax(output, mid);
                }
            }
            detail::print_syntax(output, right);
            output << "\n";
        };

        // Borde superior: ┌───┬───┐
        print_border("┌", "┬", "┐");

        // Filas de datos
        std::size_t row_idx = 0;
        std::size_t total_rows = std::distance(std::begin(matrix), std::end(matrix));

        for (const auto& row : matrix) {
            detail::print_syntax(output, "│");

            auto cell_it = std::begin(row);
            auto cell_end = std::end(row);

            for (std::size_t c = 0; c < col_widths.size(); ++c) {
                detail::print_syntax(output, " "); // Padding izquierdo

                if (cell_it != cell_end) {
                    detail::print_value(output, *cell_it);
                    std::size_t vis_len = detail::get_visible_length(*cell_it);
                    
                    // Relleno de espacios a la derecha según el ancho máximo de la columna
                    for (std::size_t pad = 0; pad < col_widths[c] - vis_len; ++pad) {
                        output << " ";
                    }
                    ++cell_it;
                } else {
                    // Celda vacía si la fila tiene menos columnas que el máximo
                    for (std::size_t pad = 0; pad < col_widths[c]; ++pad) {
                        output << " ";
                    }
                }

                detail::print_syntax(output, " "); // Padding derecho
                detail::print_syntax(output, "│");
            }
            output << "\n";

            row_idx++;
            if (row_idx < total_rows) {
                // Separador intermedio: ├───┼───┤
                print_border("├", "┼", "┤");
            }
        }

        // Borde inferior: └───┴───┘
        print_border("└", "┴", "┘");
    }

    // Sobrecarga con stream especificado y nombre por defecto
    template <typename Matrix>
    void print_table(std::ostream& output, const Matrix& matrix) {
        print_table(output, "matriz", matrix);
    }

    // Sobrecargas convenientes para std::cout
    template <typename Matrix>
    void cout_table(const std::string& name_structure, const Matrix& matrix) {
        print_table(std::cout, name_structure, matrix);
    }

    template <typename Matrix>
    void cout_table(const Matrix& matrix) {
        print_table(std::cout, "matriz", matrix);
    }

} // namespace cpp_printer