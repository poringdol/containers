#include <iostream>
#include <sstream>
#include <list>
#include <algorithm>
#include <vector>
#include <cmath>
#include "list.hpp"

using std::cout;
using std::endl;
using std::list;

#define PRINT_COMMAND(x) cout << "* " << x << endl;

template<typename Cont>
void print_list(const Cont& ls) {
	typename Cont::const_iterator it = ls.begin();
	if (ls.empty()) {
		cout << "--- List is empty" << endl;
		return;
	}
	else
		cout << "--- Now list is ";
	while (it != ls.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

template<typename T>
void push_back_size_test(ft::list<T>& ls) {
	// typename ft::list<T> lst;
	// typename typename ft::list<T>::iterator it;
	cout << "=== push_back() and size() methods test ===" << endl;

	print_list(ls);
	ls.push_back(5);
	PRINT_COMMAND("ls.push_back(5)");
	cout << "Head data is " << *ls.begin() << endl;
	cout << "Size is " << ls.size() << endl << endl;

	cout << "Add two nodes" << endl;
	ls.push_back(15);
	ls.push_back(25);
	PRINT_COMMAND("ls.push_back(15)"); 
	PRINT_COMMAND("ls.push_back(25)")
	print_list(ls);
	cout << "Size is " << ls.size() << endl;
	cout << "Max size is " << ls.max_size() << endl << endl;
}

template<typename T>
void push_front_test(ft::list<T>& ls) {
	cout << "=== push_front() test ===" << endl;
	print_list(ls);
	PRINT_COMMAND("ls.push_front(7)");
	ls.push_front(7);
	print_list(ls);
	cout << endl;
}

template<typename T>
void insert_test(ft::list<T>& ls) {
	cout << "=== insert() test ===" << endl;

	print_list(ls);
	typename ft::list<T>::iterator it = ls.begin();
	PRINT_COMMAND("ls.insert(ls.begin(), 7)");
	ls.insert(it, 7);
	print_list(ls);

	it = ls.begin();
	it++;
	PRINT_COMMAND("ls.insert(++ls.begin(), 8)");
	ls.insert(it, 8);
	print_list(ls);

	cout << endl;
}

template<typename T>
void insert_fill_test(ft::list<T>& ls) {
	cout << "=== insert() (fill) test ===" << endl;

	print_list(ls);
	typename ft::list<T>::iterator it = ls.begin();
	PRINT_COMMAND("ls.insert(ls.begin(), 3, 10)");

	ls.insert(it, 3 ,10);
	print_list(ls);

	it = ls.begin();
	it++;
	PRINT_COMMAND("ls.insert(++ls.begin(), 5, 18)");
	ls.insert(it, 5, 18);
	print_list(ls);

	cout << endl;
}

template<typename T>
void insert_range_test(ft::list<T>& ls) {
	cout << "=== insert() (range) test ===" << endl;

	std::vector<int> vect;
	vect.push_back(100);
	vect.push_back(101);
	vect.push_back(102);

	print_list(ls);
	PRINT_COMMAND("std::vector<int> vect(11, 12, 13)");
	PRINT_COMMAND("ls.insert(ls.begin(), vect.begin(), vect.end())");
	ls.insert(ls.begin(), vect.begin(), vect.end());
	print_list(ls);

	cout << endl;
}

template<typename T>
void rbegin_rend_test(ft::list<T>& ls) {
	cout << "=== rbegin() rend_test() test ===" << endl;

	ls.push_back(15);
	ls.push_back(30);
	ls.push_back(45);
	ls.push_back(60);

	print_list(ls);
	typename ft::list<T>::reverse_iterator it = ls.rbegin();

	cout << "Reverse list is ";
	while (it != ls.rend()) {
		cout << *it << " ";
		it++;
	}
	cout << endl << endl;
}

template<typename T>
void const_rbegin_rend_test(const ft::list<T>& ls) {
	cout << "=== Const rbegin() rend_test() test ===" << endl;

	print_list(ls);
	typename ft::list<T>::const_reverse_iterator it = ls.rbegin();

	cout << "Reverse list is ";
	while (it != ls.rend()) {
		cout << *it << " ";
		it++;
	}
	cout << endl << endl;
}

template<typename T>
void copy_constructor_assign_test(ft::list<T>& ls) {
	cout << "=== copy constructor & operator= test ===" << endl;
	print_list(ls);
	
	PRINT_COMMAND("ft::list<T> ls_assign = ls");
	ft::list<T> ls_assign = ls;
	print_list(ls_assign);

	PRINT_COMMAND("ft::list<T> ls_copy(ls)");
	ft::list<T> ls_copy(ls);
	print_list(ls_copy);
	
	ls_assign = ls_copy;
	cout << endl;
}

template<typename T>
void range_constructor_assign_test(ft::list<T>& ls) {
	cout << "=== range constructor test ===" << endl;
	print_list(ls);
	
	PRINT_COMMAND("ft::list<T> ls2(ls.begin(), ls.end())");
	ft::list<T> ls2(ls.begin(), ls.end());
	print_list(ls2);
	cout << endl;
}

template<typename T>
void assign_range_test(ft::list<T>& ls) {
	cout << "=== assign range test ===" << endl;
	ft::list<int> ls2;
	print_list(ls2);
	PRINT_COMMAND("ls2.assign(ls.begin(), ls.end())");
	ls2.assign(ls.begin(), ls.end());
	print_list(ls2);

	ls.pop_back();
	PRINT_COMMAND("ls.pop_back()");
	ls2.assign(ls.begin(), ls.end());
	PRINT_COMMAND("ls2.assign(ls.begin(), ls.end())");
	print_list(ls2);
	cout << endl;
}

template<typename T>
void assign_fill_test(ft::list<T>& ls) {
	cout << "=== assign fill test ===" << endl;

	ft::list<int> ls2 = ls;
	print_list(ls2);
	PRINT_COMMAND("ls.assign(10, 14)");
	ls2.assign(10, 14);
	print_list(ls2);
	cout << "List size is " << ls2.size() << endl;
	cout << endl;
}

template<typename T>
void iterator_test(ft::list<T>& ls) {
	cout << "=== iterator test ===" << endl;
	typename ft::list<T>::iterator it;

	print_list(ls);
	it = ls.begin();
	PRINT_COMMAND("it = ls.begin()")
	cout << "it point to " << *it << endl;

	it++;
	PRINT_COMMAND("it++");
	cout << "it point to " << *it << endl;

	it--;
	PRINT_COMMAND("it--");
	cout << "it point to " << *it << endl;

	PRINT_COMMAND("Print and postfix increment");
	PRINT_COMMAND("cout << *it++ << endl;");
	cout << "it point to " << *it++ << endl;
	cout << "it point to " << *it << endl;

	--it;
	PRINT_COMMAND("--it");
	cout << "it point to " << *it << endl;
	PRINT_COMMAND("Print and prefix increment");
	PRINT_COMMAND("cout << *++it << endl;");
	cout << "it point to " << *++it << endl;
	cout << "it point to " << *it << endl << endl;
}

template<typename T>
void clear_test(ft::list<T>& ls) {
	cout << "=== clear() test ===" << endl;
	cout << "List size before clear() is " << ls.size() << endl;
	print_list(ls);
	PRINT_COMMAND("ls.clear()");
	ls.clear();
	cout << "List size after clear() is " << ls.size() << endl;
	print_list(ls);
	cout << endl;
}

template<typename T>
void empty_test(ft::list<T>& ls) {
	cout << "=== empty() test ===" << endl;
	cout << std::boolalpha << "Is list empty - " << ls.empty() << endl;
	ls.push_back(15);
	PRINT_COMMAND("ls.push_back(15)")
	cout << std::boolalpha << "Is list empty - " << ls.empty() << endl << endl;
}

template<typename T>
void back_front_test(ft::list<T>& ls) {
	cout << "=== back()/front() test ===" << endl;
	ls.push_back(45);
	ls.push_back(60);
	print_list(ls);
	int i1 = ls.front();
	int i2 = ls.back();

	PRINT_COMMAND("int i1 = ls.front()");
	PRINT_COMMAND("int i2 = ls.back()");
	cout << "ls.front() value is " << i1 << endl 
		 << "ls.back() value is " << i2 << endl << endl;
}

template<typename T>
void pop_back_pop_front_test(ft::list<T>& ls) {
	print_list(ls);
	PRINT_COMMAND("ls.pop_front()");
	ls.pop_front();
	print_list(ls);
	PRINT_COMMAND("ls.pop_back()");
	ls.pop_back();
	print_list(ls);
	cout << endl;
}

void resize_test() {
	cout << "=== resize() test ===" << endl;

	ft::list<int> ls;
	 for (int i=1; i<10; ++i)
	 	ls.push_back(i);

	PRINT_COMMAND("ls.resize(5)");
	ls.resize(5);
	PRINT_COMMAND("ls.resize(8,100)");
	ls.resize(8,100);
	PRINT_COMMAND("ls.resize(12)");
	ls.resize(12);
	print_list(ls);
	cout << endl;
}

void reverse_test() {
	cout << "=== reverse() test ===" << endl;

	ft::list<int> ls;
	 for (int i=1; i<10; ++i)
	 	ls.push_back(i);

	print_list(ls);
	PRINT_COMMAND("ls.reverse()");
	ls.reverse();
	print_list(ls);

	PRINT_COMMAND("ls.clear()");
	ls.clear();
	print_list(ls);
	PRINT_COMMAND("ls.reverse()");
	ls.reverse();
	print_list(ls);
	cout << endl;
}

template<typename T>
void erase_test(ft::list<T>& ls) {
	cout << "=== erase() test ===" << endl;
	ls.push_back(15);
	cout << "Before erase() begin is - " << *ls.begin() << ", size is " << ls.size() << endl;

	typename ft::list<T>::iterator temp = ls.erase(ls.begin());
	PRINT_COMMAND("ls.erase(ls.begin()");
	cout << "After erase() begin is - " << *ls.begin() << ", size is " << ls.size() << endl;
	cout << "ls.erase() return iterator to " << *temp << endl << endl;

	cout << "Clear list and push 15, 30, 45 " << endl;
	ls.clear();
	ls.push_back(15);
	ls.push_back(30);
	ls.push_back(45);
	temp = ls.begin();
	print_list(ls);
	typename ft::list<T>::iterator temp2 = ls.erase(++temp);
	PRINT_COMMAND("temp = ls.begin()\ntemp2 = ls.erase(++temp)")
	cout << "After erase() temp2 is - " << *temp2 << ", size is " << ls.size() << endl;
	print_list(ls);
	cout << endl;
}

template<typename T>
void erase_range_test(ft::list<T>& ls) {
	cout << "=== erase() range test ===" << endl;
	ls.clear();
	ls.push_back(15);
	ls.push_back(30);
	ls.push_back(45);
	ls.push_back(60);
	print_list(ls);

	typename ft::list<T>::iterator temp = ls.begin();
	typename ft::list<T>::iterator temp2 = ls.end();
	PRINT_COMMAND("temp = ls.begin(), temp2 = ls.end()")
	PRINT_COMMAND("ls.erase(temp, --temp2);");
	//delete all nodes, exclude last
	ls.erase(temp, --temp2);
	cout << "After erase() begin is - " << *ls.begin() << ", size is " << ls.size() << endl;
	print_list(ls);
	cout << endl;
}

template<typename T>
void remove_test(ft::list<T>& ls) {
	cout << "=== remove() test ===" << endl;

	ls.push_back(1);
	ls.push_back(5);
	ls.push_back(5);
	ls.push_back(2);
	ls.push_back(3);
	ls.push_back(5);
	ls.push_back(4);
	ls.push_back(0);

	print_list(ls);
	PRINT_COMMAND("ls.remove(5)");
	ls.remove(5);
	print_list(ls);
	cout << endl;
}


// a predicate implemented as a function:
bool single_digit (const int& value) { return (value<10); }

// a predicate implemented as a class:
struct is_odd {
  bool operator() (const int& value) { return (value%2)==1; }
};

template<typename T>
void remove_if_test(ft::list<T>& ls) {
	cout << "=== remove_if() test ===" << endl;

	ls.push_back(25);
	ls.push_back(43);
	ls.push_back(8);
	ls.push_back(62);
	ls.push_back(21);
	ls.push_back(5);
	ls.push_back(16);

	print_list(ls);
	cout << "Predicate is a class" << endl;
	PRINT_COMMAND("ls.remove_if(is_odd())");
	ls.remove_if(is_odd());
	print_list(ls);
	cout << endl;

	cout << "Predicate is a function" << endl;
	PRINT_COMMAND("ls.remove_if(single_digit)");
	ls.remove_if(single_digit);
	print_list(ls);
	cout << endl;
}

void merge_test() {
	cout << "=== merge() test ===" << endl;

	ft::list<int> ls1;
	ls1.push_back(1);
	ls1.push_back(3);
	ls1.push_back(5);
	ls1.push_back(7);
	cout << "First list: ";
	print_list(ls1);

	ft::list<int> ls2;
	ls2.push_back(2);
	ls2.push_back(4);
	ls2.push_back(6);
	ls2.push_back(8);
	cout << "Second list: ";
	print_list(ls2);

	PRINT_COMMAND("ls1.merge(ls2);");
	ls1.merge(ls2);
	cout << "First list: ";
	print_list(ls1);
	cout << "First list size is - " << ls1.size()
		 << ", second list size is - " << ls2.size() << endl;
	cout << endl;
}

bool mycomparison (int first, int second)
{ return ( int(first)<int(second) ); }

void merge_compare_test() {
	cout << "=== merge() with comparator test ===" << endl;

	ft::list<int> ls1;
	ls1.push_back(1);
	ls1.push_back(3);
	ls1.push_back(5);
	ls1.push_back(7);
	cout << "First list: ";
	print_list(ls1);

	ft::list<int> ls2;
	ls2.push_back(2);
	ls2.push_back(4);
	ls2.push_back(6);
	ls2.push_back(8);
	cout << "Second list: ";
	print_list(ls2);

	PRINT_COMMAND("first.merge(ls2);");
	ls1.merge(ls2);
	cout << "First list: ";
	print_list(ls1);
	cout << "First list size is - " << ls1.size()
		 << ", second list size is - " << ls2.size() << endl;
	cout << endl;
}

void splice_1_test() {
	cout << "=== splice() 1 test ===" << endl;

	ft::list<int> mylist1, mylist2;
	ft::list<int>::iterator it;

	for (int i=1; i<=4; ++i)
		mylist1.push_back(i);      // mylist1: 1 2 3 4
	cout << "First list: ";
	print_list(mylist1);

	for (int i=1; i<=3; ++i)
		mylist2.push_back(i*10);   // mylist2: 10 20 30
	cout << "Second list: ";
	print_list(mylist2);

	it = mylist1.begin();
	++it;                         // points to 2

	PRINT_COMMAND("mylist1.splice(it, mylist2)");
	mylist1.splice(it, mylist2); // mylist1: 1 10 20 30 2 3 4
								// mylist2 (empty)
								// "it" still points to 2 (the 5th element)
	cout << "First list: ";
	print_list(mylist1);
	cout << "First list size is - " << mylist1.size()
		 << ", second list size is - " << mylist2.size() << endl;
	cout << endl;
}

void splice_2_test() {
	cout << "=== splice() 2 test ===" << endl;

	ft::list<int> mylist1, mylist2;
	ft::list<int>::iterator it1, it2;

	for (int i=1; i<=4; ++i)
		mylist1.push_back(i);      // mylist1: 1 2 3 4
	cout << "First list: ";
	print_list(mylist1);

	for (int i=1; i<=3; ++i)
		mylist2.push_back(i*10);   // mylist2: 10 20 30
	cout << "Second list: ";
	print_list(mylist2);

	it1 = mylist1.begin();
	it2 = mylist2.begin();
	++it1; ++it2;
	PRINT_COMMAND("mylist1.splice(it1, mylist2, it2)");
	mylist1.splice(it1, mylist2, it2);
	cout << "First list: ";
	print_list(mylist1);
	cout << "Second list: ";
	print_list(mylist2);

	cout << "First list size is - " << mylist1.size()
		 << ", second list size is - " << mylist2.size() << endl;
	cout << endl;
}

void splice_3_test() {
	cout << "=== splice() 3 test ===" << endl;

	ft::list<int> mylist1, mylist2;
	ft::list<int>::iterator it1, it2, it3;

	for (int i=1; i<=4; ++i)
		mylist1.push_back(i);      // mylist1: 1 2 3 4
	cout << "First list: ";
	print_list(mylist1);

	for (int i=1; i<=5; ++i)
		mylist2.push_back(i*10);   // mylist2: 10 20 30
	cout << "Second list: ";
	print_list(mylist2);

	it1 = mylist1.begin();
	it2 = mylist2.begin();
	it3 = mylist2.end();
	++it1; ++it2;
	PRINT_COMMAND("mylist1.splice(it1, mylist2, it2, it3)");
	mylist1.splice(it1, mylist2, it2, it3);
	cout << "First list: ";
	print_list(mylist1);
	cout << "Second list: ";
	print_list(mylist2);

	cout << "First list size is - " << mylist1.size()
		 << ", second list size is - " << mylist2.size() << endl;
	cout << endl;
}

void sort_test() {
	ft::list<int> ls;
	cout << "=== sort() test ===" << endl;

	for (int i = 0; i < 15; i++) {
		ls.push_back(rand() % 20);
	}
	print_list(ls);
	PRINT_COMMAND("ls.sort()");
	ls.sort();
	print_list(ls);
	cout << endl;
}

void sort_compare_test() {
	cout << "=== sort() with comparator test ===" << endl;

	ft::list<int> ls;
	for (int i = 0; i < 15; i++) {
		ls.push_back(rand() % 20);
	}
	print_list(ls);
	PRINT_COMMAND("ls.sort()");
	ls.sort(mycomparison);
	print_list(ls);
	cout << endl;
}

void swap_test() {
	cout << "=== swap() with comparator test ===" << endl;

	std::list<int> first (3,100);   // three ints with a value of 100
	std::list<int> second (5,200);  // five ints with a value of 200
	cout << "First list: ";
	print_list(first);
	cout << "Second list: ";
	print_list(second);
	
	PRINT_COMMAND("first.swap(second)")
	first.swap(second);

	std::cout << "first contains:";
	for (std::list<int>::iterator it=first.begin(); it!=first.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	std::cout << "second contains:";
	for (std::list<int>::iterator it=second.begin(); it!=second.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

// a binary predicate implemented as a function:
bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

// a binary predicate implemented as a class:
struct is_near {
  bool operator() (double first, double second)
  { return (fabs(first-second)<5.0); }
};

void unique_test() {
	double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
						12.77, 73.35, 72.25, 15.3,  72.25 };
	std::list<double> mylist (mydoubles,mydoubles+10);

	mylist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
								// 15.3,  72.25, 72.25, 73.0,  73.35
	print_list(mylist);
	PRINT_COMMAND("mylist.unique()");
	mylist.unique();           //  2.72,  3.14, 12.15, 12.77
								// 15.3,  72.25, 73.0,  73.35
	print_list(mylist);

	PRINT_COMMAND("mylist.unique (same_integral_part)");
	mylist.unique (same_integral_part);  //  2.72,  3.14, 12.15
	print_list(mylist);
										// 15.3,  72.25, 73.0

	PRINT_COMMAND("mylist.unique (is_near())");
	mylist.unique (is_near());           //  2.72, 12.15, 72.25
	print_list(mylist);

	cout << endl;
}


int main() {

	ft::list<int> ls;

	ft::list<int>::iterator it = ls.begin();
	ft::list<int>::const_iterator it2;
	it2 = it;
	push_back_size_test(ls);
	push_front_test(ls);
	insert_test(ls);
	insert_fill_test(ls);
	insert_range_test(ls);
	rbegin_rend_test(ls);
	const_rbegin_rend_test(ls);
	copy_constructor_assign_test(ls);
	range_constructor_assign_test(ls);
	assign_range_test(ls);
	assign_fill_test(ls);
	iterator_test(ls);
	clear_test(ls);
	empty_test(ls);
	back_front_test(ls);
	pop_back_pop_front_test(ls);
	resize_test();
	reverse_test();
	erase_test(ls);
	erase_range_test(ls);
	remove_test(ls);
	remove_if_test(ls);
	merge_test();
	merge_compare_test();
	splice_1_test();
	splice_2_test();
	splice_3_test();
	sort_test();
	sort_compare_test();
	swap_test();
	unique_test();

	cout << "End" << endl;

	// std::list<int> std_ls;
	// // std_ls.push_back(5);
	// auto it_ = std_ls.begin();
	// std_ls.erase(it_);
	// // std_ls.erase(it_);
}