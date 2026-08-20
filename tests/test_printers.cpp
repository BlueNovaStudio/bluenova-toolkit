#include <cassert>
#include <cctype>
#include <deque>
#include <forward_list>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "all.hpp"



namespace
{
    std::string capture_output(const std::function<void()>& printer)
    {
        std::ostringstream captured;
        auto* original_buffer = std::cout.rdbuf(captured.rdbuf());
        printer();
        std::cout.rdbuf(original_buffer);
        return captured.str();
    }

    std::string without_ansi_colors(const std::string& value)
    {
        std::string result;
        for (std::size_t index = 0; index < value.size(); ++index)
        {
            if (value[index] == '\033' && index + 1 < value.size() && value[index + 1] == '[')
            {
                index += 2;
                while (index < value.size() && !std::isalpha(static_cast<unsigned char>(value[index])))
                    ++index;
                continue;
            }

            result += value[index];
        }
        return result;
    }

    void assert_prints(const std::string& actual, const std::string& expected)
    {
        if (without_ansi_colors(actual) != expected)
        {
            std::cerr << "Actual:\n" << without_ansi_colors(actual)
                      << "Expected:\n" << expected;
        }
        assert(without_ansi_colors(actual) == expected);
    }
}

int main()
{
    // ==========================================
    // 1. DATOS DE PRUEBA
    // ==========================================
    int array_values[] = {1, 2};
    std::vector<int> vector_values{1, 2};
    std::forward_list<std::string> list_values{"uno", "dos"};
    std::deque<char> deque_values{'a', 'b'};
    std::set<int> set_values{1, 2};
    std::multiset<int> multiset_values{1, 1};
    std::unordered_set<int> unordered_set_values{1};
    std::map<std::string, int> map_values{{"total", 42}};
    std::multimap<std::string, int> multimap_values{{"total", 42}};
    std::unordered_map<std::string, int> unordered_map_values{{"total", 42}};

    std::queue<int> queue_values;
    queue_values.push(1);
    queue_values.push(2);

    std::stack<int> stack_values;
    stack_values.push(1);
    stack_values.push(2);

    std::priority_queue<int> priority_queue_values;
    priority_queue_values.push(1);
    priority_queue_values.push(2);

    // ==========================================
    // 2. PRUEBAS DE MÓDULO: CPP_PRINTER
    // ==========================================
    assert_prints(capture_output([&] {
        cpp_printer::cout_array("array", array_values, 2);
    }), "array = {1, 2}\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_vector("vector", vector_values);
    }), "vector = {1, 2}\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_list("list", list_values);
    }), "list = {\"uno\", \"dos\"}\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_deque("deque", deque_values);
    }), "deque = {'a', 'b'}\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_set("set", set_values);
    }), "set = [1, 2]\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_multiset("multiset", multiset_values);
    }), "multiset = [1, 1]\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_unordered_set("unordered_set", unordered_set_values);
    }), "unordered_set = [1]\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_map("map", map_values);
    }), "map = {\"total\": 42}\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_multimap("multimap", multimap_values);
    }), "multimap = {\"total\": 42}\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_unordered_map("unordered_map", unordered_map_values);
    }), "unordered_map = [\"total\": 42]\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_queue("queue", queue_values);
    }), "queue = {1, 2}\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_stack("stack", stack_values);
    }), "stack = {2, 1}\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_priority_queue("priority_queue", priority_queue_values);
    }), "priority_queue = {2, 1}\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_pair("pair", std::pair<std::string, char>{"key", 'x'});
    }), "pair = {\"key\": 'x'}\n");

    // Verificar que los adaptadores no destruyen su contenido
    assert(queue_values.size() == 2);
    assert(stack_values.size() == 2);
    assert(priority_queue_values.size() == 2);

    // ==========================================
    // 3. PRUEBAS DE MÓDULO: TOOLS
    // ==========================================
    std::vector<int> stats_data{5, 10, 15};
    assert_prints(capture_output([&] {
        cpp_printer::cout_stats("stats", stats_data);
    }), "stats (Estadísticas):\n"
        "  ├─ Tamaño  : 3\n"
        "  ├─ Suma    : 30\n"
        "  ├─ Promedio: 10\n"
        "  ├─ Mínimo  : 5\n"
        "  └─ Máximo  : 15\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_search("search", vector_values, 2);
    }), "search = {1, 2}\n"
        "  └─ Encontrado en índice(s): [1]\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_compare("left", vector_values, "right", vector_values);
    }), "left vs right:\n  Las estructuras son idénticas.\n");

    // ==========================================
    // 4. PRUEBAS DE MÓDULO: VIEWS
    // ==========================================
    std::vector<int> bar_data{5, 3, 8, 2};
    std::vector<std::vector<int>> table_data{{1, 42}};
    assert_prints(capture_output([&] {
        cpp_printer::cout_ascii("ascii", bar_data);
    }), "ascii:\n5 ████████\n3 █████\n8 ████████████\n2 ███\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_table("table", table_data);
    }), "table:\n┌───┬────┐\n│ 1 │ 42 │\n└───┴────┘\n");

    assert_prints(capture_output([&] {
        cpp_printer::cout_tree("tree", vector_values);
    }), "tree\n├── 1\n└── 2\n");

    // ==========================================
    // 5. PRUEBAS DE COLORES ANSI
    // ==========================================
    const auto colored_output = capture_output([&] {
        cpp_printer::cout_pair("pair", std::pair<std::string, char>{"key", 'x'});
    });
    assert(colored_output.find("\033[38;2;248;248;242m") != std::string::npos);
    assert(colored_output.find("\033[38;2;80;250;123m") != std::string::npos);

    const auto number_output = capture_output([&] {
        cpp_printer::cout_vector("numbers", vector_values);
    });
    assert(number_output.find("\033[38;2;189;147;249m") != std::string::npos);

    return 0;
}