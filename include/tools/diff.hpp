#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <type_traits>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "cpp_printer/detail/print_format.hpp"
#include "cpp_printer/detail/type_traits.hpp"

namespace cpp_printer
{
    // ============================================================
    // FUNCIONES DE AYUDA PARA IMPRESIÓN
    // ============================================================
    
    template <typename T>
    void print_diff_line(const std::string& prefix, const T& value, const std::string& color)
    {
        std::cout << color;
        detail::print_syntax(std::cout, prefix.c_str());
        detail::print_value(std::cout, value);
        std::cout << detail::color::reset << "\n";
    }
    
    template <typename T>
    void print_diff_with_marker(const T& value, const std::string& marker, const std::string& color)
    {
        std::cout << color;
        detail::print_syntax(std::cout, marker.c_str());
        detail::print_value(std::cout, value);
        std::cout << detail::color::reset << "\n";
    }

    template <typename Container1, typename Container2>
    void diff_maps_impl(const std::string&, const Container1&, const std::string&, const Container2&);
    
    // ============================================================
    // CASO 1: DIFERENCIA ENTRE SECUENCIAS ORDENADAS (VECTOR, LIST, DEQUE)
    // ============================================================
    
    template <typename Container1, typename Container2>
    void diff_sequences(const std::string& name1, const Container1& c1,
                        const std::string& name2, const Container2& c2)
    {
        // Mostrar nombres
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
        
        // Algoritmo de diferencia estilo diff
        while (it1 != end1 && it2 != end2)
        {
            if (*it1 != *it2)
            {
                has_differences = true;
                
                // Mostrar índice
                detail::print_syntax(std::cout, "  [");
                std::cout << detail::color::number << index << detail::color::reset;
                detail::print_syntax(std::cout, "] ");
                
                // Mostrar ambos valores con colores
                std::cout << detail::color::error << "- ";
                detail::print_value(std::cout, *it1);
                std::cout << detail::color::reset;
                std::cout << "\n";
                
                detail::print_syntax(std::cout, "      ");
                std::cout << detail::color::success << "+ ";
                detail::print_value(std::cout, *it2);
                std::cout << detail::color::reset;
                std::cout << "\n";
                
                ++it1;
                ++it2;
            }
            else
            {
                // Elementos iguales (mostrar en gris si quieres verbosidad)
                ++it1;
                ++it2;
            }
            ++index;
        }
        
        // Elementos sobrantes en c1 (eliminados)
        while (it1 != end1)
        {
            has_differences = true;
            detail::print_syntax(std::cout, "  [");
            std::cout << detail::color::number << index++ << detail::color::reset;
            detail::print_syntax(std::cout, "] ");
            std::cout << detail::color::error << "- ";
            detail::print_value(std::cout, *it1++);
            std::cout << detail::color::reset << "\n";
        }
        
        // Elementos sobrantes en c2 (añadidos)
        while (it2 != end2)
        {
            has_differences = true;
            detail::print_syntax(std::cout, "  [");
            std::cout << detail::color::number << index++ << detail::color::reset;
            detail::print_syntax(std::cout, "] ");
            std::cout << detail::color::success << "+ ";
            detail::print_value(std::cout, *it2++);
            std::cout << detail::color::reset << "\n";
        }
        
        if (!has_differences)
        {
            std::cout << "  " << detail::color::success 
                      << "✓ Las estructuras son idénticas." 
                      << detail::color::reset << "\n";
        }
    }
    
    // ============================================================
    // CASO 2: DIFERENCIA ENTRE MAPAS
    // ============================================================
    
