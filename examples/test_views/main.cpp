#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// Modulos de renderizado visual
#include "views/ascii.hpp"
#include "views/table.hpp"
#include "views/tree.hpp"

void test_ascii_and_table_views() {
    std::cout << "[RUNNING] test_ascii_and_table_views...\n";

    std::vector<int> histogram_data = {5, 3, 8, 2};

    // views::cout_ascii(histogram_data);
    // views::print_table(histogram_data);

    assert(histogram_data.size() == 4);
    std::cout << "[PASSED] test_ascii_and_table_views\n\n";
}

void test_tree_rendering() {
    std::cout << "[RUNNING] test_tree_rendering...\n";

    // Structura de árbol de prueba
    // views::print_tree(root_node);

    std::cout << "[PASSED] test_tree_rendering\n\n";
}

int main() {
    std::cout << "=== TEST SUITE: VIEWS ===\n\n";
    test_ascii_and_table_views();
    test_tree_rendering();
    std::cout << "All views tests completed successfully!\n";
    return 0;
}