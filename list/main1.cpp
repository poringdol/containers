#include <list>
#include <iostream>

#define PRINT_COMMAND(x) cout << "*" << x << endl;

using std::cout;
using std::endl;
using std::list;

template<typename T>
void print_list(const std::list<T>& ls) {
	typename std::list<T>::const_iterator it = ls.begin();
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

int main() {
	list<int> ls;
	ls.push_back(1);
	ls.push_back(2);
	ls.push_back(3);

	print_list(ls);
	
	PRINT_COMMAND("std::list<int> ls_assign = ls");
	list<int> ls_assign = ls;
	print_list(ls_assign);

	PRINT_COMMAND("std::list<int> ls_copy(ls)");
	list<int> ls_copy(ls);
	print_list(ls_copy);
	
	ls_assign = ls_copy;
}