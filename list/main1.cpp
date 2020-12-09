#include <iostream>

int main() {
	unsigned char uc = 128;
	uc *= 2;
	// std::cout << static_cast<int>(uc) << std::endl;
	for (unsigned char q = 0; q < uc * 2; q++)
		std::cout << q << std::endl;
}