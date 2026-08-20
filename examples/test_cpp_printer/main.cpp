#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <cassert>

// Modulos de impresion de contenedores
#include "cpp_printer/sequential/vector.hpp"
#include "cpp_printer/maps/map.hpp"
#include "cpp_printer/adapters/stack.hpp"

void test_sequential_and_maps() {
    std::cout << "[RUNNING] test_sequential_and_maps...\n";
    
    std::vector<int> numbers = {10, 20, 30};
    std::map<std::string, int> scores = {{"Alice", 90}, {"Bob", 85}};

    // cpp_printer::print(numbers);
    // cpp_printer::print(scores);

    assert(!numbers.empty());
    assert(scores.size() == 2);
    std::cout << "[PASSED] test_sequential_and_maps\n\n";
}

void test_adapters() {
    std::cout << "[RUNNING] test_adapters...\n";

    std::stack<int> st;
    st.push(1);
    st.push(2);

    // cpp_printer::print(st);

    assert(st.size() == 2);
    std::cout << "[PASSED] test_adapters\n\n";
}

int main() {
    std::cout << "=== TEST SUITE: CPP_PRINTER ===\n\n";
    test_sequential_and_maps();
    test_adapters();
    std::cout << "All cpp_printer tests completed successfully!\n";
    return 0;
}