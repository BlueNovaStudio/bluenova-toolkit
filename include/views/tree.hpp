#pragma once

#include <iostream>
#include <string>
#include <type_traits>
#include <iterator>
#include <utility>
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    namespace detail
    {
        // Helper para remover const, volatile y referencias
        template <typename T>
        using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

        // Trait para identificar std::pair (usado en std::map / std::unordered_map)
        template <typename T>
        struct is_pair : std::false_type {};

        template <typename T1, typename T2>
        struct is_pair<std::pair<T1, T2>> : std::true_type {};

        template <typename T>
        inline constexpr bool is_pair_v = is_pair<remove_cvref_t<T>>::value;

        // Trait para identificar contenedores iterables (excluyendo strings)
        template <typename T, typename = void>
        struct is_container : std::false_type {};

        template <typename T>
        struct is_container<T, std::void_t<
            decltype(std::begin(std::declval<T>())),
            decltype(std::end(std::declval<T>()))
        >> : std::integral_constant<bool,
            !std::is_same_v<remove_cvref_t<T>, std::string> &&
            !std::is_same_v<remove_cvref_t<T>, const char*> &&
            !std::is_same_v<remove_cvref_t<T>, char*>
        > {};

        template <typename T>
        inline constexpr bool is_container_v = is_container<T>::value;

        // Imprime un nodo recursivamente manteniendo la sangría del árbol
        template <typename T>
        void print_tree_node(std::ostream& os, const T& node, const std::string& prefix, bool is_last)
        {
            detail::print_syntax(os, prefix.c_str());
            detail::print_syntax(os, is_last ? "└── " : "├── ");

            std::string child_prefix = prefix + (is_last ? "    " : "│   ");
            using RawT = remove_cvref_t<T>;

            // Caso A: Par Clave-Valor (ej. Map Entry)
            if constexpr (is_pair_v<RawT>)
            {
                detail::print_value(os, node.first);
                os << "\n";

                using ValueType = remove_cvref_t<decltype(node.second)>;
                if constexpr (is_container_v<ValueType>)
                {
                    auto it = std::begin(node.second);
                    auto end = std::end(node.second);
                    auto total = std::distance(it, end);
                    std::size_t current = 0;

                    for (; it != end; ++it, ++current)
                    {
                        bool child_is_last = (current == static_cast<std::size_t>(total - 1));
                        print_tree_node(os, *it, child_prefix, child_is_last);
                    }
                }
                else
                {
                    print_tree_node(os, node.second, child_prefix, true);
                }
            }
            // Caso B: Subcontenedor (ej. vector de vectores)
            else if constexpr (is_container_v<RawT>)
            {
                auto it = std::begin(node);
                auto end = std::end(node);
                auto total = std::distance(it, end);
                detail::print_syntax(os, "[\n");
                std::size_t current = 0;

                for (; it != end; ++it, ++current)
                {
                    bool child_is_last = (current == static_cast<std::size_t>(total - 1));
                    print_tree_node(os, *it, child_prefix, child_is_last);
                }
            }
            // Caso C: Elemento Hoja (int, string, char, etc.)
            else
            {
                detail::print_value(os, node);
                os << "\n";
            }
        }
    } // namespace detail

    // Función principal con nombre personalizado de raíz
    template <typename Container>
    void cout_tree(const std::string& name_structure, const Container& container)
    {
        detail::print_name(std::cout, name_structure);
        std::cout << "\n";

        if (std::empty(container))
        {
            detail::print_syntax(std::cout, "└── [vacío]\n");
            return;
        }

        auto it = std::begin(container);
        auto end = std::end(container);
        auto total = std::distance(it, end);
        std::size_t current = 0;

        for (; it != end; ++it, ++current)
        {
            bool is_last = (current == static_cast<std::size_t>(total - 1));
            detail::print_tree_node(std::cout, *it, "", is_last);
        }
    }

    // Sobrecarga que usa "root" por defecto si no se pasa nombre
    template <typename Container>
    void cout_tree(const Container& container)
    {
        cout_tree("root", container);
    }
} 