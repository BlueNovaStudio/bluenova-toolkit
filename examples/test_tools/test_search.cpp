#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "../include/tools/search.hpp"

using namespace cpp_printer;

void example_search_basic() {
    std::cout << "\n=== SEARCH: Basic Examples ===\n";
    
    // Búsqueda en vector
    std::vector<int> nums = {1, 4, 6, 2, 8, 3, 7, 5};
    cout_search(nums, 6);
    cout_search(nums, 10);
    
    // Búsqueda en strings
    std::vector<std::string> words = {"apple", "banana", "cherry", "date"};
    cout_search(words, "cherry");
    cout_search(words, "grape");
}

void example_search_custom_name() {
    std::cout << "\n=== SEARCH: Custom Names ===\n";
    
    std::vector<int> nums = {1, 4, 6, 2, 8, 3, 7, 5};
    cout_search("numeros", nums, 6);
}

void example_search_edge_cases() {
    std::cout << "\n=== SEARCH: Edge Cases ===\n";
    
    // Contenedor vacío
    std::vector<int> empty;
    cout_search(empty, 5);
    
    // Un solo elemento
    std::vector<int> single = {42};
    cout_search(single, 42);
    cout_search(single, 43);
    
    // Elementos duplicados
    std::vector<int> duplicates = {1, 2, 3, 2, 1, 2};
    cout_search(duplicates, 2);
    cout_search(duplicates, 4);
    
    // Diferentes tipos de contenedores
    std::list<int> lst = {10, 20, 30, 40};
    cout_search(lst, 30);
}

int main() {
    example_search_basic();
    example_search_custom_name();
    example_search_edge_cases();
    return 0;
}