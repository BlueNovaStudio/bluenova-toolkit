#pragma once

#include <string>
#include <iostream>
#include <forward_list>
#include "cpp_printer/detail/print_range.hpp"
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    template <typename T>
    void cout_list(const std::string& name_list, const std::forward_list<T>& container)
    {
        detail::print_name(std::cout, name_list);
        detail::print_syntax(std::cout, " = {");
        detail::print_range(std::cout, container.begin(), container.end(),
            [](auto& output, const auto& element) { detail::print_value(output, element); });
        detail::print_syntax(std::cout, "}\n");
    }
}
