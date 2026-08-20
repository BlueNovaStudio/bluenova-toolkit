#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <map>
#include <string>
#include <cassert>
#include <cctype>
#include "../include/views/table.hpp"

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

void test_table_empty_matrix() {
    std::cout << "Testing table with empty matrix... ";
    std::vector<std::vector<int>> empty;
    auto output = capture_output([&]() { cout_table("test", empty); });
    assert(output.find("tabla vacía") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_table_empty_rows() {
    std::cout << "Testing table with empty rows... ";
    std::vector<std::vector<int>> matrix = {{}, {1, 2}, {}};
    auto output = capture_output([&]() { cout_table("test", matrix); });
    assert(output.find("tabla con filas vacías") == std::string::npos);
    assert(output.find("│ 1 │ 2 │") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_table_single_element() {
    std::cout << "Testing table with single element... ";
    std::vector<std::vector<int>> matrix = {{42}};
    auto output = capture_output([&]() { cout_table("test", matrix); });
    assert(output.find("│ 42 │") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_table_2x2() {
    std::cout << "Testing table with 2x2 matrix... ";
    std::vector<std::vector<int>> matrix = {{1, 2}, {3, 4}};
    auto output = capture_output([&]() { cout_table("test", matrix); });
    assert(output.find("│ 1 │ 2 │") != std::string::npos);
    assert(output.find("│ 3 │ 4 │") != std::string::npos);
    assert(output.find("┌───┬───┐") != std::string::npos);
    assert(output.find("├───┼───┤") != std::string::npos);
    assert(output.find("└───┴───┘") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_table_irregular() {
    std::cout << "Testing table with irregular matrix... ";
    std::vector<std::vector<int>> matrix = {{1}, {2, 3, 4}, {5, 6}};
    auto output = capture_output([&]() { cout_table("test", matrix); });
    assert(output.find("│ 1 │   │   │") != std::string::npos);
    assert(output.find("│ 2 │ 3 │ 4 │") != std::string::npos);
    assert(output.find("│ 5 │ 6 │   │") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_table_strings() {
    std::cout << "Testing table with strings... ";
    std::vector<std::vector<std::string>> matrix = {
        {"hello", "x"},
        {"a", "very long value"}
    };
    auto output = capture_output([&]() { cout_table("test", matrix); });
    assert(output.find("\"hello\"") != std::string::npos);
    assert(output.find("\"very long value\"") != std::string::npos);
    // Verificar que los anchos de columna se ajustan correctamente
    std::cout << "PASSED\n";
}

void test_table_characters() {
    std::cout << "Testing table with characters... ";
    std::vector<std::vector<char>> matrix = {{'a', 'b'}, {'c', 'd'}};
    auto output = capture_output([&]() { cout_table("test", matrix); });
    assert(output.find("'a'") != std::string::npos);
    assert(output.find("'b'") != std::string::npos);
    assert(output.find("'c'") != std::string::npos);
    assert(output.find("'d'") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_table_negative_numbers() {
    std::cout << "Testing table with negative numbers... ";
    std::vector<std::vector<int>> matrix = {{-5, 3}, {-8, -1}};
    auto output = capture_output([&]() { cout_table("test", matrix); });
    assert(output.find("-5") != std::string::npos);
    assert(output.find("-8") != std::string::npos);
    assert(output.find("-1") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_table_c_strings() {
    std::cout << "Testing table with C strings... ";
    std::vector<std::vector<const char*>> matrix = {
        {"hello", "world"},
        {"foo", nullptr}
    };
    auto output = capture_output([&]() { cout_table("test", matrix); });
    assert(output.find("\"hello\"") != std::string::npos);
    assert(output.find("\"world\"") != std::string::npos);
    assert(output.find("\"foo\"") != std::string::npos);
    assert(output.find("null") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_table_bool() {
    std::cout << "Testing table with booleans... ";
    std::vector<std::vector<bool>> matrix = {{true, false}, {false, true}};
    auto output = capture_output([&]() { cout_table("test", matrix); });
    assert(output.find("true") != std::string::npos);
    assert(output.find("false") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_table_floats() {
    std::cout << "Testing table with floats... ";
    std::vector<std::vector<double>> matrix = {{1.5, 2.333}, {3.14159, 4.0}};
    auto output = capture_output([&]() { cout_table("test", matrix); });
    assert(output.find("1.50") != std::string::npos);
    assert(output.find("2.33") != std::string::npos);
    assert(output.find("3.14") != std::string::npos);
    assert(output.find("4.00") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_table_different_containers() {
    std::cout << "Testing table with different container types... ";
    std::vector<std::list<int>> matrix = {
        {1, 2},
        {3, 4, 5}
    };
    auto output = capture_output([&]() { cout_table("test", matrix); });
    assert(output.find("│ 1 │ 2 │   │") != std::string::npos);
    assert(output.find("│ 3 │ 4 │ 5 │") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_table_wide_content() {
    std::cout << "Testing table with very wide content... ";
    std::vector<std::vector<std::string>> matrix = {
        {"a", "b", "c"},
        {"very_very_very_long_word", "short", "medium"}
    };
    auto output = capture_output([&]() { cout_table("test", matrix); });
    assert(output.find("\"very_very_very_long_word\"") != std::string::npos);
    // Verificar que la tabla se ajusta correctamente
    std::cout << "PASSED\n";
}

void test_table_all_types_mixed() {
    std::cout << "Testing table with all types mixed... ";
    std::vector<std::vector<std::string>> matrix = {
        {"int", "float", "string", "bool"},
        {"42", "3.14", "hello", "true"},
        {"-5", "-2.5", "world", "false"}
    };
    auto output = capture_output([&]() { cout_table("test", matrix); });
    assert(output.find("int") != std::string::npos);
    assert(output.find("float") != std::string::npos);
    assert(output.find("string") != std::string::npos);
    assert(output.find("bool") != std::string::npos);
    assert(output.find("42") != std::string::npos);
    assert(output.find("3.14") != std::string::npos);
    assert(output.find("hello") != std::string::npos);
    assert(output.find("true") != std::string::npos);
    std::cout << "PASSED\n";
}

void run_all_tests() {
    std::cout << "\n=== Running Table Advanced Tests ===\n\n";
    test_table_empty_matrix();
    test_table_empty_rows();
    test_table_single_element();
    test_table_2x2();
    test_table_irregular();
    test_table_strings();
    test_table_characters();
    test_table_negative_numbers();
    test_table_c_strings();
    test_table_bool();
    test_table_floats();
    test_table_different_containers();
    test_table_wide_content();
    test_table_all_types_mixed();
    std::cout << "\n✓ All table tests passed!\n";
}

int main() {
    run_all_tests();
    return 0;
}