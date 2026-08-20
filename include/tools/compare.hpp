#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <deque>
#include <map>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <type_traits>
#include "cpp_printer/detail/print_format.hpp"
#include "cpp_printer/detail/type_traits.hpp"

namespace cpp_printer
{
    template <typename Container1, typename Container2>
    void compare_ordered_sequences(const std::string&, const Container1&, const std::string&, const Container2&);

    template <typename Container1, typename Container2>
    void compare_maps(const std::string&, const Container1&, const std::string&, const Container2&);

    template <typename Container1, typename Container2>
    void compare_maps_impl(const std::string&, const Container1&, const std::string&, const Container2&);

    template <typename Container1, typename Container2>
    void compare_sets(const std::string&, const Container1&, const std::string&, const Container2&);

    template <typename Container1, typename Container2>
    void compare_unordered_containers(const std::string&, const Container1&, const std::string&, const Container2&);

    template <typename Container1, typename Container2>
    void compare_generic(const std::string&, const Container1&, const std::string&, const Container2&);

    template <typename T>
    void print_difference(std::size_t, const T&, const T&);

    template <typename T>
    void print_extra_left(std::size_t, const T&);

    template <typename T>
    void print_extra_right(std::size_t, const T&);

    template <typename Key>
    void print_map_key_only(const Key&, bool);

    template <typename Key, typename Value1, typename Value2>
    void print_map_value_difference(const Key&, const Value1&, const Value2&);

    template <typename T>
    void print_set_difference(const T&, bool);

    template <typename Container1, typename Container2>
    std::size_t count_differences_sequential(const Container1&, const Container2&);

    // ============================================================
    // FUNCIÓN PRINCIPAL (DISPATCH POR TIPO)
    // ============================================================
    
    template <typename Container1, typename Container2>
    void cout_compare(const std::string& name1, const Container1& c1,
                      const std::string& name2, const Container2& c2)
    {
        // Cabecera
        detail::print_name(std::cout, name1);
        detail::print_syntax(std::cout, " vs ");
        detail::print_name(std::cout, name2);
        detail::print_syntax(std::cout, ":\n");
        
        // Verificar contenedores vacíos
        bool empty1 = std::empty(c1);
        bool empty2 = std::empty(c2);
        
        if (empty1 && empty2) {
            std::cout << "  " << detail::color::success << "Ambos contenedores están vacíos." 
                      << " Son idénticas." << detail::color::reset << "\n";
            return;
        }
        
        if (empty1) {
            std::cout << "  " << detail::color::error << name1 << " está vacío. " 
                      << name2 << " tiene " << std::distance(std::begin(c2), std::end(c2)) 
                      << " elementos." << detail::color::reset << "\n";
            return;
        }
        
        if (empty2) {
            std::cout << "  " << detail::color::error << name2 << " está vacío. " 
                      << name1 << " tiene " << std::distance(std::begin(c1), std::end(c1)) 
                      << " elementos." << detail::color::reset << "\n";
            return;
        }
        
        // Dispatcher según el tipo de contenedor
        if constexpr (detail::is_map_like_v<Container1> && detail::is_map_like_v<Container2>) {
            compare_maps(name1, c1, name2, c2);
        } else if constexpr (detail::is_set_like_v<Container1> && detail::is_set_like_v<Container2>) {
            compare_sets(name1, c1, name2, c2);
        } else if constexpr (detail::is_unordered_v<Container1> || detail::is_unordered_v<Container2>) {
            compare_unordered_containers(name1, c1, name2, c2);
        } else if constexpr (detail::is_ordered_sequence_v<Container1> && detail::is_ordered_sequence_v<Container2>) {
            compare_ordered_sequences(name1, c1, name2, c2);
        } else {
            // Fallback: comparación genérica con intento de sentido común
            compare_generic(name1, c1, name2, c2);
        }
    }
    
    // ============================================================
    // CASO 1: CONTENEDORES ORDENADOS (VECTOR, LIST, DEQUE, ARRAY)
    // ============================================================
    
    template <typename Container1, typename Container2>
    void compare_ordered_sequences(const std::string& name1, const Container1& c1,
                                   const std::string& name2, const Container2& c2)
    {
        auto it1 = std::begin(c1);
        auto end1 = std::end(c1);
        auto it2 = std::begin(c2);
        auto end2 = std::end(c2);
        
        std::size_t index = 0;
        std::size_t differences = 0;
        
        // Comparación posición por posición
        while (it1 != end1 && it2 != end2)
        {
            if (*it1 != *it2)
            {
                ++differences;
                print_difference(index, *it1, *it2);
            }
            ++it1;
            ++it2;
            ++index;
        }
        
        // Elementos sobrantes
        while (it1 != end1) {
            ++differences;
            print_extra_left(index++, *it1++);
        }
        
        while (it2 != end2) {
            ++differences;
            print_extra_right(index++, *it2++);
        }
        
        if (differences == 0) {
            std::cout << "  " << detail::color::success 
                      << "Las estructuras son idénticas (mismo tamaño y elementos en misma posición)." 
                      << detail::color::reset << "\n";
        } else {
            std::cout << "  " << detail::color::info 
                      << "Se encontraron " << differences
                      << " diferencias." << detail::color::reset << "\n";
        }
    }
    
