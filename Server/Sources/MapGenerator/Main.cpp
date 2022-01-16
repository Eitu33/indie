#include <iostream>
#include "MapGeneration.hpp"

int main()
{
	std::vector<std::string> map;
	MapGeneration gen(10, 10);

	gen.generateMap();
	map = gen.getMap();
	for (auto &elem : map)
		std::cout << elem <<std::endl;

	return 0;
}