#pragma once

#include <iostream>
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer::detail
{
    template <typename Container, typename GetElement>
    void print_pop_container(Container container, GetElement get_element)
    {
        bool first = true;
        while (!container.empty())
        {
            if (!first)
                print_syntax(std::cout, ", ");

            print_value(std::cout, get_element(container));
            container.pop();
            first = false;
        }
    }
}
