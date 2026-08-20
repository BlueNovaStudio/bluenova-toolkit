#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cassert>
#include <cctype>
#include "../include/tools/diff.hpp"

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

void test_diff_added_element() {
    std::cout << "Testing diff with added element... ";
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 3, 4};
    auto output = capture_output([&]() { cout_diff(v1, v2); });
    assert(output.find("+ 4") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_diff_removed_element() {
    std::cout << "Testing diff with removed element... ";
    std::vector<int> v1 = {1, 2, 3, 4};
    std::vector<int> v2 = {1, 2, 3};
    auto output = capture_output([&]() { cout_diff(v1, v2); });
    assert(output.find("- 4") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_diff_multiple_changes() {
    std::cout << "Testing diff with multiple changes... ";
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 4, 6, 7};
    auto output = capture_output([&]() { cout_diff(v1, v2); });
    assert(output.find("- 3") != std::string::npos);
    assert(output.find("+ 4") != std::string::npos);
    assert(output.find("- 4") != std::string::npos);
    assert(output.find("+ 6") != std::string::npos);
    assert(output.find("- 5") != std::string::npos);
    assert(output.find("+ 7") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_diff_map_value_change() {
    std::cout << "Testing diff with map value change... ";
    std::map<std::string, int> m1 = {{"a", 1}, {"b", 2}, {"c", 3}};
    std::map<std::string, int> m2 = {{"a", 1}, {"b", 5}, {"d", 4}};
    auto output = capture_output([&]() { cout_diff("m1", m1, "m2", m2); });
    assert(output.find("\"b\": 2 → 5") != std::string::npos);
    assert(output.find("- \"c\" → 3") != std::string::npos);
    assert(output.find("+ \"d\" → 4") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_diff_set_differences() {
    std::cout << "Testing diff with set differences... ";
    std::set<int> s1 = {1, 2, 3, 4, 5};
    std::set<int> s2 = {1, 2, 4, 5, 6};
    auto output = capture_output([&]() { cout_diff(s1, s2); });
    assert(output.find("- 3") != std::string::npos);
    assert(output.find("+ 6") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_diff_empty_both() {
    std::cout << "Testing diff with both empty... ";
    std::vector<int> e1, e2;
    auto output = capture_output([&]() { cout_diff(e1, e2); });
    assert(output.find("Ambos contenedores están vacíos") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_diff_one_empty() {
    std::cout << "Testing diff with one empty... ";
    std::vector<int> v = {1, 2, 3};
    std::vector<int> e;
    auto output = capture_output([&]() { cout_diff("v", v, "e", e); });
    assert(output.find("- 1") != std::string::npos);
    assert(output.find("- 2") != std::string::npos);
    assert(output.find("- 3") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_diff_strings() {
    std::cout << "Testing diff with strings... ";
    std::vector<std::string> s1 = {"apple", "banana", "cherry"};
    std::vector<std::string> s2 = {"apple", "banana", "date"};
    auto output = capture_output([&]() { cout_diff(s1, s2); });
    assert(output.find("- \"cherry\"") != std::string::npos);
    assert(output.find("+ \"date\"") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_diff_identical() {
    std::cout << "Testing diff with identical containers... ";
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 3, 4, 5};
    auto output = capture_output([&]() { cout_diff(v1, v2); });
    assert(output.find("Las estructuras son idénticas") != std::string::npos);
    std::cout << "PASSED\n";
}

void run_all_tests() {
    std::cout << "\n=== Running Diff Advanced Tests ===\n\n";
    test_diff_added_element();
    test_diff_removed_element();
    test_diff_multiple_changes();
    test_diff_map_value_change();
    test_diff_set_differences();
    test_diff_empty_both();
    test_diff_one_empty();
    test_diff_strings();
    test_diff_identical();
    std::cout << "\n✓ All diff tests passed!\n";
}

int main() {
    run_all_tests();
    return 0;
}