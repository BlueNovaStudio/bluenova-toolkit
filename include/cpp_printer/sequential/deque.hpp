#pragma once

#include <iostream>
#include <string>
#include <deque>
#include "cpp_printer/detail/print_range.hpp"
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    template <typename T>
    void cout_deque(const std::string& name_deque, const std::deque<T>& container)
    {
        detail::print_name(std::cout, name_deque);
        detail::print_syntax(std::cout, " = {");
        detail::print_range(std::cout, container.begin(), container.end(),
            [](auto& output, const auto& element) { detail::print_value(output, element); });
        detail::print_syntax(std::cout, "}\n");
    }
}
