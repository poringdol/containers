#include <list>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include "tests.hpp"
#include "test_runner.h"
#include "vector.hpp"

/*********************************************************************/
/*								TESTS								 */
/*********************************************************************/
namespace ft_vector
{
	void constructorDefault_test() {

		ft::vector<int> myvc1;
		ASSERT_EQUAL(0u, myvc1.size());
		ASSERT_EQUAL(0u, myvc1.capacity());


		ft::vector<int> myvc2(myvc1);
		ASSERT_EQUAL(0u, myvc2.size());
		ASSERT_EQUAL(0u, myvc2.capacity());

		ft::vector<int> myvc3 = myvc1;
		ASSERT_EQUAL(0u, myvc3.size());
		ASSERT_EQUAL(0u, myvc3.capacity());
	}

	void constructorCopy_test() {
		std::vector<std::string> vc1(10, "Kto tut?");
		ft::vector<std::string> myvc1(10, "Kto tut?");

		std::vector<std::string> vc2(vc1);
		ft::vector<std::string> myvc2(myvc1);
		ASSERT_EQUAL(vc2.size(), myvc2.size());
		ASSERT_EQUAL(vc2.capacity(), myvc2.capacity());
		ASSERT_EQUAL(contToString(vc2), contToString(myvc2));

		std::vector<std::string> vc3 = vc2;
		ft::vector<std::string> myvc3 = myvc2;
		ASSERT_EQUAL(vc3.size(), myvc3.size());
		ASSERT_EQUAL(vc3.capacity(), myvc3.capacity());
		ASSERT_EQUAL(contToString(vc3), contToString(myvc3));
	}

	void constructorFill_test() {
		
		std::vector<int> vc1(10, 15);
		ft::vector<int> myvc1(10, 15);
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

		std::vector<char> vc2(10, 'X');
		ft::vector<char> myvc2(10, 'X');
		ASSERT_EQUAL(vc2.size(), myvc2.size());
		ASSERT_EQUAL(vc2.capacity(), myvc2.capacity());
		ASSERT_EQUAL(contToString(vc2), contToString(myvc2));

		std::vector<std::string> vc3(10, "Kto tut?");
		ft::vector<std::string> myvc3(10, "Kto tut?");
		ASSERT_EQUAL(vc3.size(), myvc3.size());
		ASSERT_EQUAL(vc3.capacity(), myvc3.capacity());
		ASSERT_EQUAL(contToString(vc3), contToString(myvc3));
	}

	void constructorRange_test() {

		ft::vector<int> myvc1(vc.begin(), vc.end());		// vector from std::vector
		ASSERT_EQUAL(vc.size(), myvc1.size());
		ASSERT_EQUAL(vc.capacity(), myvc1.capacity());
		ASSERT_EQUAL(contToString(vc), contToString(myvc1));


		ft::vector<int> myvc2(ls.begin(), ls.end());		// vector from std::list
		ASSERT_EQUAL(ls.size(), myvc2.size());
		ASSERT_EQUAL(contToString(ls), contToString(myvc2));

		ft::vector<int> myvc3(dq.begin(), dq.end());		// vector from std::deque
		ASSERT_EQUAL(dq.size(), myvc3.size());
		ASSERT_EQUAL(contToString(dq), contToString(myvc3));
	}

	void size_test() {

		ft::vector<int> myvc1;
		ASSERT_EQUAL(0u, myvc1.size());

		ft::vector<int> myvc2(vc.begin(), vc.end());
		ASSERT_EQUAL(10u, myvc2.size());
	}

	void empty_test() {

		ft::vector<int> myvc1;
		ASSERT_EQUAL(true, myvc1.empty());

		ft::vector<int> myvc2(vc.begin(), vc.end());
		ASSERT_EQUAL(false, myvc2.empty());
	}

	void max_size_test() {
		
		ft::vector<int> myvc;
		ASSERT_EQUAL(vc.max_size(), myvc.max_size());

		std::vector<double> vc2;
		ft::vector<double> myvc2;
		ASSERT_EQUAL(vc2.max_size(), myvc2.max_size());

		std::vector<std::string> vc3;
		ft::vector<std::string> myvc3;
		ASSERT_EQUAL(vc3.max_size(), myvc3.max_size());
	}

