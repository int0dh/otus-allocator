#include <iostream>
#include <memory>
#include <map>
#include <cmath>

#include "my_allocator.hpp"
#include "my_container.hpp"

int main() {

	std::map<int, int> standardMap;
	std::map<int, int, std::less<int>,
		my_allocator<std::pair<const int, int>>> myallocMap;

	auto values = {1, 4, 5, 2, 9, 6, 8, 4, 2, 1 };

	for (auto &v : values) {
		standardMap[v] = std::tgamma(v + 1);
		myallocMap[v] = std::tgamma(v + 1);
	}

	std::cout << "standard map" << std::endl;
	for (auto &[k, v] : standardMap) {
		std::cout << k << " " << v << std::endl;
	}
	std::cout << "my alloc map" << std::endl;
	for (auto &[k, v] : myallocMap) {
		std::cout << k << " " << v << std::endl;
	}

	my_container<int, my_allocator<int, 10>> myContainer = {values};

	std::cout << "printing out content of values " << std::endl;
	for (auto & v : values) {
		std::cout << " " << v;
	}
	std::cout << std::endl;
	std::cout << "printing out content of my container" << std::endl;

	for (auto &v : myContainer) {
		std::cout << " " << v;
	}
	std::cout << std::endl;
	return 0;
}
