#include <iostream>
#include <list>

int main() {
	std::list<int> l1, l2;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);

	l2.push_back(1);
	l2.push_back(2);
	l2.push_back(3);
	l2.push_back(3);

	std::cout << (l1 > l2) << std::endl;
}