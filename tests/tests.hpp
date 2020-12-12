#pragma once

#include <list>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include "list.hpp"

enum test {
	Exit,
	List,
	Vector,
	Map,
	Stack,
	Queue,
	All
};

static std::list<int> ls {1,2,3,4,5,6,7,8,9,0};
static std::list<int> vc {1,2,3,4,5,6,7,8,9,0};
static std::deque<int> dq {1,2,3,4,5,6,7,8,9,0};

template<typename T>
std::string contToString(const T& cont) {
	std::ostringstream os;
	for(auto it = cont.begin(); it != cont.end(); ++it)
		os << *it << " ";
	return os.str();
}

template<typename T>
void fillCont(T& cont, size_t n) {
	cont.erase(cont.begin(), cont.end());
	for (size_t i = 0; i < n; i++)
		cont.push_back(i);
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