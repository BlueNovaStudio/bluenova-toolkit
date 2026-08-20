#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
    inline void cout_ascii(const std::string& name, const std::vector<int>& nums)
    {
        detail::print_name(std::cout, name);
        std::cout << ":\n";

        const double factor = 1.5;
        for (int num : nums)
        {
            std::cout << num << " ";
            const int blocks = static_cast<int>(std::round(num * factor));
            for (int index = 0; index < blocks; ++index)
                std::cout << "█";
            std::cout << "\n";
        }
    }

    inline void cout_ascii(const std::vector<int>& nums)
    {
        cout_ascii("ascii", nums);
    }
}