#pragma once

#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "cpp_printer/detail/print_pop_container.hpp"
#include "cpp_printer/detail/print_format.hpp"

namespace cpp_printer
{
	template <typename T,
			  typename Container = std::vector<T>,
			  typename Compare = std::less<T>>
	void cout_priority_queue(
		const std::string& name_priority_queue,
		std::priority_queue<T, Container, Compare> container)
	{
		detail::print_name(std::cout, name_priority_queue);
		detail::print_syntax(std::cout, " = {");
		detail::print_pop_container(std::cout, container, [](const auto& current) {
			return current.top();
		});
		detail::print_syntax(std::cout, "}\n");
	}
}
