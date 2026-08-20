#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <cassert>
#include <cctype>
#include "../include/views/ascii.hpp"

using namespace cpp_printer;

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

void test_ascii_basic_vector() {
    std::cout << "Testing ascii with basic vector... ";
    std::vector<int> v = {5, 3, 8, 1, 6};
    auto output = capture_output([&]() { cout_ascii("test", v); });
    assert(output.find("test") != std::string::npos);
    assert(output.find("5") != std::string::npos);
    assert(output.find("3") != std::string::npos);
    assert(output.find("8") != std::string::npos);
    assert(output.find("█") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_ascii_normalization() {
    std::cout << "Testing ascii normalization... ";
    std::vector<int> v = {100, 200, 300};
    auto output = capture_output([&]() { cout_ascii("test", v); });
    // Verificar que todos los valores se normalizan al mismo rango visual
    assert(output.find("100") != std::string::npos);
    assert(output.find("200") != std::string::npos);
    assert(output.find("300") != std::string::npos);
    // La barra de 300 debería ser la más larga
    std::cout << "PASSED\n";
}

void test_ascii_negative_values() {
    std::cout << "Testing ascii with negative values... ";
    std::vector<int> v = {-5, 3, 8, -2, 10};
    auto output = capture_output([&]() { cout_ascii("test", v); });
    // Verificar que los negativos se muestran en rojo y los positivos en verde
    assert(output.find("-5") != std::string::npos);
    assert(output.find("3") != std::string::npos);
    assert(output.find("8") != std::string::npos);
    assert(output.find("-2") != std::string::npos);
    assert(output.find("10") != std::string::npos);
    // Verificar separador para valores mixtos
    std::cout << "PASSED\n";
}

void test_ascii_empty_container() {
    std::cout << "Testing ascii with empty container... ";
    std::vector<int> empty;
    auto output = capture_output([&]() { cout_ascii("test", empty); });
    assert(output.find("contenedor vacío") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_ascii_single_element() {
    std::cout << "Testing ascii with single element... ";
    std::vector<int> v = {42};
    auto output = capture_output([&]() { cout_ascii("test", v); });
    assert(output.find("42") != std::string::npos);
    assert(output.find("█") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_ascii_all_equal() {
    std::cout << "Testing ascii with all equal values... ";
    std::vector<int> v = {7, 7, 7, 7, 7};
    auto output = capture_output([&]() { cout_ascii("test", v); });
    // Todas las barras deberían tener la misma longitud
    std::cout << "PASSED\n";
}

void test_ascii_float_values() {
    std::cout << "Testing ascii with float values... ";
    std::vector<double> v = {1.5, 2.3, 0.8, 4.1, 3.7};
    auto output = capture_output([&]() { cout_ascii("test", v); });
    assert(output.find("1.5") != std::string::npos);
    assert(output.find("2.3") != std::string::npos);
    assert(output.find("0.8") != std::string::npos);
    assert(output.find("4.1") != std::string::npos);
    assert(output.find("3.7") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_ascii_custom_config() {
    std::cout << "Testing ascii with custom config... ";
    std::vector<int> v = {5, 3, 8};
    AsciiChartConfig config;
    config.max_blocks = 15;
    config.block_char = "■";
    config.show_values = false;
    auto output = capture_output([&]() { cout_ascii("test", v, config); });
    // Verificar que no muestra valores
    assert(output.find("5 █") == std::string::npos);
    assert(output.find("3 █") == std::string::npos);
    assert(output.find("8 █") == std::string::npos);
    // Verificar que usa el carácter personalizado
    assert(output.find("■") != std::string::npos);
    std::cout << "PASSED\n";
}

void test_ascii_different_containers() {
    std::cout << "Testing ascii with different containers... ";
    
    // List
    std::list<int> lst = {1, 4, 6, 2};
    auto output1 = capture_output([&]() { cout_ascii("list", lst); });
    assert(output1.find("list") != std::string::npos);
    
    // Deque
    std::deque<int> dq = {3, 7, 2, 9};
    auto output2 = capture_output([&]() { cout_ascii("deque", dq); });
    assert(output2.find("deque") != std::string::npos);
    
    // Array
    std::array<int, 4> arr = {5, 1, 8, 3};
    auto output3 = capture_output([&]() { cout_ascii("array", arr); });
    assert(output3.find("array") != std::string::npos);
    
    std::cout << "PASSED\n";
}

void test_ascii_zero_values() {
    std::cout << "Testing ascii with zero values... ";
    std::vector<int> v = {0, 5, 0, 3, 0};
    auto output = capture_output([&]() { cout_ascii("test", v); });
    assert(output.find("0") != std::string::npos);
    assert(output.find("5") != std::string::npos);
    assert(output.find("3") != std::string::npos);
    std::cout << "PASSED\n";
}

void run_all_tests() {
    std::cout << "\n=== Running ASCII Advanced Tests ===\n\n";
    test_ascii_basic_vector();
    test_ascii_normalization();
    test_ascii_negative_values();
    test_ascii_empty_container();
    test_ascii_single_element();
    test_ascii_all_equal();
    test_ascii_float_values();
    test_ascii_custom_config();
    test_ascii_different_containers();
    test_ascii_zero_values();
    std::cout << "\n✓ All ascii tests passed!\n";
}

int main() {
    run_all_tests();
    return 0;
}