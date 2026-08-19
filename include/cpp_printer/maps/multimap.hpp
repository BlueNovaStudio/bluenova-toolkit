#pragma once

#include <iostream>
#include <string>
#include <map>
#include "cpp_printer/detail/print_range.hpp"
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    template <typename Key, typename T>
    void cout_multimap(const std::string& name_multimap, const std::multimap<Key, T>& container)
    {
        detail::print_name(std::cout, name_multimap);
        detail::print_syntax(std::cout, " = {");
        detail::print_range(container.begin(), container.end(),
            [](auto& output, const auto& element) {
                detail::print_value(output, element.first);
                detail::print_syntax(output, ": ");
                detail::print_value(output, element.second);
            });
        detail::print_syntax(std::cout, "}\n");
    }
}
