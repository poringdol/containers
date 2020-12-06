#include <iostream>
#include <sstream>
#include <list>
#include <algorithm>
#include "list.hpp"

using std::cout;
using std::endl;
using std::list;

#define PRINT_COMMAND(x) cout << x << endl;

template<typename T>
void print_list(const ft::list<T>& ls) {
	typename ft::list<T>::const_iterator it = ls.begin();
	if (ls.empty())
		cout << "--- List is empty" << endl;
	else
		cout << "--- Now list is ";
	while (it != ls.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

int main() {

	ft::list<int> ls;

// push_back() and size() test
	cout << "=== push_back() and size() methods test ===" << endl;

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
	cout << "Size is " << ls.size() << endl << endl;


// iterator test
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

// clear() test
cout << "=== clear() test ===" << endl;
	cout << "List size before clear() is " << ls.size() << endl;
	print_list(ls);
	PRINT_COMMAND("ls.clear()");
	ls.clear();
	cout << "List size after clear() is " << ls.size() << endl;
	print_list(ls);

// empty() test
	cout << "=== empty() test ===" << endl;
	cout << std::boolalpha << "Is list empty - " << ls.empty() << endl;
	ls.push_back(15);
	PRINT_COMMAND("ls.push_back(15)")
	cout << std::boolalpha << "Is list empty - " << ls.empty() << endl << endl;

// back()/front() test
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

// erase() test
	cout << "=== erase() test ===" << endl;
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

// erase() range test
	cout << "=== erase() range test ===" << endl;
	ls.clear();
	ls.push_back(15);
	ls.push_back(30);
	ls.push_back(45);
	ls.push_back(60);
	print_list(ls);

	temp = ls.begin();
	temp2 = ls.end();
	PRINT_COMMAND("temp = ls.begin(), temp2 = ls.end()")
	PRINT_COMMAND("ls.erase(temp, --temp2);");
	//delete all nodes, exclude last
	ls.erase(temp, --temp2);
	cout << "After erase() begin is - " << *ls.begin() << ", size is " << ls.size() << endl;
	print_list(ls);
	cout << endl;

// insert test
	cout << "=== insert() test ===" << endl;
	print_list(ls);
	PRINT_COMMAND("ls.insert(ls.begin(), 10)");
	ls.insert(ls.begin(), 10);
	print_list(ls);


	cout << "End" << endl;

	// std::list<int> std_ls;
	// // std_ls.push_back(5);
	// auto it_ = std_ls.begin();
	// std_ls.erase(it_);
	// // std_ls.erase(it_);
}