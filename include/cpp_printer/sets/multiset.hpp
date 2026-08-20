#pragma once

#include <iostream>
#include <string>
#include <set>
#include "cpp_printer/detail/print_range.hpp"
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    template <typename T>
    void cout_multiset(const std::string& name_multiset, const std::multiset<T>& container)
    {
        detail::print_name(std::cout, name_multiset);
        detail::print_syntax(std::cout, " = [");
        detail::print_range(std::cout, container.begin(), container.end(),
            [](auto& output, const auto& element) { detail::print_value(output, element); });
        detail::print_syntax(std::cout, "]\n");
    }
}
