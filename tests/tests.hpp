#pragma once

#include <list>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include "list.hpp"
#include "vector.hpp"
#include "stack.hpp"

namespace ft {
	
	enum test {
		Exit,
		List,
		Vector,
		Map,
		Stack,
		Queue,
		All
	};
}

extern int ENABLE_LOGS;

static int arr_int[11] = {1,2,3,4,5,6,7,8,9,0,-1};
static char arr_str[][11] = {"one", "two", "three", "four", "five",
									"six", "seven", "eight", "nine", "zero", ""};

static std::pair<int, int> vect_map1[15] =  {std::make_pair(50, 1),
							std::make_pair(25, 1), 
								std::make_pair(8, 1), std::make_pair(35, 1),
									std::make_pair(1, 1), std::make_pair(12, 1),
									std::make_pair(30, 1), std::make_pair(40, 1),
							std::make_pair(75, 1),
								std::make_pair(60, 1), std::make_pair(90, 1),
									std::make_pair(55, 1), std::make_pair(70, 1),
									std::make_pair(80, 1), std::make_pair(100, 1)};

static std::pair<int, int> vect_map2[15] =  { std::make_pair(1, 1), std::make_pair(8, 1), std::make_pair(12, 1),
								std::make_pair(25, 1), std::make_pair(30, 1), std::make_pair(35, 1),
								std::make_pair(40, 1), std::make_pair(50, 1), std::make_pair(55, 1),
								std::make_pair(60, 1), std::make_pair(70, 1), std::make_pair(75, 1),
								std::make_pair(80, 1), std::make_pair(90, 1), std::make_pair(100, 1) };

static std::pair<std::string, int> vect_map3[15] =  { std::make_pair("one", 1), std::make_pair("two", 2), std::make_pair("three", 3),
								std::make_pair("four", 4), std::make_pair("five", 5), std::make_pair("six", 6),
								std::make_pair("seven", 7), std::make_pair("eight", 8), std::make_pair("nine", 9),
								std::make_pair("ten", 10), std::make_pair("eleven", 11), std::make_pair("twelve", 12),
								std::make_pair("thirteen", 13), std::make_pair("fourteen", 14), std::make_pair("fifteen", 15) };

static std::list<int> ls(arr_int, arr_int + 10);
static std::vector<int> vc(arr_int, arr_int + 10);
static std::deque<int> dq(arr_int, arr_int + 10);
static std::vector<std::string> str(arr_str, arr_str + 10);
static std::vector<std::pair<int, int> > map1(vect_map1, vect_map1 + 15);
static std::vector<std::pair<int, int> > map2(vect_map2, vect_map2 + 15);
static std::vector<std::pair<std::string, int> > map3(vect_map3, vect_map3 + 15);

  template<typename T>
std::string contToString(const T& cont) {
	std::ostringstream os;
	for(typename T::const_iterator it = cont.begin(); it != cont.end(); ++it) {
		os << *it << " ";
	}
	if (ENABLE_LOGS) {
		int i = 0;
		for(typename T::const_iterator it = cont.begin(); it != cont.end() && i < 50; ++it, ++i)
			std::cout << *it << " ";
		if (i == 50)
			std::cout << " ... too long output";
		std::cout << std::endl;
	}
	return os.str();
}

  template<typename T>
std::string stackToString(T& cont) {

	std::ostringstream os;
	size_t size = cont.size();

	while (size--) {
		os << cont.top() << " ";
		cont.pop();
	}
	if (ENABLE_LOGS) {
		std::cout << os.str() << std::endl;
	}
	return os.str();
}

  template<typename T>
std::string queueToString(T& cont) {

	std::ostringstream os;
	size_t size = cont.size();

	while (size--) {
		os << cont.front() << " ";
		cont.pop();
	}
	if (ENABLE_LOGS) {
		std::cout << os.str() << std::endl;
	}
	return os.str();
}

namespace ft_list
{
	void list_test();

	void constructorDefault_test();
	void constructorFill_test();
	void constructorRange_test();
	void size_test();
	void empty_test();
	void max_size_test();
	void begin_test();
	void rbegin_rend_test();
	void front_back_test();
	void assign_range_test();
	void assign_fill_test();
	void sort_test();
	void sort_compare_test();
	void merge_test();
	void splice_test();
	void insert_test();
	void push_back_front_test();
	void pop_back_front_test();
	void resize_test();
	void clear_test();
	void erase_test();
	void remove_test();
	void remove_if_test();
	void swap_test();
	void unique_test();
	void operators_test();
}

namespace ft_vector
{
	void vector_test();

	void constructorDefault_test();
	void constructorCopy_test();
	void constructorFill_test();
	void constructorRange_test();
	void size_test();
	void empty_test();
	void max_size_test();
	void begin_test();
	void rbegin_rend_test();
	void front_back_test();
	void assign_range_test();
	void assign_fill_test();
	void at_test();
	void insert_range_test();
	void insert_fill_test();
	void insert_element_test();
	void push_back_test();
	void pop_back_test();
	void reserve_test();
	void resize_test();
	void clear_test();
	void erase_test();
	void swap_test();
	void operators_test();
}

namespace ft_stack
{
	void stack_test();

	void constructorDefault_test();
	void size_test();
	void empty_test();
	void push_test();
	void top_test();
	void pop_test();
	void operators_test();
}

namespace ft_queue
{
	void queue_test();

	void constructorDefault_test();
	void size_test();
	void empty_test();
	void front_test();
	void back_test();
	void pop_test();
	void push_test();
	void operators_test();
}

namespace ft_map
{
	void map_test();

	void constructorDefault_test();
	// void constructorFill_test();
	// void constructorRange_test();
	void size_test();
	void empty_test();
	// void max_size_test();
	// void begin_test();
	// void rbegin_rend_test();
	// void front_back_test();
	// void assign_range_test();
	// void assign_fill_test();
	// void sort_test();
	// void sort_compare_test();
	// void merge_test();
	// void splice_test();
	// void insert_test();
	// void push_back_front_test();
	// void pop_back_front_test();
	// void resize_test();
	// void clear_test();
	// void erase_test();
	// void remove_test();
	// void remove_if_test();
	// void swap_test();
	// void unique_test();
	// void operators_test();
}