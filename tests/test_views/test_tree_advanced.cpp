#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>
#include <variant>
#include <cassert>
#include <cctype>
#include "../include/views/tree.hpp"

using namespace cpp_printer;

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

void test_tree_simple_vector() {
    std::cout << "Testing tree with simple vector... ";
    std::vector<int> v = {1, 2, 3, 4};
    auto output = capture_output([&]() { cout_tree("test", v); });
    assert(output.find("test") != std::string::npos);
    assert(output.find("├── 1") != std::string::npos);
    assert(output.find("├── 2") != std::string::npos);
    assert(output.find("├── 3") != std::string::npos);
    assert(output.find("└── 4") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_tree_nested_vector() {
    std::cout << "Testing tree with nested vector... ";
    std::vector<std::vector<int>> v = {{1, 2}, {3, 4, 5}, {6}};
    auto output = capture_output([&]() { cout_tree("test", v); });
    assert(output.find("1") != std::string::npos);
    assert(output.find("2") != std::string::npos);
    assert(output.find("3") != std::string::npos);
    assert(output.find("4") != std::string::npos);
    assert(output.find("5") != std::string::npos);
    assert(output.find("6") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_tree_simple_map() {
    std::cout << "Testing tree with simple map... ";
    std::map<std::string, int> m = {{"apple", 5}, {"banana", 3}, {"cherry", 8}};
    auto output = capture_output([&]() { cout_tree("test", m); });
    assert(output.find("apple → 5") != std::string::npos);
    assert(output.find("banana → 3") != std::string::npos);
    assert(output.find("cherry → 8") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_tree_map_with_vector() {
    std::cout << "Testing tree with map of vectors... ";
    std::map<std::string, std::vector<int>> m = {
        {"even", {2, 4, 6, 8}},
        {"odd", {1, 3, 5, 7}}
    };
    auto output = capture_output([&]() { cout_tree("test", m); });
    assert(output.find("even →") != std::string::npos);
    assert(output.find("├── 2") != std::string::npos);
    assert(output.find("├── 4") != std::string::npos);
    assert(output.find("├── 6") != std::string::npos);
    assert(output.find("└── 8") != std::string::npos);
    assert(output.find("odd →") != std::string::npos);
    assert(output.find("├── 1") != std::string::npos);
    assert(output.find("├── 3") != std::string::npos);
    assert(output.find("├── 5") != std::string::npos);
    assert(output.find("└── 7") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_tree_nested_map() {
    std::cout << "Testing tree with nested map... ";
    std::map<std::string, std::map<std::string, int>> m = {
        {"person1", {{"age", 25}, {"height", 175}}},
        {"person2", {{"age", 30}, {"height", 180}}}
    };
    auto output = capture_output([&]() { cout_tree("test", m); });
    assert(output.find("person1 →") != std::string::npos);
    assert(output.find("├── age → 25") != std::string::npos);
    assert(output.find("└── height → 175") != std::string::npos);
    assert(output.find("person2 →") != std::string::npos);
    assert(output.find("├── age → 30") != std::string::npos);
    assert(output.find("└── height → 180") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_tree_deep_nested() {
    std::cout << "Testing tree with deeply nested structure... ";
    std::map<std::string, std::map<std::string, std::map<std::string, int>>> m = {
        {"level1", {
            {"level2", {
                {"level3_value", 42}
            }}
        }}
    };
    auto output = capture_output([&]() { cout_tree("test", m); });
    assert(output.find("level1 →") != std::string::npos);
    assert(output.find("level2 →") != std::string::npos);
    assert(output.find("level3_value → 42") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_tree_empty_structures() {
    std::cout << "Testing tree with empty structures... ";
    std::vector<int> empty_vec;
    std::map<std::string, int> empty_map;
    std::map<std::string, std::vector<int>> empty_nested;
    
    auto output1 = capture_output([&]() { cout_tree("empty_vec", empty_vec); });
    assert(output1.find("[vacío]") != std::string::npos);
    
    auto output2 = capture_output([&]() { cout_tree("empty_map", empty_map); });
    assert(output2.find("[vacío]") != std::string::npos);
    
    auto output3 = capture_output([&]() { cout_tree("empty_nested", empty_nested); });
    assert(output3.find("[vacío]") != std::string::npos);
    
    std::cout << "PASSED\n";
}

void test_tree_set() {
    std::cout << "Testing tree with set... ";
    std::set<std::string> s = {"alpha", "beta", "gamma"};
    auto output = capture_output([&]() { cout_tree("test", s); });
    assert(output.find("├── \"alpha\"") != std::string::npos);
    assert(output.find("├── \"beta\"") != std::string::npos);
    assert(output.find("└── \"gamma\"") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_tree_unordered_map() {
    std::cout << "Testing tree with unordered_map... ";
    std::unordered_map<std::string, std::vector<std::string>> m = {
        {"fruits", {"apple", "banana", "cherry"}},
        {"vegetables", {"carrot", "broccoli"}}
    };
    auto output = capture_output([&]() { cout_tree("test", m); });
    // Verificar que contiene los elementos (el orden puede variar)
    assert(output.find("fruits →") != std::string::npos || output.find("vegetables →") != std::string::npos);
    assert(output.find("apple") != std::string::npos);
    assert(output.find("banana") != std::string::npos);
    assert(output.find("cherry") != std::string::npos);
    assert(output.find("carrot") != std::string::npos);
    assert(output.find("broccoli") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_tree_mixed_types() {
    std::cout << "Testing tree with mixed types... ";
    std::map<std::string, std::vector<std::variant<int, std::string, double>>> m = {
        {"mixed", {42, "hello", 3.14}}
    };
    auto output = capture_output([&]() { cout_tree("test", m); });
    assert(output.find("mixed →") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_tree_list() {
    std::cout << "Testing tree with list... ";
    std::list<int> lst = {10, 20, 30, 40, 50};
    auto output = capture_output([&]() { cout_tree("test", lst); });
    assert(output.find("├── 10") != std::string::npos);
    assert(output.find("├── 20") != std::string::npos);
    assert(output.find("├── 30") != std::string::npos);
    assert(output.find("├── 40") != std::string::npos);
    assert(output.find("└── 50") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_tree_deque() {
    std::cout << "Testing tree with deque... ";
    std::deque<int> dq = {1, 2, 3, 4};
    auto output = capture_output([&]() { cout_tree("test", dq); });
    assert(output.find("├── 1") != std::string::npos);
    assert(output.find("├── 2") != std::string::npos);
    assert(output.find("├── 3") != std::string::npos);
    assert(output.find("└── 4") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_tree_complex_map_vector() {
    std::cout << "Testing tree with complex map of vectors... ";
    std::map<std::string, std::map<std::string, std::vector<int>>> m = {
        {"group1", {
            {"scores", {95, 87, 92}},
            {"grades", {1, 2, 3}}
        }},
        {"group2", {
            {"scores", {78, 82, 90}}
        }}
    };
    auto output = capture_output([&]() { cout_tree("test", m); });
    assert(output.find("group1 →") != std::string::npos);
    assert(output.find("group2 →") != std::string::npos);
    assert(output.find("scores →") != std::string::npos);
    assert(output.find("grades →") != std::string::npos);
    assert(output.find("95") != std::string::npos);
    assert(output.find("87") != std::string::npos);
    assert(output.find("92") != std::string::npos);
    assert(output.find("78") != std::string::npos);
    assert(output.find("82") != std::string::npos);
    assert(output.find("90") != std::string::npos);
    std::cout << "PASSED\n";
}

void run_all_tests() {
    std::cout << "\n=== Running Tree Advanced Tests ===\n\n";
    test_tree_simple_vector();
    test_tree_nested_vector();
    test_tree_simple_map();
    test_tree_map_with_vector();
    test_tree_nested_map();
    test_tree_deep_nested();
    test_tree_empty_structures();
    test_tree_set();
    test_tree_unordered_map();
    test_tree_mixed_types();
    test_tree_list();
    test_tree_deque();
    test_tree_complex_map_vector();
    std::cout << "\n✓ All tree tests passed!\n";
}

int main() {
    run_all_tests();
    return 0;
}