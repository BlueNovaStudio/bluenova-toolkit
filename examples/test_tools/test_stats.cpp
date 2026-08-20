#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <map>
#include <set>
#include "../include/tools/stats.hpp"

using namespace cpp_printer;

void example_stats_basic() {
    std::cout << "\n=== STATS: Basic Examples ===\n";
    
    // Vector de enteros
    std::vector<int> nums = {1, 4, 6, 2, 8, 3, 7, 5};
    cout_stats("vector_enteros", nums);
    
    // Vector de flotantes
    std::vector<double> floats = {1.5, 2.3, 0.8, 4.1, 3.7};
    cout_stats("vector_flotantes", floats);
    
    // Lista
    std::list<int> lst = {10, 20, 30, 40, 50};
    cout_stats("lista", lst);
    
    // Deque
    std::deque<int> dq = {5, 3, 8, 1, 9};
    cout_stats("deque", dq);
}

void example_stats_edge_cases() {
    std::cout << "\n=== STATS: Edge Cases ===\n";
    
    // Contenedor vacío
    std::vector<int> empty;
    cout_stats("vacio", empty);
    
    // Un solo elemento
    std::vector<int> single = {42};
    cout_stats("un_elemento", single);
    
    // Números negativos
    std::vector<int> negative = {-5, -3, -8, -1};
    cout_stats("negativos", negative);
    
    // Mezcla de positivos y negativos
    std::vector<int> mixed = {-5, 3, 8, -2, 10};
    cout_stats("mixtos", mixed);
    
    // Todos iguales
    std::vector<int> equal = {7, 7, 7, 7, 7};
    cout_stats("iguales", equal);
}

void example_stats_sets_maps() {
    std::cout << "\n=== STATS: Sets and Maps ===\n";
    
    // Set
    std::set<int> s = {1, 4, 6, 2, 8, 3};
    cout_stats("set_enteros", s);
    
    // Map (solo claves)
    std::map<std::string, int> m = {{"a", 1}, {"b", 4}, {"c", 6}, {"d", 2}};
    cout_stats("map_enteros", m);
    
    // Unordered map
    std::unordered_map<int, double> um = {{1, 1.5}, {2, 2.3}, {3, 0.8}};
    cout_stats("unordered_map", um);
}

int main() {
    example_stats_basic();
    example_stats_edge_cases();
    example_stats_sets_maps();
    return 0;
}