	void begin_test() {
		
		ft::vector<int> myvc(vc.begin(), vc.end());
		ft::vector<int>::iterator myit = myvc.begin();
		std::vector<int>::iterator it = vc.begin();
		ASSERT_EQUAL(*it, *myit);

		*it = 100;
		*myit = 100;
		ASSERT_EQUAL(*it, *myit);

		const ft::vector<int> myvc2(vc.begin(), vc.end());
		ft::vector<int>::const_iterator myit2 = myvc.begin();
		ASSERT_EQUAL(*myit2, 100);
		*it = 0;
	}

	void rbegin_rend_test() {

		ft::vector<int> myvc(vc.begin(), vc.end());
		ASSERT_EQUAL(contToString(vc), contToString(myvc));

		ft::vector<int> myrvc(vc.rbegin(), vc.rend());
		std::vector<int> rvc(vc.rbegin(), vc.rend());
		ASSERT_EQUAL(*rvc.rbegin(), *myrvc.rbegin());
		ASSERT_EQUAL(contToString(rvc), contToString(myrvc));
	}

	void front_back_test() {

		ft::vector<int> myvc(vc.begin(), vc.end());
		ASSERT_EQUAL(contToString(vc), contToString(myvc));

		ASSERT_EQUAL(vc.front(), myvc.front());
		ASSERT_EQUAL(vc.back(), myvc.back());
	}

	void assign_range_test() {

		ft::vector<int> myvc;								// assign to empty vector
		myvc.assign(vc.begin(), vc.end());
		ASSERT_EQUAL(contToString(vc), contToString(myvc));

		myvc.assign(vc.rbegin(), vc.rend());				// assign from equal size vector
		std::vector<int> rvc;
		rvc.assign(vc.rbegin(), vc.rend());
		ASSERT_EQUAL(contToString(rvc), contToString(myvc));

		std::vector<int> smaller(5, 5);						// assign from smaller vector
		rvc.assign(smaller.begin(), smaller.end());
		myvc.assign(smaller.begin(), smaller.end());
		ASSERT_EQUAL(rvc.size(), myvc.size());
		ASSERT_EQUAL(rvc.capacity(), myvc.capacity());
		ASSERT_EQUAL(contToString(rvc), contToString(myvc));

		std::vector<int> bigger(25, 25);					// assign from bigger vector
		rvc.assign(bigger.begin(), bigger.end());
		myvc.assign(bigger.begin(), bigger.end());
		ASSERT_EQUAL(rvc.size(), myvc.size());
		ASSERT_EQUAL(rvc.capacity(), myvc.capacity());
		ASSERT_EQUAL(contToString(rvc), contToString(myvc));

		myvc.assign(ls.begin(), ls.end());					// assign from std::list
		ASSERT_EQUAL(contToString(ls), contToString(myvc));

		myvc.assign(dq.begin(), dq.end());					// assign from std::deque
		ASSERT_EQUAL(contToString(dq), contToString(myvc));
	}

	// void assign_fill_test() {

	// 	std::vector<int> avc;
	// 	avc.assign(18, 100);
	// 	ft::vector<int> myvc;
	// 	myvc.assign(18, 100);
	// 	ASSERT_EQUAL(contToString(avc), contToString(myvc));

	// 	std::vector<double> avc2;
	// 	avc2.assign(20, 100.);
	// 	ft::vector<double> myvc2;
	// 	myvc2.assign(20, 100.);
	// 	ASSERT_EQUAL(contToString(avc2), contToString(myvc2));

	// 	std::vector<std::string> avc3;
	// 	avc3.assign(22, "Fart");
	// 	ft::vector<std::string> myvc3;
	// 	myvc3.assign(22, "Fart");
	// 	ASSERT_EQUAL(contToString(avc3), contToString(myvc3));
	// }

	// void sort_test() {

	// 	std::vector<int> vect;
	// 	for (int i = 0; i < 10; i++) { vect.push_back(rand() % 100); }

