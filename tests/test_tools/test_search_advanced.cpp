#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "tools/search.hpp"

int main()
{
    const std::vector<std::string> values{"one", "two", "two"};
    std::ostringstream output;
    auto* original_buffer = std::cout.rdbuf(output.rdbuf());
    cpp_printer::cout_search("values", values, std::string{"two"});
    std::cout.rdbuf(original_buffer);

    const std::string text = output.str();
    assert(text.find("values") != std::string::npos);
    assert(text.find("two") != std::string::npos);
    assert(text.find("[1") != std::string::npos);
    assert(text.find("2]") != std::string::npos);
    return 0;
}
