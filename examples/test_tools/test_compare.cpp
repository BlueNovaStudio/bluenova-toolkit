#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>
#include "../include/tools/compare.hpp"

using namespace cpp_printer;

void example_compare_basic() {
    std::cout << "\n=== COMPARE: Basic Examples ===\n";
    
    // Vectores idénticos
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 3, 4, 5};
    cout_compare("v1", v1, "v2", v2);
    
    // Vectores con diferencias
    std::vector<int> v3 = {1, 2, 3, 4, 5};
    std::vector<int> v4 = {1, 2, 3, 6, 7};
    cout_compare("v3", v3, "v4", v4);
    
    // Vectores de diferentes tamaños
    std::vector<int> v5 = {1, 2, 3};
    std::vector<int> v6 = {1, 2, 3, 4, 5};
    cout_compare("v5", v5, "v6", v6);
}

void example_compare_maps() {
    std::cout << "\n=== COMPARE: Maps ===\n";
    
    // Maps idénticos
    std::map<std::string, int> m1 = {{"a", 1}, {"b", 2}, {"c", 3}};
    std::map<std::string, int> m2 = {{"a", 1}, {"b", 2}, {"c", 3}};
    cout_compare("m1", m1, "m2", m2);
    
    // Maps con diferencias
    std::map<std::string, int> m3 = {{"a", 1}, {"b", 2}, {"c", 3}};
    std::map<std::string, int> m4 = {{"a", 1}, {"b", 5}, {"d", 4}};
    cout_compare("m3", m3, "m4", m4);
}

void example_compare_sets() {
    std::cout << "\n=== COMPARE: Sets ===\n";
    
    // Sets idénticos
    std::set<int> s1 = {1, 2, 3, 4, 5};
    std::set<int> s2 = {1, 2, 3, 4, 5};
    cout_compare("s1", s1, "s2", s2);
    
    // Sets con diferencias
    std::set<int> s3 = {1, 2, 3, 4, 5};
    std::set<int> s4 = {1, 2, 4, 5, 6};
    cout_compare("s3", s3, "s4", s4);
}

void example_compare_mixed_types() {
    std::cout << "\n=== COMPARE: Mixed Types ===\n";
    
    // Vector vs Lista
    std::vector<int> vec = {1, 2, 3, 4};
    std::list<int> lst = {1, 2, 3, 4};
    cout_compare("vector", vec, "lista", lst);
    
    // List vs Vector (diferentes)
    std::list<int> lst2 = {1, 2, 3, 5};
    cout_compare("vector_original", vec, "lista_diferente", lst2);
}

void example_compare_strings() {
    std::cout << "\n=== COMPARE: Strings ===\n";
    
    std::vector<std::string> s1 = {"apple", "banana", "cherry"};
    std::vector<std::string> s2 = {"apple", "banana", "date"};
    cout_compare("s1", s1, "s2", s2);
}

int main() {
    example_compare_basic();
    example_compare_maps();
    example_compare_sets();
    example_compare_mixed_types();
    example_compare_strings();
    return 0;
}