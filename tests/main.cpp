#include <iostream>
#include <cstdlib>
#include "tests.hpp"

#define BW "\033[0;0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[1;33m"
#define PURPLE "\033[1;35m"

using std::cin;
using std::cout;
using std::endl;

int ENABLE_LOGS = 0;

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
			cin >> index;
			if (cin.eof()) {
				cout << std::endl;
				exit(0);
			}
			if (!cin || index < 0 || index > 6) {
				cout << RED << "\nIncorrect input\n" << BW << endl;
				cin.clear();
				while (cin.get() != '\n');
			} else {
				cin.ignore();
				break;
			}
		}
		void (*last_test)() = NULL;
	
		if (index == ft::List) {

			last_test = ft_list::list_test;
			ft_list::list_test();
			
		} else if (index == ft::Vector) {

			last_test = ft_vector::vector_test;
			ft_vector::vector_test();

		} else if (index == ft::Map) {

			cout << RED << "In progress" << BW << endl;

		} else if (index == ft::Stack) {

			last_test = ft_stack::stack_test;
			ft_stack::stack_test();

		} else if (index == ft::Queue) {

			last_test = ft_queue::queue_test;
			ft_queue::queue_test();

		} else if (index == ft::All) {

			ft_list::list_test();
			ft_vector::vector_test();
			ft_stack::stack_test();
			ft_queue::queue_test();

		} else if (index == ft::Exit)
			exit(0);
		
		cout << endl;
		cout << YELLOW << "1. " << BLUE << "Relanch last test and show logs" <<  BW <<endl;
		cout << YELLOW << "2. " << BLUE << "Return to the test selection menu" << BW << endl;
		cout << YELLOW << "0. " << BLUE << "Exit" << BW << endl << endl;
		cin >> index;
		if (index == 1) {
			if (last_test == NULL) {
				cout << RED << "Displaying logs enable only in single test mode. Return to the main menu and select one test" << BW << endl;
			} else {
				ENABLE_LOGS = 1;
				last_test();
			}
		} else if (index == 2) {
			continue;
		} else if (index == 0)
			exit(0);

		cout << "\nEnter " << BLUE << "1" << BW << " to continue"
			 << " or " << BLUE << "0 " << BW << "to exit" << endl;
		index = 0;
		cin >> index;
		if (index == '0')
			break; 
	}
}
