#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "tools/compare.hpp"
#include "tools/search.hpp"
#include "tools/stats.hpp"

void test_stats_and_compare()
{
    std::cout << "[RUNNING] test_stats_and_compare...\n";

    std::vector<int> data = {1, 5, 10, 15, 20};
    cpp_printer::cout_stats("data", data);
    cpp_printer::cout_compare("data", data, "copy", data);

    assert(!data.empty());
    std::cout << "[PASSED] test_stats_and_compare\n\n";
}

void test_search_algorithms()
{
    std::cout << "[RUNNING] test_search_algorithms...\n";

    std::vector<std::string> items = {"apple", "banana", "cherry"};
    cpp_printer::cout_search("items", items, std::string{"banana"});

    assert(items.size() == 3);
    std::cout << "[PASSED] test_search_algorithms\n\n";
}

int main()
{
    std::cout << "=== TEST SUITE: TOOLS ===\n\n";
    test_stats_and_compare();
    test_search_algorithms();
    std::cout << "All tools tests completed successfully!\n";
    return 0;
}