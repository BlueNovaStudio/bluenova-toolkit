#pragma once

#include <iostream>
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer::detail
{
    template <typename Container, typename GetElement>
    void print_pop_container(std::ostream& output, Container container, GetElement get_element)
    {
        bool first = true;
        while (!container.empty())
        {
            if (!first)
                print_syntax(output, ", ");

            print_value(output, get_element(container));
            container.pop();
            first = false;
        }
    }
}
