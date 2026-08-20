#pragma once

#include <string>
#include <iostream>
#include <array>
#include "cpp_printer/detail/print_range.hpp"
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    template <typename T>
    void cout_array(const std::string& name_array, const T* arr, size_t size)
    {
        detail::print_name(std::cout, name_array);
        detail::print_syntax(std::cout, " = {");
        detail::print_range(std::cout, arr, arr + size,
            [](auto& output, const auto& element) { detail::print_value(output, element); });
        detail::print_syntax(std::cout, "}\n");
    }
}