    template <typename Container1, typename Container2>
    void diff_maps_impl(const std::string& name1, const Container1& map1,
                        const std::string& name2, const Container2& map2)
    {
        detail::print_name(std::cout, name1);
        detail::print_syntax(std::cout, " vs ");
        detail::print_name(std::cout, name2);
        detail::print_syntax(std::cout, ":\n");
        
        bool has_differences = false;
        auto it1 = map1.begin();
        auto end1 = map1.end();
        auto it2 = map2.begin();
        auto end2 = map2.end();
        
        while (it1 != end1 && it2 != end2)
        {
            if (it1->first != it2->first)
            {
                has_differences = true;
                if (it1->first < it2->first)
                {
                    // Clave solo en map1 (eliminada)
                    detail::print_syntax(std::cout, "  ");
                    std::cout << detail::color::error << "- ";
                    detail::print_value(std::cout, it1->first);
                    std::cout << " → ";
                    detail::print_value(std::cout, it1->second);
                    std::cout << detail::color::reset << "\n";
                    ++it1;
                }
                else
                {
                    // Clave solo en map2 (añadida)
                    detail::print_syntax(std::cout, "  ");
                    std::cout << detail::color::success << "+ ";
                    detail::print_value(std::cout, it2->first);
                    std::cout << " → ";
                    detail::print_value(std::cout, it2->second);
                    std::cout << detail::color::reset << "\n";
                    ++it2;
                }
            }
            else
            {
                // Misma clave, comparar valores
                if (it1->second != it2->second)
                {
                    has_differences = true;
                    detail::print_syntax(std::cout, "  ");
                    detail::print_value(std::cout, it1->first);
                    std::cout << ": ";
                    std::cout << detail::color::error << it1->second << detail::color::reset;
                    std::cout << " → ";
                    std::cout << detail::color::success << it2->second << detail::color::reset;
                    std::cout << "\n";
                }
                ++it1;
                ++it2;
            }
        }
        
        // Claves solo en map1
        while (it1 != end1)
        {
            has_differences = true;
            detail::print_syntax(std::cout, "  ");
            std::cout << detail::color::error << "- ";
            detail::print_value(std::cout, it1->first);
            std::cout << " → ";
            detail::print_value(std::cout, it1->second);
            std::cout << detail::color::reset << "\n";
            ++it1;
        }
        
        // Claves solo en map2
        while (it2 != end2)
        {
            has_differences = true;
            detail::print_syntax(std::cout, "  ");
            std::cout << detail::color::success << "+ ";
            detail::print_value(std::cout, it2->first);
            std::cout << " → ";
            detail::print_value(std::cout, it2->second);
            std::cout << detail::color::reset << "\n";
            ++it2;
        }
        
        if (!has_differences)
        {
            std::cout << "  " << detail::color::success 
                      << "✓ Los mapas son idénticos." 
                      << detail::color::reset << "\n";
        }
    }

    template <typename Container1, typename Container2>
    void diff_maps(const std::string& name1, const Container1& c1,
                   const std::string& name2, const Container2& c2)
    {
        if constexpr (detail::is_unordered_v<Container1> || detail::is_unordered_v<Container2>) {
            detail::print_name(std::cout, name1);
            detail::print_syntax(std::cout, " vs ");
            detail::print_name(std::cout, name2);
            detail::print_syntax(std::cout, ":\n  (Comparando por clave, no por orden)\n");
            bool has_differences = false;
            for (const auto& [key, value] : c1) {
                const auto found = c2.find(key);
                if (found == c2.end()) {
                    has_differences = true;
                    detail::print_syntax(std::cout, "  ");
                    std::cout << detail::color::error << "- ";
                    detail::print_value(std::cout, key);
                    std::cout << " → ";
                    detail::print_value(std::cout, value);
                    std::cout << detail::color::reset << "\n";
                } else if (value != found->second) {
                    has_differences = true;
                    detail::print_value(std::cout, key);
                    std::cout << ": " << detail::color::error;
                    detail::print_value(std::cout, value);
                    std::cout << detail::color::reset << " → " << detail::color::success;
                    detail::print_value(std::cout, found->second);
                    std::cout << detail::color::reset << "\n";
                }
            }
            for (const auto& [key, value] : c2) {
                if (c1.find(key) == c1.end()) {
                    has_differences = true;
                    detail::print_syntax(std::cout, "  ");
                    std::cout << detail::color::success << "+ ";
                    detail::print_value(std::cout, key);
                    std::cout << " → ";
                    detail::print_value(std::cout, value);
                    std::cout << detail::color::reset << "\n";
                }
            }
            if (!has_differences) {
                std::cout << "  " << detail::color::success << "✓ Los mapas son idénticos."
                          << detail::color::reset << "\n";
            }
        } else {
            diff_maps_impl(name1, c1, name2, c2);
        }
    }
    
    // ============================================================
    // CASO 3: DIFERENCIA ENTRE SETS
    // ============================================================
    
