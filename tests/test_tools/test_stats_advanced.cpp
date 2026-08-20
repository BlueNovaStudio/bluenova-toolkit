#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <cctype>
#include "../include/tools/stats.hpp"

using namespace cpp_printer;

struct HashOnlyKey {
    int id;
};

inline bool operator==(const HashOnlyKey& lhs, const HashOnlyKey& rhs) {
    return lhs.id == rhs.id;
}

struct HashOnlyKeyHash {
    std::size_t operator()(const HashOnlyKey& key) const noexcept {
        return std::hash<int>{}(key.id);
    }
};

// Helper para capturar salida
template<typename Func>
std::string capture_output(Func func) {
    std::streambuf* old = std::cout.rdbuf();
    std::ostringstream oss;
    std::cout.rdbuf(oss.rdbuf());
    func();
    std::cout.rdbuf(old);
    std::string result;
    const std::string colored = oss.str();
    for (std::size_t i = 0; i < colored.size(); ++i) {
        if (colored[i] == '\033' && i + 1 < colored.size() && colored[i + 1] == '[') {
            i += 2;
            while (i < colored.size() && !std::isalpha(static_cast<unsigned char>(colored[i]))) ++i;
            continue;
        }
        result += colored[i];
    }
    return result;
}

void test_stats_vector_int() {
    std::cout << "Testing stats with vector<int>... ";
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto output = capture_output([&]() { cout_stats("test", v); });
    assert(output.find("Tamaño  : 5") != std::string::npos);
    assert(output.find("Suma    : 15") != std::string::npos);
    assert(output.find("Promedio: 3") != std::string::npos);
    assert(output.find("Mínimo  : 1") != std::string::npos);
    assert(output.find("Máximo  : 5") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_stats_vector_double() {
    std::cout << "Testing stats with vector<double>... ";
    std::vector<double> v = {1.5, 2.3, 0.8, 4.1};
    auto output = capture_output([&]() { cout_stats("test", v); });
    assert(output.find("Tamaño  : 4") != std::string::npos);
    assert(output.find("Suma    : 8.7") != std::string::npos);
    assert(output.find("Promedio: 2.175") != std::string::npos);
    assert(output.find("Mínimo  : 0.8") != std::string::npos);
    assert(output.find("Máximo  : 4.1") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_stats_empty_container() {
    std::cout << "Testing stats with empty container... ";
    std::vector<int> empty;
    auto output = capture_output([&]() { cout_stats("test", empty); });
    assert(output.find("contenedor vacío") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_stats_single_element() {
    std::cout << "Testing stats with single element... ";
    std::vector<int> v = {42};
    auto output = capture_output([&]() { cout_stats("test", v); });
    assert(output.find("Tamaño  : 1") != std::string::npos);
    assert(output.find("Suma    : 42") != std::string::npos);
    assert(output.find("Promedio: 42") != std::string::npos);
    assert(output.find("Mínimo  : 42") != std::string::npos);
    assert(output.find("Máximo  : 42") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_stats_negative_numbers() {
    std::cout << "Testing stats with negative numbers... ";
    std::vector<int> v = {-5, -3, -8, -1};
    auto output = capture_output([&]() { cout_stats("test", v); });
    assert(output.find("Tamaño  : 4") != std::string::npos);
    assert(output.find("Suma    : -17") != std::string::npos);
    assert(output.find("Promedio: -4.25") != std::string::npos);
    assert(output.find("Mínimo  : -8") != std::string::npos);
    assert(output.find("Máximo  : -1") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_stats_mixed_signs() {
    std::cout << "Testing stats with mixed signs... ";
    std::vector<int> v = {-5, 3, 8, -2, 10};
    auto output = capture_output([&]() { cout_stats("test", v); });
    assert(output.find("Tamaño  : 5") != std::string::npos);
    assert(output.find("Suma    : 14") != std::string::npos);
    assert(output.find("Promedio: 2.8") != std::string::npos);
    assert(output.find("Mínimo  : -5") != std::string::npos);
    assert(output.find("Máximo  : 10") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_stats_list() {
    std::cout << "Testing stats with list... ";
    std::list<int> lst = {1, 2, 3, 4, 5};
    auto output = capture_output([&]() { cout_stats("test", lst); });
    assert(output.find("Tamaño  : 5") != std::string::npos);
    assert(output.find("Suma    : 15") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_stats_deque() {
    std::cout << "Testing stats with deque... ";
    std::deque<int> dq = {1, 2, 3, 4, 5};
    auto output = capture_output([&]() { cout_stats("test", dq); });
    assert(output.find("Tamaño  : 5") != std::string::npos);
    assert(output.find("Suma    : 15") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_stats_set() {
    std::cout << "Testing stats with set... ";
    std::set<int> s = {1, 2, 3, 4, 5};
    auto output = capture_output([&]() { cout_stats("test", s); });
    assert(output.find("Tamaño (claves únicas): 5") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_stats_map() {
    std::cout << "Testing stats with map (keys)... ";
    std::map<std::string, int> m = {{"a", 1}, {"b", 2}, {"c", 3}};
    auto output = capture_output([&]() { cout_stats("test", m); });
    // Para map, solo muestra tamaño (claves)
    assert(output.find("Tamaño (pares): 3") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_stats_unordered_map_with_hash_only_keys() {
    std::cout << "Testing stats with unordered map hash-only keys... ";
    std::unordered_map<HashOnlyKey, int, HashOnlyKeyHash> values = {{{1}, 10}, {{2}, 20}};
    auto output = capture_output([&]() { cout_stats("test", values); });
    assert(output.find("Tamaño (pares): 2") != std::string::npos);
    assert(output.find("Claves no ordenables numéricamente") != std::string::npos);
    assert(output.find("Promedio valor: 15") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_stats_all_equal() {
    std::cout << "Testing stats with all equal values... ";
    std::vector<int> v = {7, 7, 7, 7, 7};
    auto output = capture_output([&]() { cout_stats("test", v); });
    assert(output.find("Tamaño  : 5") != std::string::npos);
    assert(output.find("Suma    : 35") != std::string::npos);
    assert(output.find("Promedio: 7") != std::string::npos);
    assert(output.find("Mínimo  : 7") != std::string::npos);
    assert(output.find("Máximo  : 7") != std::string::npos);
    std::cout << "PASSED\n";
}

void run_all_tests() {
    std::cout << "\n=== Running Stats Advanced Tests ===\n\n";
    test_stats_vector_int();
    test_stats_vector_double();
    test_stats_empty_container();
    test_stats_single_element();
    test_stats_negative_numbers();
    test_stats_mixed_signs();
    test_stats_list();
    test_stats_deque();
    test_stats_set();
    test_stats_map();
    test_stats_unordered_map_with_hash_only_keys();
    test_stats_all_equal();
    std::cout << "\n✓ All stats tests passed!\n";
}

int main() {
    run_all_tests();
    return 0;
}
