#pragma once

#include <iostream>
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer::detail
{
    template <typename Iterator, typename PrintElement>
    void print_range(Iterator begin, Iterator end, PrintElement print_element)
    {
        bool first = true;
        for (auto current = begin; current != end; ++current)
        {
            if (!first)
                print_syntax(std::cout, ", ");

            print_element(std::cout, *current);
            first = false;
        }
    }
}
