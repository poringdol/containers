#pragma once

#include <list>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include "list.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "multimap.hpp"

extern int ENABLE_LOGS;

namespace ft {
	
	enum test {
		Exit,
		List,
		Vector,
		Map,
		Stack,
		Queue,
		Deque,
		Set,
		Multiset,
		Multimap,
		All
	};

	template<typename U>
	void
	print_tree(U& tree) { if (ENABLE_LOGS) tree._print_tree(); }
}

static int arr_int[16] = {1,2,3,4,5,6,7,8,9,0,1,2,3,1,3,-1};
static int arr_int2[16] = {1,2,3,1,2,2,1,4,0,0,1,2,3,1,3,-1};
static char arr_str[][16] = {"one_1", "two_1", "three_1", "four_1", "five_1",
									"six_1", "seven_1", "eight_1", "nine_1", "zero_1",
									"one_2", "two_2", "one_3", "two_3", "three_2", ""};

static std::pair<int, int> vect_map1[20] =  {std::make_pair(50, 1),
							std::make_pair(25, 2), 
								std::make_pair(8, 3), std::make_pair(35, 4),
									std::make_pair(1, 5), std::make_pair(12, 6),
									std::make_pair(30, 7), std::make_pair(40, 8),
							std::make_pair(75, 9),
								std::make_pair(60, 10), std::make_pair(90, 11),
									std::make_pair(55, 12), std::make_pair(70, 13),
									std::make_pair(80, 14), std::make_pair(100, 15),
							std::make_pair(25, 2), 
								std::make_pair(8, 3), std::make_pair(35, 4),
								std::make_pair(8, 3), std::make_pair(35, 4)};

static std::pair<int, int> vect_map2[20] =  { std::make_pair(1, 1), std::make_pair(8, 2), std::make_pair(12, 3),
								std::make_pair(25, 4), std::make_pair(30, 5), std::make_pair(35, 6),
								std::make_pair(40, 7), std::make_pair(50, 8), std::make_pair(55, 9),
								std::make_pair(40, 7), std::make_pair(50, 8), std::make_pair(55, 9),
								std::make_pair(60, 10), std::make_pair(70, 11), std::make_pair(75, 12),
								std::make_pair(60, 10), std::make_pair(70, 11),
								std::make_pair(80, 13), std::make_pair(90, 14), std::make_pair(100, 15) };

static std::pair<std::string, int> vect_map3[20] =  { std::make_pair("one", 1), std::make_pair("two", 2), std::make_pair("three", 3),
								std::make_pair("four", 4), std::make_pair("five", 5), std::make_pair("six", 6),
								std::make_pair("seven", 71), std::make_pair("eight", 81), std::make_pair("nine", 91),
								std::make_pair("seven", 72), std::make_pair("eight", 82), std::make_pair("nine", 92),
								std::make_pair("ten", 101), std::make_pair("eleven", 111), std::make_pair("twelve", 12),
								std::make_pair("ten", 102), std::make_pair("eleven", 112),
								std::make_pair("thirteen", 13), std::make_pair("fourteen", 14), std::make_pair("fifteen", 15) };

static std::list<int> ls(arr_int, arr_int + 15);
static std::vector<int> vc(arr_int, arr_int + 15);
static std::vector<int> vc2(arr_int2, arr_int2 + 15);
static std::deque<int> dq(arr_int, arr_int + 15);
static std::vector<std::string> str(arr_str, arr_str + 15);
static std::vector<std::pair<int, int> > map1(vect_map1, vect_map1 + 20);
static std::vector<std::pair<int, int> > map2(vect_map2, vect_map2 + 20);
static std::vector<std::pair<std::string, int> > map3(vect_map3, vect_map3 + 20);

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

  template<typename T>
std::string mapToString(const T& cont) {
	std::ostringstream os;
	for(typename T::const_iterator it = cont.begin(); it != cont.end(); ++it) {
		os << it->first << " " << it->second << ", ";
		// std::cout << it->first << " " << it->second << std::endl;
	}
	if (ENABLE_LOGS) {
		int i = 0;
		for(typename T::const_iterator it = cont.begin(); it != cont.end() && i < 50; ++it, ++i)
			std::cout << it->first << " " << it->second << ", ";
		if (i == 50)
			std::cout << " ... too long output";
		std::cout << std::endl;
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
	void constructorRange_test();
	void constructorCopy_test();
	void begin_end_test();
	void size_test();
	void max_size_test();
	void empty_test();
	void find_test();
	void count_test();
	void insert_range_test();
	void insert_single_test();
	void insert_hint_test();
	void erase_single_test();
	void erase_key_test();
	void erase_range_test();
	void operator_square_braces();
	void clear_test();
	void swap_test();
	void lower_bound_test();
	void upper_bound_test();
	void equal_range_test();
	void operators_test();
}

namespace ft_deque
{
	void deque_test();

	// void constructorDefault_test();
	// void size_test();
	// void empty_test();
	// void front_test();
	// void back_test();
	// void pop_test();
	// void push_test();
	// void operators_test();
}

namespace ft_set
{
	void set_test();
	
	void constructorDefault_test();
	void constructorRange_test();
	void constructorCopy_test();
	void begin_end_test();
	void size_test();
	void max_size_test();
	void empty_test();
	void find_test();
	void count_test();
	void insert_range_test();
	void insert_single_test();
	void insert_hint_test();
	void erase_single_test();
	void erase_key_test();
	void erase_range_test();
	void clear_test();
	void swap_test();
	void lower_bound_test();
	void upper_bound_test();
	void equal_range_test();
	void operators_test();
}

namespace ft_multiset
{
	void multiset_test();

	void constructorDefault_test();
	void constructorRange_test();
	void constructorCopy_test();
	void begin_end_test();
	void size_test();
	void max_size_test();
	void empty_test();
	void find_test();
	void count_test();
	void insert_range_test();
	void insert_single_test();
	void insert_hint_test();
	void erase_single_test();
	void erase_key_test();
	void erase_range_test();
	void operator_square_braces();
	void clear_test();
	void swap_test();
	void lower_bound_test();
	void upper_bound_test();
	void equal_range_test();
	void operators_test();
}

namespace ft_multimap
{
	void multimap_test();

	void constructorDefault_test();
	void constructorRange_test();
	void constructorCopy_test();
	void begin_end_test();
	void size_test();
	void max_size_test();
	void empty_test();
	void find_test();
	void count_test();
	void insert_range_test();
	void insert_single_test();
	void insert_hint_test();
	void erase_single_test();
	void erase_key_test();
	void erase_range_test();
	void clear_test();
	void swap_test();
	void lower_bound_test();
	void upper_bound_test();
	void equal_range_test();
	void operators_test();
}