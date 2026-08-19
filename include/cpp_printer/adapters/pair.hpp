#pragma once

#include <iostream>
#include <string>
#include <utility>
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    template <typename Key, typename T>
    void cout_pair(const std::string& name_pair, const std::pair<Key, T>& container)
    {
        detail::print_name(std::cout, name_pair);
        detail::print_syntax(std::cout, " = {");
        detail::print_value(std::cout, container.first);
        detail::print_syntax(std::cout, ": ");
        detail::print_value(std::cout, container.second);
        detail::print_syntax(std::cout, "}\n");
    }
}