    // ============================================================
    // CASO 2: MAPS (std::map, std::unordered_map)
    // ============================================================
    
    template <typename Container1, typename Container2>
    void compare_maps_impl(const std::string& name1, const Container1& map1,
                           const std::string& name2, const Container2& map2)
    {
        bool has_differences = false;
        auto it1 = map1.begin();
        auto end1 = map1.end();
        auto it2 = map2.begin();
        auto end2 = map2.end();
        
        // Encontrar diferencias en claves y valores
        while (it1 != end1 && it2 != end2)
        {
            if (it1->first != it2->first) {
                has_differences = true;
                if (it1->first < it2->first) {
                    print_map_key_only(it1->first, true);
                    ++it1;
                } else {
                    print_map_key_only(it2->first, false);
                    ++it2;
                }
            } else {
                // Misma clave, comparar valores
                if (it1->second != it2->second) {
                    has_differences = true;
                    print_map_value_difference(it1->first, it1->second, it2->second);
                }
                ++it1;
                ++it2;
            }
        }
        
        // Elementos sobrantes en map1
        while (it1 != end1) {
            has_differences = true;
            print_map_key_only(it1->first, true);
            ++it1;
        }
        
        // Elementos sobrantes en map2
        while (it2 != end2) {
            has_differences = true;
            print_map_key_only(it2->first, false);
            ++it2;
        }
        
        if (!has_differences) {
            std::cout << "  " << detail::color::success 
                      << "Los maps son idénticos (mismas claves y valores)." 
                      << detail::color::reset << "\n";
        }
    }

    template <typename Container1, typename Container2>
    void compare_maps(const std::string& name1, const Container1& c1,
                      const std::string& name2, const Container2& c2)
    {
        if constexpr (detail::is_unordered_v<Container1> || detail::is_unordered_v<Container2>) {
            using KeyType = typename Container1::key_type;
            using MappedType1 = typename Container1::mapped_type;
            using MappedType2 = typename Container2::mapped_type;
            std::map<KeyType, MappedType1> map1(c1.begin(), c1.end());
            std::map<KeyType, MappedType2> map2(c2.begin(), c2.end());
            compare_maps_impl(name1, map1, name2, map2);
        } else {
            compare_maps_impl(name1, c1, name2, c2);
        }
    }
    
    // ============================================================
    // CASO 3: SETS (std::set, std::unordered_set)
    // ============================================================
    
    template <typename Container1, typename Container2>
    void compare_sets(const std::string& name1, const Container1& c1,
                      const std::string& name2, const Container2& c2)
    {
        using ElementType = typename Container1::value_type;
        
        // Convertir a std::set para comparación ordenada
        std::set<ElementType> set1(c1.begin(), c1.end());
        std::set<ElementType> set2(c2.begin(), c2.end());
        
        bool has_differences = false;
        auto it1 = set1.begin();
        auto end1 = set1.end();
        auto it2 = set2.begin();
        auto end2 = set2.end();
        
        while (it1 != end1 && it2 != end2)
        {
            if (*it1 != *it2) {
                has_differences = true;
                if (*it1 < *it2) {
                    print_set_difference(*it1, true);
                    ++it1;
                } else {
                    print_set_difference(*it2, false);
                    ++it2;
                }
            } else {
                ++it1;
                ++it2;
            }
        }
        
        while (it1 != end1) {
            has_differences = true;
            print_set_difference(*it1++, true);
        }
        
        while (it2 != end2) {
            has_differences = true;
            print_set_difference(*it2++, false);
        }
        
        if (!has_differences) {
            std::cout << "  " << detail::color::success 
                      << "Los sets son idénticos (mismos elementos)." 
                      << detail::color::reset << "\n";
        }
    }
    
    // ============================================================
    // CASO 4: CONTENEDORES UNORDERED
    // ============================================================
    
