#include <iostream>
#include <vector>
#include <list>
#include "includes/list.hpp"

using namespace std;

int main() {
	vector<int> vi;
	vector<char> vc;
	vector<double> vd;

	cout << "Vect int size : " << sizeof(vi) << endl <<
			"Vect char size : " << sizeof(vc) << endl <<
			"Vect double size : " << sizeof(vd) << endl << endl;
	
	vi.push_back(10);
	vc.push_back('C');
	vd.push_back(100.);

	list<int> ls;
	ft:list<int> mls;
	cout << "List int size : " << sizeof(ls) << endl <<
			"My list int size : " << sizeof(mls) << endl << endl;
}