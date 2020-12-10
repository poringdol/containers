#include <iostream>
#include "tests.hpp"

#define BW "\033[0;0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[1;33m"
#define PURPLE "\033[1;35m"

using namespace std;

int main() {
	
	while (1) {
		cout << YELLOW << "\nSelect tests to run" << BW << endl << endl;

		cout << YELLOW << "1. " << BLUE << "List" <<  BW <<endl;
		cout << YELLOW << "2. " << BLUE << "Vector" << BW << endl;
		cout << YELLOW << "3. " << BLUE << "Map" << BW << endl;
		cout << YELLOW << "4. " << BLUE << "Stack" << BW << endl;
		cout << YELLOW << "5. " << BLUE << "Queue" << BW << endl;
		cout << YELLOW << "6. " << BLUE << "All" << BW << endl;
		cout << YELLOW << "0. " << BLUE << "Exit" << BW << endl << endl;


		int index = 10;
		while (1) {
			cout << YELLOW << "Enter index: " << BW;
			std::cin >> index;
			if (std::cin.eof()) {
				std::cout << std::endl;
				exit(0);
			}
			if (!std::cin || index < 0 || index > 6) {
				cout << RED << "\nIncorrect input\n" << BW << endl;
				std::cin.clear();
				while (std::cin.get() != '\n');
			} else {
				std::cin.ignore();
				break;
			}
		}
		if (index == test::List) {
			list_test();
		} else if (index == test::Vector) {
			cout << RED << "In progress" << BW << endl;
		} else if (index == test::Map) {
			cout << RED << "In progress" << BW << endl;
		} else if (index == test::Stack) {
			cout << RED << "In progress" << BW << endl;
		} else if (index == test::Queue) {
			cout << RED << "In progress" << BW << endl;
		} else if (index == test::All) {
			cout << RED << "In progress" << BW << endl;
		} else
			exit(0);
	}

}