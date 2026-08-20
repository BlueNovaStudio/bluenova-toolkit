#include <vector>

#include "views/ascii.hpp"

int main()
{
	const std::vector<int> values{5, 3, 8, 2};
	cpp_printer::cout_ascii("values", values);
	return 0;
}
