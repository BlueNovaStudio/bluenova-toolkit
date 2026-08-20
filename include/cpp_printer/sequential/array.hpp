#pragma once

#include <string>
#include <iostream>
#include <array>
#include <cstddef>
#include "cpp_printer/detail/print_range.hpp"
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    template <typename T>
    void cout_array(const std::string& name_array, const T* arr, std::size_t size)
    {
        detail::print_name(std::cout, name_array);
        detail::print_syntax(std::cout, " = {");
        if (size == 0) {
            detail::print_syntax(std::cout, "}\n");
            return;
        }
        if (arr == nullptr) {
            detail::print_syntax(std::cout, "<puntero nulo>}\n");
            return;
        }
        detail::print_range(std::cout, arr, arr + size,
            [](auto& output, const auto& element) { detail::print_value(output, element); });
        detail::print_syntax(std::cout, "}\n");
    }

    template <typename T, std::size_t Size>
    void cout_array(const std::string& name_array, const std::array<T, Size>& array)
    {
        cout_array(name_array, array.data(), array.size());
    }
}