	// 	std::vector<int> svc(vect.begin(), vect.end());
	// 	ft::vector<int> myvc(vect.begin(), vect.end());
	// 	ASSERT_EQUAL(contToString(svc), contToString(myvc));

	// 	svc.sort();
	// 	myvc.sort();
	// 	ASSERT_EQUAL(contToString(svc), contToString(myvc));
	// }

	// bool mycomparison (int first, int second) { return (first % 2) < (second % 2); }

	// void sort_compare_test() {

	// 	std::vector<int> evc;
	// 	ft::vector<int> myevc;
	// 	evc.sort(mycomparison);
	// 	myevc.sort(mycomparison);
	// 	ASSERT_EQUAL(contToString(evc), contToString(myevc));

	// 	std::vector<int> vect;
	// 	for (int i = 0; i < 10; i++) { vect.push_back(rand() % 100); }

	// 	std::vector<int> svc(vect.begin(), vect.end());
	// 	ft::vector<int> myvc(vect.begin(), vect.end());
	// 	ASSERT_EQUAL(contToString(svc), contToString(myvc));

	// 	svc.sort(mycomparison);
	// 	myvc.sort(mycomparison);
	// 	ASSERT_EQUAL(contToString(svc), contToString(myvc));
	// }

	// void merge_test() {
	// 	std::vector<int> vect1;
	// 	std::vector<int> vect2;
	// 	for (int i = 0; i < 10; i++) { vect1.push_back(rand() % 100); }
	// 	for (int i = 0; i < 10; i++) { vect2.push_back(rand() % 100); }

	// 	std::vector<int> vc1(vect1.begin(), vect1.end());
	// 	std::vector<int> vc2(vect2.begin(), vect2.end());
	// 	vc1.sort();
	// 	vc2.sort();

	// 	ft::vector<int> myvc1(vect1.begin(), vect1.end());
	// 	ft::vector<int> myvc2(vect2.begin(), vect2.end());
	// 	myvc1.sort();
	// 	myvc2.sort();

	// 	vc1.merge(vc2);
	// 	myvc1.merge(myvc2);
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(contToString(vc2), contToString(myvc2));

	// // merge compare
	// 	vc2.assign(vect1.begin(), vect1.end());
	// 	myvc2.assign(vect1.begin(), vect1.end());
	// 	vc2.sort();
	// 	myvc2.sort();

	// 	vc1.merge(vc2, mycomparison);
	// 	myvc1.merge(myvc2, mycomparison);
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(contToString(vc2), contToString(myvc2));
	// }

	// void splice_test() {

	// // splice (iterator position, list& x)
	// 	std::vector<int> vc1(vc.begin(), vc.end());
	// 	std::vector<int> vc2(vc.begin(), vc.end());

	// 	ft::vector<int> myvc1(vc.begin(), vc.end());
	// 	ft::vector<int> myvc2(vc.begin(), vc.end());

	// 	vc1.splice(++(vc1.begin()), vc2);
	// 	myvc1.splice(++(myvc1.begin()), myvc2);

	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(contToString(vc2), contToString(myvc2));

	// // splice (iterator position, list& x, iterator i)
	// 	vc2.assign(vc.begin(), vc.end());
	// 	myvc2.assign(vc.begin(), vc.end());

	// 	vc1.splice(vc1.begin(), vc2, ++(vc2.begin()));
	// 	myvc1.splice(myvc1.begin(), myvc2, ++(myvc2.begin()));

	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(contToString(vc2), contToString(myvc2));

	// // splice (iterator position, list& x, iterator first, iterator last)
	// 	vc2.assign(vc.begin(), vc.end());
	// 	myvc2.assign(vc.begin(), vc.end());

	// 	vc1.splice(vc1.begin(), vc2, vc2.begin(), vc2.end());
	// 	myvc1.splice(myvc1.begin(), myvc2, myvc2.begin(), myvc2.end());

	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(contToString(vc2), contToString(myvc2));
	// }

	// void insert_test() {
	// 	std::vector<int> vc1(vc.begin(), vc.end());
	// 	ft::vector<int> myvc1(vc.begin(), vc.end());

