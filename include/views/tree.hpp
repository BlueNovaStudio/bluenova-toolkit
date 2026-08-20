#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <type_traits>
#include <iterator>
#include <utility>
#include <map>
#include <vector>
#include "cpp_printer/detail/print_format.hpp"
#include "cpp_printer/detail/type_traits.hpp"

namespace cpp_printer
{
    namespace detail
    {
        // Trait para identificar std::pair (usado en std::map / std::unordered_map)
        template <typename T>
        struct is_pair : std::false_type {};

        template <typename T1, typename T2>
        struct is_pair<std::pair<T1, T2>> : std::true_type {};

        template <typename T>
        inline constexpr bool is_pair_v = is_pair<remove_cvref_t<T>>::value;

        // Trait para identificar contenedores iterables (excluyendo strings y mapas)
        template <typename T, typename = void>
        struct is_container : std::false_type {};

        template <typename T>
        struct is_container<T, std::void_t<
            decltype(std::begin(std::declval<T>())),
            decltype(std::end(std::declval<T>()))
        >> : std::integral_constant<bool,
            !std::is_same_v<remove_cvref_t<T>, std::string> &&
            !std::is_same_v<remove_cvref_t<T>, const char*> &&
            !std::is_same_v<remove_cvref_t<T>, char*> &&
            !is_map_like_v<T>  // Los mapas se manejan por separado
        > {};

        template <typename T>
        inline constexpr bool is_container_v = is_container<T>::value;

        // Trait para detectar si un tipo es "hoja" (no contenedor)
        template <typename T>
        struct is_leaf : std::integral_constant<bool,
            !is_container_v<T> &&
            !is_map_like_v<T> &&
            !is_pair_v<T>
        > {};

        template <typename T>
        inline constexpr bool is_leaf_v = is_leaf<T>::value;

        // Map keys are labels in a tree, so string keys are displayed without
        // the quotes used for regular values.
        template <typename T>
        void print_tree_key(std::ostream& os, const T& key)
        {
            if constexpr (std::is_same_v<remove_cvref_t<T>, std::string>) {
                os << key;
            } else {
                detail::print_value(os, key);
            }
        }

        template <typename Map>
        void print_map_like(std::ostream&, const Map&, const std::string&, bool);

        template <typename Container>
        void print_container(std::ostream&, const Container&, const std::string&, bool);

        // Versión mejorada de print_tree_node sin usar std::distance
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
                // Imprimir la clave
                print_tree_key(os, node.first);
                os << " → ";

                using ValueType = remove_cvref_t<decltype(node.second)>;
                
                // Verificar si el valor es un mapa
                if constexpr (is_map_like_v<ValueType>) {
                    os << "\n";
                    // Imprimir el mapa como subárbol
                    print_map_like(os, node.second, child_prefix, true);
                } else if constexpr (is_container_v<ValueType>) {
                    os << "\n";
                    // Imprimir el contenedor como subárbol
                    print_container(os, node.second, child_prefix, true);
                } else if constexpr (is_pair_v<ValueType>) {
                    // Si el valor es un par (mapa anidado de otro tipo)
                    os << "\n";
                    print_tree_node(os, node.second, child_prefix, true);
                } else {
                    // Valor hoja
                    detail::print_value(os, node.second);
                    os << "\n";
                }
            }
            // Caso B: Mapa (std::map, std::unordered_map)
            else if constexpr (is_map_like_v<RawT>)
            {
                print_map_like(os, node, prefix, is_last);
            }
            // Caso C: Contenedor (vector, list, deque, set, etc.)
            else if constexpr (is_container_v<RawT>)
            {
                print_container(os, node, prefix, is_last);
            }
            // Caso D: Elemento Hoja (int, string, char, etc.)
            else if constexpr (is_leaf_v<RawT>)
            {
                detail::print_value(os, node);
                os << "\n";
            }
            // Caso E: Fallback (cualquier otro tipo)
            else
            {
                detail::print_value(os, node);
                os << "\n";
            }
        }

        // Función especializada para imprimir mapas
        template <typename Map>
        void print_map_like(std::ostream& os, const Map& map, const std::string& prefix, bool is_last)
        {
            if (std::empty(map)) {
                detail::print_syntax(os, prefix.c_str());
                detail::print_syntax(os, is_last ? "└── " : "├── ");
                detail::print_syntax(os, "[mapa vacío]\n");
                return;
            }

            auto it = map.begin();
            const auto end = map.end();
            while (it != end) {
                const auto current = it++;
                print_tree_node(os, *current, prefix, it == end);
            }
        }

        // Función especializada para imprimir contenedores
        template <typename Container>
        void print_container(std::ostream& os, const Container& container, const std::string& prefix, bool is_last)
        {
            if (std::empty(container)) {
                detail::print_syntax(os, prefix.c_str());
                detail::print_syntax(os, is_last ? "└── " : "├── ");
                detail::print_syntax(os, "[contenedor vacío]\n");
                return;
            }

            auto it = container.begin();
            const auto end = container.end();
            while (it != end) {
                const auto current = it++;
                const bool child_is_last = it == end;
                
                // Para contenedores de pares (como mapas de pares)
                using ElementType = remove_cvref_t<decltype(*current)>;
                if constexpr (is_pair_v<ElementType>) {
                    print_tree_node(os, *current, prefix, child_is_last);
                } else if constexpr (is_map_like_v<ElementType> || is_container_v<ElementType>) {
                    print_tree_node(os, *current, prefix, child_is_last);
                } else {
                    detail::print_syntax(os, prefix.c_str());
                    detail::print_syntax(os, child_is_last ? "└── " : "├── ");
                    detail::print_value(os, *current);
                    os << "\n";
                }
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

        // Detectar si es un mapa
        if constexpr (detail::is_map_like_v<Container>) {
            detail::print_map_like(std::cout, container, "", false);
        } else if constexpr (detail::is_container_v<Container>) {
            detail::print_container(std::cout, container, "", false);
        } else {
            // Caso de un solo elemento (no contenedor)
            detail::print_tree_node(std::cout, container, "", true);
        }
    }

    // Sobrecarga que usa "root" por defecto si no se pasa nombre
    template <typename Container>
    void cout_tree(const Container& container)
    {
        cout_tree("root", container);
    }
}
