#include <map>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <map>
#include "tests.hpp"
#include "test_runner.h"
#include "map.hpp"

/*********************************************************************/
/*								TESTS								 */
/*********************************************************************/
namespace ft_map
{

	void constructorDefault_test() {

		ft::map<int, int> mymp1;
		ASSERT_EQUAL(0u, mymp1.size());

		// ft::map<int, int> mymp2(mymp1);
		// ASSERT_EQUAL(0u, mymp2.size());

		// ft::map<int, int> mymp3 = mymp1;
		// ASSERT_EQUAL(0u, mymp3.size());
	}

	// void constructorFill_test() {
		
	// 	ft::map<int, int> mp1(10, 15);
	// 	ft::map<int, int> mymp1(10, 15);
	// 	ASSERT_EQUAL(mp1.size(), mymp1.size());
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));

	// 	ft::map<char> mp2(10, 'X');
	// 	ft::map<char> mymp2(10, 'X');
	// 	ASSERT_EQUAL(mp2.size(), mymp2.size());
	// 	ASSERT_EQUAL(contToString(mp2), contToString(mymp2));

	// 	ft::map<std::string> mp3(10, "Kto tut?");
	// 	ft::map<std::string> mymp3(10, "Kto tut?");
	// 	ASSERT_EQUAL(mp3.size(), mymp3.size());
	// 	ASSERT_EQUAL(contToString(mp3), contToString(mymp3));
	// }

	// void constructorRange_test() {

	// 	ft::map<int, int> mymp1(map1.begin(), map1.end());		// map from std::map
	// 	ASSERT_EQUAL(mp.size(), mymp1.size());
	// 	ASSERT_EQUAL(contToString(mp), contToString(mymp1));


	// 	ft::map<int, int> mymp2(vc.begin(), vc.end());		// map from std::vector
	// 	ASSERT_EQUAL(vc.size(), mymp2.size());
	// 	ASSERT_EQUAL(contToString(vc), contToString(mymp2));

	// 	ft::map<int, int> mymp3(dq.begin(), dq.end());		// map from std::deque
	// 	ASSERT_EQUAL(dq.size(), mymp3.size());
	// 	ASSERT_EQUAL(contToString(dq), contToString(mymp3));
	// }

	void size_test() {

		ft::map<int, int> mymp1;
		ASSERT_EQUAL(0u, mymp1.size());

		ft::map<int, int> mymp2(map1.begin(), map1.end());
		ASSERT_EQUAL(15u, mymp2.size());
	}

	void empty_test() {

		ft::map<int, int> mymp1;
		ASSERT_EQUAL(true, mymp1.empty());

		ft::map<int, int> mymp2(map1.begin(), map1.end());
		ASSERT_EQUAL(false, mymp2.empty());
	}

	// void max_size_test() {
		
	// 	ft::map<int, int> mymp;
	// 	ASSERT_EQUAL(mp.max_size(), mymp.max_size());
	// }

	// void begin_test() {
		
	// 	ft::map<int, int> mymp(map1.begin(), map1.end());
	// 	ft::map<int, int>::iterator myit = mymap1.begin();
	// 	std::map<int, int>::iterator it = map1.begin();
	// 	ASSERT_EQUAL(*myit, *it);

	// 	*it = 100;
	// 	*myit = 100;
	// 	ASSERT_EQUAL(*it, *myit);

	// 	const ft::map<int, int> mymp2(map1.begin(), map1.end());
	// 	ft::map<int, int>::const_iterator myit2 = mymap1.begin();
	// 	ASSERT_EQUAL(*myit2, 100);
	// 	*it = 0;
	// }

	// void rbegin_rend_test() {

	// 	ft::map<int, int> mymp(map1.begin(), map1.end());
	// 	ASSERT_EQUAL(contToString(mp), contToString(mymp));

	// 	ft::map<int, int> myrmp(mp.rbegin(), mp.rend());
	// 	std::map<int, int> rmp(mp.rbegin(), mp.rend());
	// 	ASSERT_EQUAL(contToString(rmp), contToString(myrmp));
	// }

	// void front_back_test() {

	// 	ft::map<int, int> mymp(map1.begin(), map1.end());
	// 	ASSERT_EQUAL(contToString(mp), contToString(mymp));

	// 	ASSERT_EQUAL(mp.front(), mymp.front());
	// 	ASSERT_EQUAL(mp.back(), mymp.back());
	// }

	// void assign_range_test() {

	// 	ft::map<int, int> mymp;
	// 	mymp.assign(map1.begin(), map1.end());
	// 	ASSERT_EQUAL(contToString(mp), contToString(mymp));

	// 	mymp.assign(mp.rbegin(), mp.rend());
	// 	std::map<int, int> rmp;
	// 	rmp.assign(mp.rbegin(), mp.rend());
	// 	ASSERT_EQUAL(contToString(rmp), contToString(mymp));

	// 	mymp.assign(vc.begin(), vc.end());
	// 	ASSERT_EQUAL(contToString(vc), contToString(mymp));

	// 	mymp.assign(dq.begin(), dq.end());
	// 	ASSERT_EQUAL(contToString(dq), contToString(mymp));
	// }

	// void assign_fill_test() {

	// 	std::map<int, int> amp;
	// 	amp.assign(18, 100);
	// 	ft::map<int, int> mymp;
	// 	mymp.assign(18, 100);
	// 	ASSERT_EQUAL(contToString(amp), contToString(mymp));

	// 	std::map<double> amp2;
	// 	amp2.assign(20, 100.);
	// 	ft::map<double> mymp2;
	// 	mymp2.assign(20, 100.);
	// 	ASSERT_EQUAL(contToString(amp2), contToString(mymp2));

	// 	std::map<std::string> amp3;
	// 	amp3.assign(22, "Fart");
	// 	ft::map<std::string> mymp3;
	// 	mymp3.assign(22, "Fart");
	// 	ASSERT_EQUAL(contToString(amp3), contToString(mymp3));
	// }

	// void sort_test() {

	// 	std::vector<int> vect;
	// 	for (int i = 0; i < 10; i++) { vect.push_back(rand() % 100); }

	// 	std::map<int, int> smp(vect.begin(), vect.end());
	// 	ft::map<int, int> mymp(vect.begin(), vect.end());
	// 	ASSERT_EQUAL(contToString(smp), contToString(mymp));

	// 	smp.sort();
	// 	mymp.sort();
	// 	ASSERT_EQUAL(contToString(smp), contToString(mymp));
	// }

	// bool mycomparison (int first, int second) { return (first % 2) < (second % 2); }

	// void sort_compare_test() {

	// 	std::map<int, int> emp;
	// 	ft::map<int, int> myemp;
	// 	emp.sort(mycomparison);
	// 	myemp.sort(mycomparison);
	// 	ASSERT_EQUAL(contToString(emp), contToString(myemp));

	// 	std::vector<int> vect;
	// 	for (int i = 0; i < 10; i++) { vect.push_back(rand() % 100); }

	// 	std::map<int, int> smp(vect.begin(), vect.end());
	// 	ft::map<int, int> mymp(vect.begin(), vect.end());
	// 	ASSERT_EQUAL(contToString(smp), contToString(mymp));

	// 	smp.sort(mycomparison);
	// 	mymp.sort(mycomparison);
	// 	ASSERT_EQUAL(contToString(smp), contToString(mymp));
	// }

	// void merge_test() {
	// 	std::vector<int> vect1;
	// 	std::vector<int> vect2;
	// 	for (int i = 0; i < 10; i++) { vect1.push_back(rand() % 100); }
	// 	for (int i = 0; i < 10; i++) { vect2.push_back(rand() % 100); }

	// 	std::map<int, int> mp1(vect1.begin(), vect1.end());
	// 	std::map<int, int> mp2(vect2.begin(), vect2.end());
	// 	mp1.sort();
	// 	mp2.sort();

	// 	ft::map<int, int> mymp1(vect1.begin(), vect1.end());
	// 	ft::map<int, int> mymp2(vect2.begin(), vect2.end());
	// 	mymp1.sort();
	// 	mymp2.sort();

	// 	mp1.merge(mp2);
	// 	mymp1.merge(mymp2);
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(contToString(mp2), contToString(mymp2));

	// // merge compare
	// 	mp2.assign(vect1.begin(), vect1.end());
	// 	mymp2.assign(vect1.begin(), vect1.end());
	// 	mp2.sort();
	// 	mymp2.sort();

	// 	mp1.merge(mp2, mycomparison);
	// 	mymp1.merge(mymp2, mycomparison);
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(contToString(mp2), contToString(mymp2));
	// }

	// void splice_test() {

	// // splice (iterator position, map& x)
	// 	std::map<int, int> mp1(map1.begin(), map1.end());
	// 	std::map<int, int> mp2(map1.begin(), map1.end());

	// 	ft::map<int, int> mymp1(map1.begin(), map1.end());
	// 	ft::map<int, int> mymp2(map1.begin(), map1.end());

	// 	mp1.splice(++(mp1.begin()), mp2);
	// 	mymp1.splice(++(mymp1.begin()), mymp2);

	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(contToString(mp2), contToString(mymp2));

	// // splice (iterator position, map& x, iterator i)
	// 	mp2.assign(map1.begin(), map1.end());
	// 	mymp2.assign(map1.begin(), map1.end());

	// 	mp1.splice(mp1.begin(), mp2, ++(mp2.begin()));
	// 	mymp1.splice(mymp1.begin(), mymp2, ++(mymp2.begin()));

	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(contToString(mp2), contToString(mymp2));

	// // splice (iterator position, map& x, iterator first, iterator last)
	// 	mp2.assign(map1.begin(), map1.end());
	// 	mymp2.assign(map1.begin(), map1.end());

	// 	mp1.splice(mp1.begin(), mp2, mp2.begin(), mp2.end());
	// 	mymp1.splice(mymp1.begin(), mymp2, mymp2.begin(), mymp2.end());

	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(contToString(mp2), contToString(mymp2));
	// }

	// void insert_test() {
	// 	std::map<int, int> mp1(map1.begin(), map1.end());
	// 	ft::map<int, int> mymp1(map1.begin(), map1.end());

	// // insert (iterator position, const T& data)
	// 	std::map<int, int>::iterator it = mp1.insert(++(mp1.begin()), 100);
	// 	ft::map<int, int>::iterator  myit = mymp1.insert(++(mymp1.begin()), 100);
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(*it, *myit);

	// // insert (iterator position, size_t n, const T& val)
	// 	mp1.insert(++(mp1.begin()), 10, 150);
	// 	mymp1.insert(++(mymp1.begin()), 10, 150);
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));

	// // insert (iterator position, InputIterator first, InputIterator last)
	// 	mp1.insert(mp1.begin(), map1.begin(), map1.end());
	// 	mymp1.insert(mymp1.begin(), map1.begin(), map1.end());
	// }

	// void push_back_front_test() {
	// 	std::map<int, int> mp1;
	// 	ft::map<int, int> mymp1;

	// 	mp1.push_back(12);
	// 	mymp1.push_back(12);
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));

	// 	mp1.push_back(17);
	// 	mymp1.push_back(17);
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));

	// 	mp1.push_front(11);
	// 	mymp1.push_front(11);
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// }

	// void pop_back_front_test() {
	// 	std::map<int, int> mp1;
	// 	ft::map<int, int> mymp1;

	// // test with empty map
	// 	// mp1.pop_front();
	// 	// mymp1.pop_front();
	// 	// ASSERT_EQUAL(mp1.size(), mymp1.size());

	// 	// mp1.pop_back();
	// 	// mymp1.pop_back();
	// 	// ASSERT_EQUAL(mp1.size(), mymp1.size());

	// // test with not empty map
	// 	mp1.assign(map1.begin(), map1.end());
	// 	mymp1.assign(map1.begin(), map1.end());

	// 	mp1.pop_back();
	// 	mymp1.pop_back();
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(mp1.size(), mymp1.size());

	// 	mp1.pop_front();
	// 	mymp1.pop_front();
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(mp1.size(), mymp1.size());
	// }

	// void resize_test() {
	// 	std::map<int, int> mp1;
	// 	ft::map<int, int> mymp1;

	// 	mp1.resize(12, 1);
	// 	mymp1.resize(12, 1);
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(mp1.size(), mymp1.size());

	// 	mp1.resize(17, 2);
	// 	mymp1.resize(17, 2);
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(mp1.size(), mymp1.size());

	// 	mp1.resize(8, 3);
	// 	mymp1.resize(8, 3);
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(mp1.size(), mymp1.size());
	// }

	// void clear_test() {
	// 	std::map<int, int> mp1(map1.begin(), map1.end());
	// 	ft::map<int, int> mymp1(map1.begin(), map1.end());

	// 	mp1.clear();
	// 	mymp1.clear();
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(mp1.size(), mymp1.size());

	// 	mp1.clear();
	// 	mymp1.clear();
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(mp1.size(), mymp1.size());
	// }

	// void erase_test() {
	// 	std::map<int, int> mp1(map1.begin(), map1.end());
	// 	ft::map<int, int> mymp1(map1.begin(), map1.end());

	// 	mp1.erase(++(mp1.begin()));
	// 	mymp1.erase(++(mymp1.begin()));
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));

	// 	mp1.erase(--(mp1.end()));
	// 	mymp1.erase(--(mymp1.end()));
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));

	// 	mp1.erase(++(mp1.begin()), mp1.end());
	// 	mymp1.erase(++(mymp1.begin()), mymp1.end());
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(mp1.size(), mymp1.size());
	// }

	// void remove_test() {
	// 	std::map<int, int> mp1(map1.begin(), map1.end());
	// 	ft::map<int, int> mymp1(map1.begin(), map1.end());

	// 	mp1.remove(5);
	// 	mymp1.remove(5);
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(mp1.size(), mymp1.size());

	// 	mp1.remove(105);
	// 	mymp1.remove(105);
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(mp1.size(), mymp1.size());
	// }

	// bool single_digit (const int& value) { return (value<5); }

	// struct is_odd {
	// bool operator() (const int& value) { return (value%2)==1; }
	// };

	// void remove_if_test() {
	// 	std::map<int, int> mp1(map1.begin(), map1.end());
	// 	ft::map<int, int> mymp1(map1.begin(), map1.end());

	// 	mp1.remove_if(single_digit);
	// 	mymp1.remove_if(single_digit);
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));

	// 	mp1.remove_if(is_odd());
	// 	mymp1.remove_if(is_odd());
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// }

	// void swap_test() {
	// 	std::map<int, int> mp1(map1.begin(), map1.end());
	// 	std::map<int, int> mp2(vc.begin(), vc.end());
	// 	ft::map<int, int> mymp1(map1.begin(), map1.end());
	// 	ft::map<int, int> mymp2(vc.begin(), vc.end());

	// 	mp1.swap(mp2);
	// 	mymp1.swap(mymp2);
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(contToString(mp2), contToString(mymp2));
	// }

	// void unique_test() {
	// 	std::vector<int> vec;
	// 	for (int i = 0; i < 20; i++) vec.push_back(rand() % 10);

	// 	std::map<int, int> mp1(vec.begin(), vec.end());
	// 	ft::map<int, int> mymp1(vec.begin(), vec.end());

	// 	mp1.unique();
	// 	mymp1.unique();
	// 	ASSERT_EQUAL(contToString(mp1), contToString(mymp1));
	// 	ASSERT_EQUAL(mp1.size(), mymp1.size());
	// }

	// void operators_test() {
	// 	std::map<int, int> mp1, mp2;
	// 	ft::map<int, int> mymp1, mymp2;

	// 	int arr_str[][7] = {{1,2,3,4,-1}, {1,2,3,4,4,-1},
	// 					{1,2,3,1,4,1,-1}, {1,2,3,4,5,-1},
	// 					{0,2,3,4,5,6,-1}, {0,-1}};
	// 	std::vector<int> v[6];
	// 	for (int i = 0; i < 6; i++) {
	// 		for (int j = 0; arr_str[i][j] != -1; j++) {
	// 			v[i].push_back(arr_str[i][j]);
	// 		}
	// 	}

	// 	for (int i = 0; i < 6; i++) {
	// 		mp1.assign(v[i].begin(), v[i].end());
	// 		mymp1.assign(v[i].begin(), v[i].end());
	// 	for (int j = 0; j < 6; j++) {
	// 			mp2.assign(v[j].begin(), v[j].end());
	// 			mymp2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(mp1 == mp2, mymp1 == mymp2);
	// 		}
	// 	}

	// 	for (int i = 0; i < 6; i++) {
	// 		mp1.assign(v[i].begin(), v[i].end());
	// 		mymp1.assign(v[i].begin(), v[i].end());
	// 		for (int j = 0; j < 6; j++) {
	// 			mp2.assign(v[j].begin(), v[j].end());
	// 			mymp2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(mp1 != mp2, mymp1 != mymp2);
	// 		}
	// 	}

	// 	for (int i = 0; i < 6; i++) {
	// 		mp1.assign(v[i].begin(), v[i].end());
	// 		mymp1.assign(v[i].begin(), v[i].end());
	// 		for (int j = 0; j < 6; j++) {
	// 			mp2.assign(v[j].begin(), v[j].end());
	// 			mymp2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(mp1 < mp2, mymp1 < mymp2);
	// 		}
	// 	}

	// 	for (int i = 0; i < 6; i++) {
	// 		mp1.assign(v[i].begin(), v[i].end());
	// 		mymp1.assign(v[i].begin(), v[i].end());
	// 		for (int j = 0; j < 6; j++) {
	// 			mp2.assign(v[j].begin(), v[j].end());
	// 			mymp2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(mp1 <= mp2, mymp1 <= mymp2);
	// 		}
	// 	}

	// 	for (int i = 0; i < 6; i++) {
	// 		mp1.assign(v[i].begin(), v[i].end());
	// 		mymp1.assign(v[i].begin(), v[i].end());
	// 		for (int j = 0; j < 6; j++) {
	// 			mp2.assign(v[j].begin(), v[j].end());
	// 			mymp2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(mp1 > mp2, mymp1 > mymp2);
	// 		}
	// 	}

	// 		for (int i = 0; i < 6; i++) {
	// 		mp1.assign(v[i].begin(), v[i].end());
	// 		mymp1.assign(v[i].begin(), v[i].end());
	// 		for (int j = 0; j < 6; j++) {
	// 			mp2.assign(v[j].begin(), v[j].end());
	// 			mymp2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(mp1 >= mp2, mymp1 >= mymp2);
	// 		}
	// 	}
		
	// }
}