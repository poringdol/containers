#include <iostream>
#include <sstream>
#include <list>
#include <algorithm>
#include "list.hpp"

using std::cout;
using std::endl;
using std::list;

#define PRINT_COMMAND(x) cout << "*" << x << endl;

template<typename T>
void print_list(const ft::list<T>& ls) {
	typename ft::list<T>::const_iterator it = ls.begin();
	if (ls.empty()) {
		cout << "--- List is empty";
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

void push_back_size_test(ft::list<int>& ls) {
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

void push_front_test(ft::list<int>& ls) {
	cout << "=== push_front() test ===" << endl;
	print_list(ls);
	PRINT_COMMAND("ls.push_front(7)");
	ls.push_front(7);
	print_list(ls);
	cout << endl;
}

void copy_constructor_assign_test(ft::list<int>& ls) {
	cout << "=== copy constructor & operator= test ===" << endl;
	print_list(ls);
	
	PRINT_COMMAND("ft::list<int> ls_assign = ls");
	ft::list<int> ls_assign = ls;
	print_list(ls_assign);

	PRINT_COMMAND("ft::list<int> ls_copy(ls)");
	ft::list<int> ls_copy(ls);
	print_list(ls_copy);
	
	ls_assign = ls_copy;
}

void iterator_test(ft::list<int>& ls) {
	cout << "=== iterator test ===" << endl;
	ft::list<int>::iterator it;

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

void clear_test(ft::list<int>& ls) {
	cout << "=== clear() test ===" << endl;
	cout << "List size before clear() is " << ls.size() << endl;
	print_list(ls);
	PRINT_COMMAND("ls.clear()");
	ls.clear();
	cout << "List size after clear() is " << ls.size() << endl;
	print_list(ls);
}

void empty_test(ft::list<int>& ls) {
	cout << "=== empty() test ===" << endl;
	cout << std::boolalpha << "Is list empty - " << ls.empty() << endl;
	ls.push_back(15);
	PRINT_COMMAND("ls.push_back(15)")
	cout << std::boolalpha << "Is list empty - " << ls.empty() << endl << endl;
}

void back_front_test(ft::list<int>& ls) {
	cout << "=== back()/front() test ===" << endl;
	ls.push_back(45);
	ls.push_back(60);
	print_list(ls);
	PRINT_COMMAND("ls.push_back(45)")
	int i1 = ls.front();
	int i2 = ls.back();

	PRINT_COMMAND("int i1 = ls.front()");
	PRINT_COMMAND("int i2 = ls.back()");
	cout << "ls.front() value is " << i1 << endl 
		 << "ls.back() value is " << i2 << endl << endl;
}

void pop_back_pop_front_test(ft::list<int>& ls) {
	print_list(ls);
	PRINT_COMMAND("ls.pop_front()");
	ls.pop_front();
	print_list(ls);
	PRINT_COMMAND("ls.pop_back()");
	ls.pop_back();
	print_list(ls);
	cout << endl;
}

void erase_test(ft::list<int>& ls) {
	cout << "=== erase() test ===" << endl;
	ls.push_back(15);
	cout << "Before erase() begin is - " << *ls.begin() << ", size is " << ls.size() << endl;

	ft::list<int>::iterator temp = ls.erase(ls.begin());
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
	ft::list<int>::iterator temp2 = ls.erase(++temp);
	PRINT_COMMAND("temp = ls.begin()\ntemp2 = ls.erase(++temp)")
	cout << "After erase() temp2 is - " << *temp2 << ", size is " << ls.size() << endl;
	print_list(ls);
	cout << endl;
}

void erase_range_test(ft::list<int>& ls) {
	cout << "=== erase() range test ===" << endl;
	ls.clear();
	ls.push_back(15);
	ls.push_back(30);
	ls.push_back(45);
	ls.push_back(60);
	print_list(ls);

	ft::list<int>::iterator temp = ls.begin();
	ft::list<int>::iterator temp2 = ls.end();
	PRINT_COMMAND("temp = ls.begin(), temp2 = ls.end()")
	PRINT_COMMAND("ls.erase(temp, --temp2);");
	//delete all nodes, exclude last
	ls.erase(temp, --temp2);
	cout << "After erase() begin is - " << *ls.begin() << ", size is " << ls.size() << endl;
	print_list(ls);
	cout << endl;
}

int main() {

	ft::list<int> ls;

	push_back_size_test(ls);
	push_front_test(ls);
	copy_constructor_assign_test(ls);
	iterator_test(ls);
	clear_test(ls);
	empty_test(ls);
	back_front_test(ls);
	pop_back_pop_front_test(ls);
	erase_test(ls);
	erase_range_test(ls);

// insert test
	// cout << "=== insert() test ===" << endl;
	// ls.clear();
	// print_list(ls);
	// PRINT_COMMAND("ls.insert(ls.begin(), 10)");
	// temp = ls.insert(ls.begin(), 10);
	// cout << "insert() return pointer to " << *temp << endl;
	// print_list(ls);
	// temp = ls.insert(ls.begin(), 20);
	// cout << "insert() return pointer to " << *temp << endl;
	// print_list(ls);

// merge

// assign


	cout << "End" << endl;

	// std::list<int> std_ls;
	// // std_ls.push_back(5);
	// auto it_ = std_ls.begin();
	// std_ls.erase(it_);
	// // std_ls.erase(it_);
}