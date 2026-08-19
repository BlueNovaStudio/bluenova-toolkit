#include "cpp_printer/print.hpp"

#include <map>
#include <queue>
#include <string>
#include <vector>

int main()
{
	std::vector<int> numbers = {1, 2, 3};
	std::map<std::string, int> scores = {
		{"ana", 10},
		{"luis", 8}
	};

	std::queue<std::string> tasks;
	tasks.push("compile");
	tasks.push("print");

	cpp_printer::cout_vector("numbers", numbers);
	cpp_printer::cout_map("scores", scores);
	cpp_printer::cout_queue("tasks", tasks);

	return 0;
}
