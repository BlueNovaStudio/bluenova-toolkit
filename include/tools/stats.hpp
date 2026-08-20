#pragma once

#include <iostream>
#include <string>
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
    template <typename T, typename = void>
    struct stats_is_comparable : std::false_type {};

    template <typename T>
    struct stats_is_comparable<T, std::void_t<
        decltype(std::declval<const T&>() < std::declval<const T&>()),
        decltype(std::declval<const T&>() > std::declval<const T&>())>>
        : std::true_type {};

    template <typename Container>
    void print_stats_generic(const std::string&, const Container&);

    template <typename Container>
    void print_stats_map(const std::string&, const Container&);

    template <typename Container>
    void print_stats_set(const std::string&, const Container&);
    
    // ============================================================
    // FUNCIÓN PRINCIPAL (DISPATCH POR TIPO)
    // ============================================================
    
    template <typename Container>
    void cout_stats(const std::string& name_structure, const Container& container)
    {
        detail::print_name(std::cout, name_structure);
        
        // Caso: contenedor vacío
        if (std::empty(container))
        {
            detail::print_syntax(std::cout, " [contenedor vacío]\n");
            return;
        }
        
        detail::print_syntax(std::cout, " (Estadísticas):\n");
        
        // Dispatcher según el tipo de contenedor
        if constexpr (detail::is_map_like_v<Container>) {
            print_stats_map(name_structure, container);
        } else if constexpr (detail::is_set_like_v<Container>) {
            print_stats_set(name_structure, container);
        } else {
            print_stats_generic(name_structure, container);
        }
    }
    
    // ============================================================
    // CASO 1: CONTENEDORES GENÉRICOS (VECTOR, LIST, DEQUE, ETC)
    // ============================================================
    
    template <typename Container>
    void print_stats_generic(const std::string&, const Container& container)
    {
        auto it = std::begin(container);
        auto end = std::end(container);
        
        using ElementType = std::remove_cv_t<std::remove_reference_t<decltype(*it)>>;
        
        // Verificar si el tipo es numérico
        constexpr bool is_numeric = std::is_arithmetic_v<ElementType>;
        constexpr bool is_comparable = stats_is_comparable<ElementType>::value &&
                                       std::is_copy_constructible_v<ElementType> &&
                                       std::is_copy_assignable_v<ElementType>;
        
        std::size_t size = 0;
        long double suma = 0.0L;
        
        // Primer pase: calcular métricas
        for (; it != end; ++it) {
            if constexpr (is_numeric) suma += static_cast<long double>(*it);
            ++size;
        }
        
        // Helper de impresión
        auto print_row = [](const char* label, const auto& val, bool is_last = false) {
            detail::print_syntax(std::cout, is_last ? "  └─ " : "  ├─ ");
            detail::print_syntax(std::cout, label);
            detail::print_syntax(std::cout, ": ");
            detail::print_value(std::cout, val);
            std::cout << "\n";
        };
        
        // Imprimir estadísticas
        print_row("Tamaño  ", size);
        
        if constexpr (is_numeric) {
            const long double promedio = suma / static_cast<long double>(size);
            print_row("Suma    ", suma);
            print_row("Promedio", promedio);
        } else {
            detail::print_syntax(std::cout, "  ├─ Tipo no numérico\n");
        }
        
        if constexpr (is_comparable) {
            auto min_val = *std::begin(container);
            auto max_val = min_val;
            for (const auto& elem : container) {
                if (elem < min_val) min_val = elem;
                if (elem > max_val) max_val = elem;
            }
            print_row("Mínimo  ", min_val);
            print_row("Máximo  ", max_val, true);
        } else {
            detail::print_syntax(std::cout, "  └─ Tipo no comparable\n");
        }
    }
    
    // ============================================================
    // CASO 2: MAP (std::map, std::unordered_map)
    // ============================================================
    
    template <typename Container>
    void print_stats_map(const std::string&, const Container& container)
    {
        auto it = std::begin(container);
        auto end = std::end(container);
        
        using KeyType = typename Container::key_type;
        using MappedType = typename Container::mapped_type;
        
        const std::size_t size = container.size();
        long double suma_keys = 0.0L;
        long double suma_values = 0.0L;
        
        // Solo si las claves son numéricas
        constexpr bool key_is_numeric = std::is_arithmetic_v<KeyType>;
        constexpr bool value_is_numeric = std::is_arithmetic_v<MappedType>;
        
        for (; it != end; ++it)
        {
            const auto& [key, value] = *it;
            
            if constexpr (key_is_numeric) {
                suma_keys += static_cast<long double>(key);
            }
            
            if constexpr (value_is_numeric) {
                suma_values += static_cast<long double>(value);
            }
        }
        
        auto print_row = [](const char* label, const auto& val, bool is_last = false) {
            detail::print_syntax(std::cout, is_last ? "  └─ " : "  ├─ ");
            detail::print_syntax(std::cout, label);
            detail::print_syntax(std::cout, ": ");
            detail::print_value(std::cout, val);
            std::cout << "\n";
        };
        
        print_row("Tamaño (pares)", size);
        if constexpr (key_is_numeric) {
            auto min_key = std::begin(container)->first;
            auto max_key = min_key;
            for (const auto& entry : container) {
                min_key = std::min(min_key, entry.first);
                max_key = std::max(max_key, entry.first);
            }
            print_row("Clave mínima  ", min_key);
            print_row("Clave máxima  ", max_key);
            const long double avg_key = suma_keys / static_cast<long double>(size);
            print_row("Promedio clave", avg_key);
        } else {
            detail::print_syntax(std::cout, "  ├─ Claves no ordenables numéricamente\n");
        }
        
        if constexpr (value_is_numeric) {
            auto min_value = std::begin(container)->second;
            auto max_value = min_value;
            for (const auto& entry : container) {
                min_value = std::min(min_value, entry.second);
                max_value = std::max(max_value, entry.second);
            }
            const long double avg_value = suma_values / static_cast<long double>(size);
            print_row("Valor mínimo  ", min_value);
            print_row("Valor máximo  ", max_value);
            print_row("Promedio valor", avg_value, true);
        } else {
            detail::print_syntax(std::cout, "  └─ Valores no numéricos\n");
        }
    }
    
    // ============================================================
    // CASO 3: SET (std::set, std::unordered_set)
    // ============================================================
    
    template <typename Container>
    void print_stats_set(const std::string&, const Container& container)
    {
        auto it = std::begin(container);
        auto end = std::end(container);
        
        using ElementType = typename Container::value_type;
        
        const std::size_t size = container.size();
        long double suma = 0.0L;
        
        constexpr bool is_numeric = std::is_arithmetic_v<ElementType>;
        
        for (; it != end; ++it)
        {
            const auto& elem = *it;
            
            if constexpr (is_numeric) {
                suma += static_cast<long double>(elem);
            }
        }
        
        auto print_row = [](const char* label, const auto& val, bool is_last = false) {
            detail::print_syntax(std::cout, is_last ? "  └─ " : "  ├─ ");
            detail::print_syntax(std::cout, label);
            detail::print_syntax(std::cout, ": ");
            detail::print_value(std::cout, val);
            std::cout << "\n";
        };
        
        print_row("Tamaño (claves únicas)", size);
        if constexpr (is_numeric) {
            auto min_val = *std::begin(container);
            auto max_val = min_val;
            for (const auto& elem : container) {
                min_val = std::min(min_val, elem);
                max_val = std::max(max_val, elem);
            }
            print_row("Mínimo  ", min_val);
            print_row("Máximo  ", max_val);
            const long double promedio = suma / static_cast<long double>(size);
            print_row("Suma    ", suma);
            print_row("Promedio", promedio, true);
        } else {
            detail::print_syntax(std::cout, "  └─ Tipo no numérico\n");
        }
    }
}
