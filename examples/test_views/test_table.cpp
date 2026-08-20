#include <vector>

#include "views/table.hpp"

int main()
{
	const std::vector<std::vector<int>> matrix{{1, 2}, {3, 4}};
	cpp_printer::cout_table("matrix", matrix);
	return 0;
}
