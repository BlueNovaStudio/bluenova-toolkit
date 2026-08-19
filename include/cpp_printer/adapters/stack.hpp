#pragma once

#include <iostream>
#include <string>
#include <stack>
#include "cpp_printer/detail/print_pop_container.hpp"
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    template <typename T, typename Container>
    void cout_stack(const std::string& name_stack, std::stack<T, Container> container)
    {
        detail::print_name(std::cout, name_stack);
        detail::print_syntax(std::cout, " = {");
        detail::print_pop_container(container, [](const auto& current) {
            return current.top();
        });
        detail::print_syntax(std::cout, "}\n");
    }
}