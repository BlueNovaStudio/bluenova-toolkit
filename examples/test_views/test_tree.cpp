#include <vector>

#include "views/tree.hpp"

int main()
{
	const std::vector<int> values{1, 2, 3};
	cpp_printer::cout_tree("values", values);
	return 0;
}
