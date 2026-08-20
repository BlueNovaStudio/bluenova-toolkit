#pragma once

#include <iostream>
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer::detail
{
    template <typename Iterator, typename PrintElement>
    void print_range(std::ostream& output, Iterator begin, Iterator end, PrintElement print_element)
    {
        bool first = true;
        for (auto current = begin; current != end; ++current)
        {
            if (!first)
                print_syntax(output, ", ");

            print_element(output, *current);
            first = false;
        }
    }
}