	// // insert (iterator position, const T& data)
	// 	std::vector<int>::iterator it = vc1.insert(++(vc1.begin()), 100);
	// 	ft::vector<int>::iterator  myit = myvc1.insert(++(myvc1.begin()), 100);
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(*it, *myit);

	// // insert (iterator position, size_t n, const T& val)
	// 	vc1.insert(++(vc1.begin()), 10, 150);
	// 	myvc1.insert(++(myvc1.begin()), 10, 150);
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

	// // insert (iterator position, InputIterator first, InputIterator last)
	// 	vc1.insert(vc1.begin(), vc.begin(), vc.end());
	// 	myvc1.insert(myvc1.begin(), vc.begin(), vc.end());
	// }

	// void push_back_front_test() {
	// 	std::vector<int> vc1;
	// 	ft::vector<int> myvc1;

	// 	vc1.push_back(12);
	// 	myvc1.push_back(12);
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

	// 	vc1.push_back(17);
	// 	myvc1.push_back(17);
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

	// 	vc1.push_front(11);
	// 	myvc1.push_front(11);
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// }

	// void pop_back_front_test() {
	// 	std::vector<int> vc1;
	// 	ft::vector<int> myvc1;

	// // test with empty list
	// 	// vc1.pop_front();
	// 	// myvc1.pop_front();
	// 	// ASSERT_EQUAL(vc1.size(), myvc1.size());

	// 	// vc1.pop_back();
	// 	// myvc1.pop_back();
	// 	// ASSERT_EQUAL(vc1.size(), myvc1.size());

	// // test with not empty list
	// 	vc1.assign(vc.begin(), vc.end());
	// 	myvc1.assign(vc.begin(), vc.end());

	// 	vc1.pop_back();
	// 	myvc1.pop_back();
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(vc1.size(), myvc1.size());

	// 	vc1.pop_front();
	// 	myvc1.pop_front();
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(vc1.size(), myvc1.size());
	// }

	// void resize_test() {
	// 	std::vector<int> vc1;
	// 	ft::vector<int> myvc1;

	// 	vc1.resize(12, 1);
	// 	myvc1.resize(12, 1);
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(vc1.size(), myvc1.size());

	// 	vc1.resize(17, 2);
	// 	myvc1.resize(17, 2);
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(vc1.size(), myvc1.size());

	// 	vc1.resize(8, 3);
	// 	myvc1.resize(8, 3);
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(vc1.size(), myvc1.size());
	// }

	// void clear_test() {
	// 	std::vector<int> vc1(vc.begin(), vc.end());
	// 	ft::vector<int> myvc1(vc.begin(), vc.end());

	// 	vc1.clear();
	// 	myvc1.clear();
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(vc1.size(), myvc1.size());

	// 	vc1.clear();
	// 	myvc1.clear();
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(vc1.size(), myvc1.size());
	// }

	// void erase_test() {
	// 	std::vector<int> vc1(vc.begin(), vc.end());
	// 	ft::vector<int> myvc1(vc.begin(), vc.end());

	// 	vc1.erase(++(vc1.begin()));
	// 	myvc1.erase(++(myvc1.begin()));
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

	// 	vc1.erase(--(vc1.end()));
	// 	myvc1.erase(--(myvc1.end()));
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

	// 	vc1.erase(++(vc1.begin()), vc1.end());
	// 	myvc1.erase(++(myvc1.begin()), myvc1.end());
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(vc1.size(), myvc1.size());
	// }

	// void remove_test() {
	// 	std::vector<int> vc1(vc.begin(), vc.end());
	// 	ft::vector<int> myvc1(vc.begin(), vc.end());

	// 	vc1.remove(5);
	// 	myvc1.remove(5);
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(vc1.size(), myvc1.size());

	// 	vc1.remove(105);
	// 	myvc1.remove(105);
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(vc1.size(), myvc1.size());
	// }

	// bool single_digit (const int& value) { return (value<5); }

	// struct is_odd {
	// bool operator() (const int& value) { return (value%2)==1; }
	// };

	// void remove_if_test() {
	// 	std::vector<int> vc1(vc.begin(), vc.end());
	// 	ft::vector<int> myvc1(vc.begin(), vc.end());

