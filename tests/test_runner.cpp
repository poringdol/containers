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

		RUN_TEST(tr, ft_list::constructorDefault_test);
		RUN_TEST(tr, ft_list::constructorFill_test);
		RUN_TEST(tr, ft_list::constructorRange_test);
		RUN_TEST(tr, ft_list::size_test);
		RUN_TEST(tr, ft_list::empty_test);
		RUN_TEST(tr, ft_list::max_size_test);
		RUN_TEST(tr, ft_list::begin_test);
		RUN_TEST(tr, ft_list::rbegin_rend_test);
		RUN_TEST(tr, ft_list::front_back_test);
		RUN_TEST(tr, ft_list::assign_range_test);
		RUN_TEST(tr, ft_list::assign_fill_test);
		RUN_TEST(tr, ft_list::sort_test);
		RUN_TEST(tr, ft_list::sort_compare_test);
		RUN_TEST(tr, ft_list::merge_test);
		RUN_TEST(tr, ft_list::splice_test);
		RUN_TEST(tr, ft_list::insert_test);
		RUN_TEST(tr, ft_list::push_back_front_test);
		RUN_TEST(tr, ft_list::pop_back_front_test);
		RUN_TEST(tr, ft_list::resize_test);
		RUN_TEST(tr, ft_list::clear_test);
		RUN_TEST(tr, ft_list::erase_test);
		RUN_TEST(tr, ft_list::remove_test);
		RUN_TEST(tr, ft_list::remove_if_test);
		RUN_TEST(tr, ft_list::swap_test);
		RUN_TEST(tr, ft_list::unique_test);
		RUN_TEST(tr, ft_list::operators_test);
	}
}