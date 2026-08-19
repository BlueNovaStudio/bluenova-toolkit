#pragma once

#include <iostream>
#include <string>
#include <queue>
#include "cpp_printer/detail/print_pop_container.hpp"
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    template <typename T, typename Container>
    void cout_queue(const std::string& name_queue, std::queue<T, Container> container)
    {
        detail::print_name(std::cout, name_queue);
        detail::print_syntax(std::cout, " = {");
        detail::print_pop_container(container, [](const auto& current) {
            return current.front();
        });
        detail::print_syntax(std::cout, "}\n");
    }
}