    template <typename Container1, typename Container2>
    void compare_unordered_containers(const std::string& name1, const Container1& c1,
                                      const std::string& name2, const Container2& c2)
    {
        // Para unordered, comparamos por contenido, no por orden
        // Crear copias ordenadas si es posible
        using ElementType = decltype(*std::begin(c1));
        
        std::vector<ElementType> vec1(c1.begin(), c1.end());
        std::vector<ElementType> vec2(c2.begin(), c2.end());
        
        std::sort(vec1.begin(), vec1.end());
        std::sort(vec2.begin(), vec2.end());
        
        bool has_differences = false;
        auto it1 = vec1.begin();
        auto end1 = vec1.end();
        auto it2 = vec2.begin();
        auto end2 = vec2.end();
        
        // Mostrar mensaje informativo
        detail::print_syntax(std::cout, "  (Comparando por contenido, no por orden)\n");
        
        while (it1 != end1 && it2 != end2)
        {
            if (*it1 != *it2) {
                has_differences = true;
                print_difference(std::distance(vec1.begin(), it1), *it1, *it2);
                ++it1;
                ++it2;
            } else {
                ++it1;
                ++it2;
            }
        }
        
        while (it1 != end1) {
            has_differences = true;
            print_extra_left(std::distance(vec1.begin(), it1), *it1++);
        }
        
        while (it2 != end2) {
            has_differences = true;
            print_extra_right(std::distance(vec2.begin(), it2), *it2++);
        }
        
        if (!has_differences) {
            std::cout << "  " << detail::color::success 
                      << "Los contenedores unordered son idénticos (mismos elementos)." 
                      << detail::color::reset << "\n";
        }
    }
    
    // ============================================================
    // CASO 5: FALLBACK GENÉRICO
    // ============================================================
    
    template <typename Container1, typename Container2>
    void compare_generic(const std::string& name1, const Container1& c1,
                         const std::string& name2, const Container2& c2)
    {
        std::cout << "  " << detail::color::warning 
                  << "Comparando tipos de contenedores diferentes. Usando comparación posición por posición."
                  << detail::color::reset << "\n";
        
        compare_ordered_sequences(name1, c1, name2, c2);
    }
    
    // ============================================================
    // FUNCIONES DE AYUDA PARA IMPRESIÓN
    // ============================================================
    
    template <typename T>
    void print_difference(std::size_t index, const T& val1, const T& val2)
    {
        detail::print_syntax(std::cout, "  [");
        std::cout << detail::color::number << index << detail::color::reset;
        detail::print_syntax(std::cout, "] ");
        detail::print_value(std::cout, val1);
        std::cout << detail::color::error << " != " << detail::color::reset;
        detail::print_value(std::cout, val2);
        std::cout << "\n";
    }
    
    template <typename T>
    void print_extra_left(std::size_t index, const T& val)
    {
        detail::print_syntax(std::cout, "  [");
        std::cout << detail::color::number << index << detail::color::reset;
        detail::print_syntax(std::cout, "] ");
        detail::print_value(std::cout, val);
        std::cout << detail::color::error << " != <ausente>\n" << detail::color::reset;
    }
    
    template <typename T>
    void print_extra_right(std::size_t index, const T& val)
    {
        detail::print_syntax(std::cout, "  [");
        std::cout << detail::color::number << index << detail::color::reset;
        detail::print_syntax(std::cout, "] ");
        std::cout << detail::color::error << "<ausente> != " << detail::color::reset;
        detail::print_value(std::cout, val);
        std::cout << "\n";
    }
    
    template <typename Key>
    void print_map_key_only(const Key& key, bool in_first)
    {
        detail::print_syntax(std::cout, "  ");
        if (in_first) {
            detail::print_value(std::cout, key);
            std::cout << detail::color::error << " != <ausente>\n" << detail::color::reset;
        } else {
            std::cout << detail::color::error << "<ausente> -> " << detail::color::reset;
            detail::print_value(std::cout, key);
            std::cout << "\n";
        }
    }
    
    template <typename Key, typename Value1, typename Value2>
    void print_map_value_difference(const Key& key, const Value1& val1, const Value2& val2)
    {
        detail::print_syntax(std::cout, "  ");
        detail::print_value(std::cout, key);
        detail::print_syntax(std::cout, ": ");
        detail::print_value(std::cout, val1);
        std::cout << detail::color::error << " != " << detail::color::reset;
        detail::print_value(std::cout, val2);
        std::cout << "\n";
    }
    
    template <typename T>
    void print_set_difference(const T& val, bool in_first)
    {
        detail::print_syntax(std::cout, "  ");
        if (in_first) {
            detail::print_value(std::cout, val);
            std::cout << detail::color::error << " <-> <ausente>\n" << detail::color::reset;
        } else {
            std::cout << detail::color::error << "<ausente> <-> " << detail::color::reset;
            detail::print_value(std::cout, val);
            std::cout << "\n";
        }
    }
    
    template <typename Container1, typename Container2>
    std::size_t count_differences_sequential(const Container1& c1, const Container2& c2)
    {
        auto it1 = std::begin(c1);
        auto end1 = std::end(c1);
        auto it2 = std::begin(c2);
        auto end2 = std::end(c2);
        
        std::size_t count = 0;
        
        while (it1 != end1 && it2 != end2) {
            if (*it1 != *it2) count++;
            ++it1;
            ++it2;
        }
        
        count += std::distance(it1, end1);
        count += std::distance(it2, end2);
        
        return count;
    }
}
