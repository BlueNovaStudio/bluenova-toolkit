#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "cpp_printer/detail/print_range.hpp"
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    template <typename T>
    void cout_vector(const std::string& name_vector, const std::vector<T>& container) 
    {
        detail::print_name(std::cout, name_vector);
        detail::print_syntax(std::cout, " = {");
        detail::print_range(container.begin(), container.end(),
            [](auto& output, const auto& element) { detail::print_value(output, element); });
        detail::print_syntax(std::cout, "}\n");
    }   
}
