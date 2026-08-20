#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cassert>
#include <cctype>
#include "../include/tools/compare.hpp"

using namespace cpp_printer;

struct HashOnlyKey {
    int id;
};

inline bool operator==(const HashOnlyKey& lhs, const HashOnlyKey& rhs) {
    return lhs.id == rhs.id;
}

inline std::ostream& operator<<(std::ostream& output, const HashOnlyKey& key) {
    return output << key.id;
}

struct HashOnlyKeyHash {
    std::size_t operator()(const HashOnlyKey& key) const noexcept {
        return std::hash<int>{}(key.id);
    }
};

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

void test_compare_identical_vectors() {
    std::cout << "Testing compare with identical vectors... ";
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 3, 4, 5};
    auto output = capture_output([&]() { cout_compare("v1", v1, "v2", v2); });
    assert(output.find("idénticas") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_compare_different_vectors() {
    std::cout << "Testing compare with different vectors... ";
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 3, 6, 7};
    auto output = capture_output([&]() { cout_compare("v1", v1, "v2", v2); });
    assert(output.find("!=") != std::string::npos);
    assert(output.find("[3] 4 != 6") != std::string::npos);
    assert(output.find("[4] 5 != 7") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_compare_different_sizes() {
    std::cout << "Testing compare with different sizes... ";
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 3, 4, 5};
    auto output = capture_output([&]() { cout_compare("v1", v1, "v2", v2); });
    assert(output.find("<ausente>") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_compare_identical_maps() {
    std::cout << "Testing compare with identical maps... ";
    std::map<std::string, int> m1 = {{"a", 1}, {"b", 2}, {"c", 3}};
    std::map<std::string, int> m2 = {{"a", 1}, {"b", 2}, {"c", 3}};
    auto output = capture_output([&]() { cout_compare("m1", m1, "m2", m2); });
    assert(output.find("idénticos") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_compare_different_maps() {
    std::cout << "Testing compare with different maps... ";
    std::map<std::string, int> m1 = {{"a", 1}, {"b", 2}, {"c", 3}};
    std::map<std::string, int> m2 = {{"a", 1}, {"b", 5}, {"d", 4}};
    auto output = capture_output([&]() { cout_compare("m1", m1, "m2", m2); });
    assert(output.find("\"b\": 2 != 5") != std::string::npos);
    assert(output.find("\"c\" != <ausente>") != std::string::npos);
    assert(output.find("<ausente> -> \"d\"") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_compare_identical_sets() {
    std::cout << "Testing compare with identical sets... ";
    std::set<int> s1 = {1, 2, 3, 4, 5};
    std::set<int> s2 = {1, 2, 3, 4, 5};
    auto output = capture_output([&]() { cout_compare("s1", s1, "s2", s2); });
    assert(output.find("idénticos") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_compare_different_sets() {
    std::cout << "Testing compare with different sets... ";
    std::set<int> s1 = {1, 2, 3, 4, 5};
    std::set<int> s2 = {1, 2, 4, 5, 6};
    auto output = capture_output([&]() { cout_compare("s1", s1, "s2", s2); });
    assert(output.find("3 <-> <ausente>") != std::string::npos);
    assert(output.find("<ausente> <-> 6") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_compare_mixed_types() {
    std::cout << "Testing compare with mixed types (vector vs list)... ";
    std::vector<int> vec = {1, 2, 3, 4};
    std::list<int> lst = {1, 2, 3, 4};
    auto output = capture_output([&]() { cout_compare("vec", vec, "lst", lst); });
    assert(output.find("idénticas") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_compare_strings() {
    std::cout << "Testing compare with strings... ";
    std::vector<std::string> s1 = {"apple", "banana", "cherry"};
    std::vector<std::string> s2 = {"apple", "banana", "date"};
    auto output = capture_output([&]() { cout_compare("s1", s1, "s2", s2); });
    assert(output.find("\"cherry\" != \"date\"") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_compare_empty_containers() {
    std::cout << "Testing compare with empty containers... ";
    std::vector<int> e1, e2;
    auto output = capture_output([&]() { cout_compare("e1", e1, "e2", e2); });
    assert(output.find("idénticas") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_compare_unordered_hash_only_keys() {
    std::cout << "Testing compare with unordered hash-only keys... ";
    std::unordered_map<HashOnlyKey, int, HashOnlyKeyHash> left = {{{1}, 10}, {{2}, 20}};
    std::unordered_map<HashOnlyKey, int, HashOnlyKeyHash> right = {{{1}, 10}, {{2}, 30}};
    auto output = capture_output([&]() { cout_compare("left", left, "right", right); });
    assert(output.find("2: 20 != 30") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_compare_unordered_multiset_multiplicity() {
    std::cout << "Testing compare with unordered multiset multiplicity... ";
    std::unordered_multiset<int> left = {1, 1, 2};
    std::unordered_multiset<int> right = {1, 2};
    auto output = capture_output([&]() { cout_compare("left", left, "right", right); });
    assert(output.find("1 <-> <ausente>") != std::string::npos);
    std::cout << "PASSED\n";
}

void run_all_tests() {
    std::cout << "\n=== Running Compare Advanced Tests ===\n\n";
    test_compare_identical_vectors();
    test_compare_different_vectors();
    test_compare_different_sizes();
    test_compare_identical_maps();
    test_compare_different_maps();
    test_compare_identical_sets();
    test_compare_different_sets();
    test_compare_mixed_types();
    test_compare_strings();
    test_compare_empty_containers();
    test_compare_unordered_hash_only_keys();
    test_compare_unordered_multiset_multiplicity();
    std::cout << "\n✓ All compare tests passed!\n";
}

int main() {
    run_all_tests();
    return 0;
}
