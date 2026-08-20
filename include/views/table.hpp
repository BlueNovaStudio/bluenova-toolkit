#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <type_traits>
#include <iomanip>
#include <iterator>
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer::detail {

    // Helper para obtener la longitud VISIBLE (sin contar secuencias de escape ANSI)
    template <typename T>
    std::size_t get_visible_length(const T& value) {
        using Value = std::remove_cv_t<std::remove_reference_t<T>>;

        if constexpr (std::is_same_v<Value, std::string>) {
            return value.length() + 2; // Incluye las comillas " " de la representación
        } else if constexpr (std::is_same_v<Value, const char*> || std::is_same_v<Value, char*>) {
            return (value ? std::strlen(value) : 4) + 2; // "null" es el caso especial
        } else if constexpr (std::is_array_v<Value> && std::is_same_v<std::remove_extent_t<Value>, char>) {
            const auto terminator = std::find(std::begin(value), std::end(value), '\0');
            return static_cast<std::size_t>(std::distance(std::begin(value), terminator)) + 2;
        } else if constexpr (std::is_same_v<Value, char>) {
            return 3; // Incluye comillas simples ' '
        } else if constexpr (std::is_same_v<Value, bool>) {
            return value ? 4 : 5; // "true" o "false"
        } else if constexpr (std::is_floating_point_v<Value>) {
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(2) << value;
            return ss.str().length();
        } else {
            std::ostringstream ss;
            ss << value;
            return ss.str().length();
        }
    }

    // Helper para imprimir valores con formato consistente
    template <typename T>
    void print_value_formatted(std::ostream& output, const T& value) {
        using Value = std::remove_cv_t<std::remove_reference_t<T>>;

        if constexpr (std::is_same_v<Value, std::string>) {
            output << "\"" << value << "\"";
        } else if constexpr (std::is_same_v<Value, const char*> || std::is_same_v<Value, char*>) {
            if (value) {
                output << "\"" << value << "\"";
            } else {
                output << "null";
            }
        } else if constexpr (std::is_array_v<Value> && std::is_same_v<std::remove_extent_t<Value>, char>) {
            const auto terminator = std::find(std::begin(value), std::end(value), '\0');
            output << '"';
            output.write(value, static_cast<std::streamsize>(std::distance(std::begin(value), terminator)));
            output << '"';
        } else if constexpr (std::is_same_v<Value, char>) {
            output << "'" << value << "'";
        } else if constexpr (std::is_same_v<Value, bool>) {
            output << (value ? "true" : "false");
        } else if constexpr (std::is_floating_point_v<Value>) {
            output << std::fixed << std::setprecision(2) << value;
        } else {
            output << value;
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
        // Verificar si la matriz está vacía (compatible con C++17)
        if (std::empty(matrix)) {
            detail::print_name(output, name_structure);
            detail::print_syntax(output, " [tabla vacía]\n");
            return;
        }

        // Calcular columnas y detectar filas con datos en una sola pasada.
        std::vector<std::size_t> col_widths;
        std::size_t max_columns = 0;
        for (const auto& row : matrix) {
            std::size_t row_size = std::distance(std::begin(row), std::end(row));
            max_columns = std::max(max_columns, row_size);
        }

        if (max_columns == 0) {
            detail::print_name(output, name_structure);
            detail::print_syntax(output, " [tabla con filas vacías]\n");
            return;
        }

        // Inicializar widths con max_columns
        col_widths.resize(max_columns, 0);

        // Segundo pase: calcular anchos máximos
        for (const auto& row : matrix) {
            std::size_t col_idx = 0;
            for (const auto& cell : row) {
                std::size_t cell_len = detail::get_visible_length(cell);
                col_widths[col_idx] = std::max(col_widths[col_idx], cell_len);
                col_idx++;
            }
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
                    // Imprimir el valor con formato
                    detail::print_value_formatted(output, *cell_it);
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
