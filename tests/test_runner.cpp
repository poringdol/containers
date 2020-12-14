#include <list>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include "tests.hpp"
#include "test_runner.h"

void fillContainers() {
	fillCont(ls, 10);
	fillCont(vc, 12);
	fillCont(dq, 15);
}

namespace ft_list
{
	void list_test() {
		
		// fillContainers();

		TestRunner tr;

		std::cout << YELLOW 
				<< "\n####################################################\n";
		std::cout << "#                                                  #\n";
		std::cout << "#                   List tests                     #\n";
		std::cout << "#                                                  #\n";
		std::cout << "####################################################\n\n"
				<< BW;

		RUN_TEST(tr, constructorDefault_test);
		RUN_TEST(tr, constructorFill_test);
		RUN_TEST(tr, constructorRange_test);
		RUN_TEST(tr, size_test);
		RUN_TEST(tr, empty_test);
		RUN_TEST(tr, max_size_test);
		RUN_TEST(tr, begin_test);
		RUN_TEST(tr, rbegin_rend_test);
		RUN_TEST(tr, front_back_test);
		RUN_TEST(tr, assign_range_test);
		RUN_TEST(tr, assign_fill_test);
		RUN_TEST(tr, sort_test);
		RUN_TEST(tr, sort_compare_test);
		RUN_TEST(tr, merge_test);
		RUN_TEST(tr, splice_test);
		RUN_TEST(tr, insert_test);
		RUN_TEST(tr, push_back_front_test);
		RUN_TEST(tr, pop_back_front_test);
		RUN_TEST(tr, resize_test);
		RUN_TEST(tr, clear_test);
		RUN_TEST(tr, erase_test);
		RUN_TEST(tr, remove_test);
		RUN_TEST(tr, remove_if_test);
		RUN_TEST(tr, swap_test);
		RUN_TEST(tr, unique_test);
		RUN_TEST(tr, operators_test);
		ENABLE_LOGS = 0;
	}
}

namespace ft_vector
{
	void vector_test() {
		
		fillContainers();

		TestRunner tr;

		std::cout << YELLOW <<
				   "\n####################################################\n";
		std::cout << "#                                                  #\n";
		std::cout << "#                   Vector tests                   #\n";
		std::cout << "#                                                  #\n";
		std::cout << "####################################################\n\n"
				<< BW;

		RUN_TEST(tr, constructorDefault_test);
		RUN_TEST(tr, constructorCopy_test);
		RUN_TEST(tr, constructorFill_test);
		RUN_TEST(tr, constructorRange_test);
		RUN_TEST(tr, size_test);
		RUN_TEST(tr, empty_test);
		RUN_TEST(tr, max_size_test);
		RUN_TEST(tr, begin_test);
		RUN_TEST(tr, rbegin_rend_test);
		RUN_TEST(tr, front_back_test);
		RUN_TEST(tr, assign_range_test);
		RUN_TEST(tr, assign_fill_test);
		RUN_TEST(tr, at_test);
		RUN_TEST(tr, insert_range_test);
		RUN_TEST(tr, insert_fill_test);
		RUN_TEST(tr, insert_element_test);
		RUN_TEST(tr, push_back_test);
		RUN_TEST(tr, pop_back_test);
		RUN_TEST(tr, reserve_test);
		RUN_TEST(tr, resize_test);
		RUN_TEST(tr, clear_test);
		RUN_TEST(tr, erase_test);
		RUN_TEST(tr, swap_test);
		RUN_TEST(tr, operators_test);
		ENABLE_LOGS = 0;
	}
}

namespace ft_stack
{
	void stack_test() {
		
		fillContainers();

		TestRunner tr;

		std::cout << YELLOW <<
				   "\n####################################################\n";
		std::cout << "#                                                  #\n";
		std::cout << "#                   Stack tests                    #\n";
		std::cout << "#                                                  #\n";
		std::cout << "####################################################\n\n"
				<< BW;

		// RUN_TEST(tr, constructorDefault_test);
		// RUN_TEST(tr, size_test);
		// RUN_TEST(tr, empty_test);
		// RUN_TEST(tr, push_test);
		// RUN_TEST(tr, begin_test);
		// RUN_TEST(tr, pop_test);
		// RUN_TEST(tr, operators_test);
		
		ENABLE_LOGS = 0;
	}
}

