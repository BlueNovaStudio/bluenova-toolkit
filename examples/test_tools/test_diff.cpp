#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include "../include/tools/diff.hpp"

using namespace cpp_printer;

void example_diff_basic() {
    std::cout << "\n=== DIFF: Basic Examples ===\n";
    
    // Añadir elemento
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 3, 4};
    cout_diff("v1", v1, "v2", v2);
    
    // Eliminar elemento
    std::vector<int> v3 = {1, 2, 3, 4};
    std::vector<int> v4 = {1, 2, 3};
    cout_diff("v3", v3, "v4", v4);
    
    // Múltiples cambios
    std::vector<int> v5 = {1, 2, 3, 4, 5};
    std::vector<int> v6 = {1, 2, 4, 6, 7};
    cout_diff("v5", v5, "v6", v6);
    
    // Diferencias en posiciones intermedias
    std::vector<int> v7 = {1, 2, 3, 4, 5};
    std::vector<int> v8 = {1, 2, 3, 6, 7};
    cout_diff("v7", v7, "v8", v8);
}

void example_diff_maps() {
    std::cout << "\n=== DIFF: Maps ===\n";
    
    // Map con cambios de valores
    std::map<std::string, int> m1 = {{"a", 1}, {"b", 2}, {"c", 3}};
    std::map<std::string, int> m2 = {{"a", 1}, {"b", 5}, {"d", 4}};
    cout_diff("m1", m1, "m2", m2);
    
    // Map con adiciones y eliminaciones
    std::map<std::string, int> m3 = {{"a", 1}, {"b", 2}, {"c", 3}};
    std::map<std::string, int> m4 = {{"a", 1}, {"d", 4}, {"e", 5}};
    cout_diff("m3", m3, "m4", m4);
}

void example_diff_sets() {
    std::cout << "\n=== DIFF: Sets ===\n";
    
    // Set con diferencias
    std::set<int> s1 = {1, 2, 3, 4, 5};
    std::set<int> s2 = {1, 2, 4, 5, 6, 7};
    cout_diff("s1", s1, "s2", s2);
}

void example_diff_edge_cases() {
    std::cout << "\n=== DIFF: Edge Cases ===\n";
    
    // Ambos vacíos
    std::vector<int> e1, e2;
    cout_diff(e1, e2);
    
    // Uno vacío
    std::vector<int> e3 = {1, 2, 3};
    std::vector<int> e4;
    cout_diff("con_elementos", e3, "vacio", e4);
    
    // Con strings
    std::vector<std::string> s1 = {"apple", "banana", "cherry"};
    std::vector<std::string> s2 = {"apple", "banana", "date", "elderberry"};
    cout_diff(s1, s2);
}

int main() {
    example_diff_basic();
    example_diff_maps();
    example_diff_sets();
    example_diff_edge_cases();
    return 0;
}