	// 	vc1.remove_if(single_digit);
	// 	myvc1.remove_if(single_digit);
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

	// 	vc1.remove_if(is_odd());
	// 	myvc1.remove_if(is_odd());
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// }

	// void swap_test() {
	// 	std::vector<int> vc1(vc.begin(), vc.end());
	// 	std::vector<int> vc2(vc.begin(), vc.end());
	// 	ft::vector<int> myvc1(vc.begin(), vc.end());
	// 	ft::vector<int> myvc2(vc.begin(), vc.end());

	// 	vc1.swap(vc2);
	// 	myvc1.swap(myvc2);
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(contToString(vc2), contToString(myvc2));
	// }

	// void unique_test() {
	// 	std::vector<int> vec;
	// 	for (int i = 0; i < 20; i++) vec.push_back(rand() % 10);

	// 	std::vector<int> vc1(vec.begin(), vec.end());
	// 	ft::vector<int> myvc1(vec.begin(), vec.end());

	// 	vc1.unique();
	// 	myvc1.unique();
	// 	ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	// 	ASSERT_EQUAL(vc1.size(), myvc1.size());
	// }

	// void operators_test() {
	// 	std::vector<int> vc1, vc2;
	// 	ft::vector<int> myvc1, myvc2;

	// 	std::vector<int> v[6] = {{1,2,3,4}, {1,2,3,4,4},
	// 							{1,2,3,1,4,1}, {1,2,3,4,5},
	// 							{0,2,3,4,5,6}, {0}};

	// 	for (int i = 0; i < 6; i++) {
	// 		vc1.assign(v[i].begin(), v[i].end());
	// 		myvc1.assign(v[i].begin(), v[i].end());
	// 	for (int j = 0; j < 6; j++) {
	// 			vc2.assign(v[j].begin(), v[j].end());
	// 			myvc2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(vc1 == vc2, myvc1 == myvc2);
	// 		}
	// 	}

	// 	for (int i = 0; i < 6; i++) {
	// 		vc1.assign(v[i].begin(), v[i].end());
	// 		myvc1.assign(v[i].begin(), v[i].end());
	// 		for (int j = 0; j < 6; j++) {
	// 			vc2.assign(v[j].begin(), v[j].end());
	// 			myvc2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(vc1 != vc2, myvc1 != myvc2);
	// 		}
	// 	}

	// 	for (int i = 0; i < 6; i++) {
	// 		vc1.assign(v[i].begin(), v[i].end());
	// 		myvc1.assign(v[i].begin(), v[i].end());
	// 		for (int j = 0; j < 6; j++) {
	// 			vc2.assign(v[j].begin(), v[j].end());
	// 			myvc2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(vc1 < vc2, myvc1 < myvc2);
	// 		}
	// 	}

	// 	for (int i = 0; i < 6; i++) {
	// 		vc1.assign(v[i].begin(), v[i].end());
	// 		myvc1.assign(v[i].begin(), v[i].end());
	// 		for (int j = 0; j < 6; j++) {
	// 			vc2.assign(v[j].begin(), v[j].end());
	// 			myvc2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(vc1 <= vc2, myvc1 <= myvc2);
	// 		}
	// 	}

	// 	for (int i = 0; i < 6; i++) {
	// 		vc1.assign(v[i].begin(), v[i].end());
	// 		myvc1.assign(v[i].begin(), v[i].end());
	// 		for (int j = 0; j < 6; j++) {
	// 			vc2.assign(v[j].begin(), v[j].end());
	// 			myvc2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(vc1 > vc2, myvc1 > myvc2);
	// 		}
	// 	}

	// 		for (int i = 0; i < 6; i++) {
	// 		vc1.assign(v[i].begin(), v[i].end());
	// 		myvc1.assign(v[i].begin(), v[i].end());
	// 		for (int j = 0; j < 6; j++) {
	// 			vc2.assign(v[j].begin(), v[j].end());
	// 			myvc2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(vc1 >= vc2, myvc1 >= myvc2);
	// 		}
	// 	}
		
	// }
}