    template <typename Container1, typename Container2>
    void diff_sets(const std::string& name1, const Container1& c1,
                   const std::string& name2, const Container2& c2)
    {
        if constexpr (detail::is_unordered_v<Container1> || detail::is_unordered_v<Container2>) {
            detail::print_name(std::cout, name1);
            detail::print_syntax(std::cout, " vs ");
            detail::print_name(std::cout, name2);
            detail::print_syntax(std::cout, ":\n  (Comparando por contenido, no por orden)\n");

            bool has_differences = false;
            for (auto it = c1.begin(); it != c1.end();) {
                const auto range = c1.equal_range(*it);
                const auto count1 = c1.count(*it);
                const auto count2 = c2.count(*it);
                if (count1 > count2) {
                    for (typename Container1::size_type i = 0; i < count1 - count2; ++i) {
                        has_differences = true;
                        print_diff_with_marker(*it, "- ", detail::color::error);
                    }
                }
                it = range.second;
            }
            for (auto it = c2.begin(); it != c2.end();) {
                const auto range = c2.equal_range(*it);
                const auto count2 = c2.count(*it);
                const auto count1 = c1.count(*it);
                if (count2 > count1) {
                    for (typename Container2::size_type i = 0; i < count2 - count1; ++i) {
                        has_differences = true;
                        print_diff_with_marker(*it, "+ ", detail::color::success);
                    }
                }
                it = range.second;
            }
            if (!has_differences) {
                std::cout << "  " << detail::color::success << "✓ Los sets son idénticos."
                          << detail::color::reset << "\n";
            }
            return;
        }

        const Container1& set1 = c1;
        const Container2& set2 = c2;
        
        detail::print_name(std::cout, name1);
        detail::print_syntax(std::cout, " vs ");
        detail::print_name(std::cout, name2);
        detail::print_syntax(std::cout, ":\n");
        
        bool has_differences = false;
        auto it1 = set1.begin();
        auto end1 = set1.end();
        auto it2 = set2.begin();
        auto end2 = set2.end();
        
        while (it1 != end1 && it2 != end2)
        {
            if (*it1 != *it2)
            {
                has_differences = true;
                if (*it1 < *it2)
                {
                    // Elemento solo en set1 (eliminado)
                    detail::print_syntax(std::cout, "  ");
                    std::cout << detail::color::error << "- ";
                    detail::print_value(std::cout, *it1);
                    std::cout << detail::color::reset << "\n";
                    ++it1;
                }
                else
                {
                    // Elemento solo en set2 (añadido)
                    detail::print_syntax(std::cout, "  ");
                    std::cout << detail::color::success << "+ ";
                    detail::print_value(std::cout, *it2);
                    std::cout << detail::color::reset << "\n";
                    ++it2;
                }
            }
            else
            {
                ++it1;
                ++it2;
            }
        }
        
        // Elementos solo en set1
        while (it1 != end1)
        {
            has_differences = true;
            detail::print_syntax(std::cout, "  ");
            std::cout << detail::color::error << "- ";
            detail::print_value(std::cout, *it1++);
            std::cout << detail::color::reset << "\n";
        }
        
        // Elementos solo en set2
        while (it2 != end2)
        {
            has_differences = true;
            detail::print_syntax(std::cout, "  ");
            std::cout << detail::color::success << "+ ";
            detail::print_value(std::cout, *it2++);
            std::cout << detail::color::reset << "\n";
        }
        
        if (!has_differences)
        {
            std::cout << "  " << detail::color::success 
                      << "✓ Los sets son idénticos." 
                      << detail::color::reset << "\n";
        }
    }
    
    // ============================================================
    // FUNCIÓN PRINCIPAL cout_diff
    // ============================================================
    
    /**
     * Muestra las diferencias entre dos contenedores.
     * 
     * @param name1 Nombre del primer contenedor
     * @param c1 Primer contenedor
     * @param name2 Nombre del segundo contenedor
     * @param c2 Segundo contenedor
     * 
     * Ejemplo:
     *   vector<int> v1 = {1, 2, 3};
     *   vector<int> v2 = {1, 2, 3, 4};
     *   cout_diff("v1", v1, "v2", v2);
     *   // Salida:
     *   // v1 vs v2:
     *   //   [0] - 1
     *   //        + 1
     *   //   [1] - 2
     *   //        + 2
     *   //   [2] - 3
     *   //        + 3
     *   //   [3] + 4
     */
    template <typename Container1, typename Container2>
    void cout_diff(const std::string& name1, const Container1& c1,
                   const std::string& name2, const Container2& c2)
    {
        // Verificar contenedores vacíos
        bool empty1 = std::empty(c1);
        bool empty2 = std::empty(c2);
        
        if (empty1 && empty2) {
            detail::print_name(std::cout, name1);
            detail::print_syntax(std::cout, " vs ");
            detail::print_name(std::cout, name2);
            detail::print_syntax(std::cout, ":\n");
            std::cout << "  " << detail::color::success 
                      << "✓ Ambos contenedores están vacíos." 
                      << detail::color::reset << "\n";
            return;
        }
        
        // Dispatcher según el tipo de contenedor
        if constexpr (detail::is_map_like_v<Container1> && detail::is_map_like_v<Container2>) {
            diff_maps(name1, c1, name2, c2);
        } else if constexpr (detail::is_set_like_v<Container1> && detail::is_set_like_v<Container2>) {
            diff_sets(name1, c1, name2, c2);
        } else {
            // Fallback: comparación secuencial
            diff_sequences(name1, c1, name2, c2);
        }
    }
    
    // Sobrecarga con nombres por defecto
    template <typename Container1, typename Container2>
    void cout_diff(const Container1& c1, const Container2& c2) {
        cout_diff("left", c1, "right", c2);
    }
    
    // Sobrecarga para vectores (caso más común)
    template <typename T>
    void cout_diff(const std::vector<T>& v1, const std::vector<T>& v2) {
        cout_diff("v1", v1, "v2", v2);
    }
}
