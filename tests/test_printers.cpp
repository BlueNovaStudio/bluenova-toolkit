#include "cpp_printer/print.hpp"

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
		assert(without_ansi_colors(actual) == expected);
	}
}

int main()
{
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

	assert(queue_values.size() == 2);
	assert(stack_values.size() == 2);
	assert(priority_queue_values.size() == 2);

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
