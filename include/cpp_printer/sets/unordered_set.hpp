#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include "cpp_printer/detail/print_range.hpp"
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    template <typename T>
    void cout_unordered_set(const std::string& name_unordered_set, const std::unordered_set<T>& container)
    {
        detail::print_name(std::cout, name_unordered_set);
        detail::print_syntax(std::cout, " = [");
        detail::print_range(std::cout, container.begin(), container.end(),
            [](auto& output, const auto& element) { detail::print_value(output, element); });
        detail::print_syntax(std::cout, "]\n");
    }
}
