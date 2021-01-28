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

		std::vector<std::string> g_vc2(vc1);
		ft::vector<std::string> myvc2(myvc1);
		ASSERT_EQUAL(g_vc2.size(), myvc2.size());
		ASSERT_EQUAL(g_vc2.capacity(), myvc2.capacity());
		ASSERT_EQUAL(contToString(g_vc2), contToString(myvc2));

		std::vector<std::string> vc3 = g_vc2;
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

		std::vector<char> g_vc2(10, 'X');
		ft::vector<char> myvc2(10, 'X');
		ASSERT_EQUAL(g_vc2.size(), myvc2.size());
		ASSERT_EQUAL(g_vc2.capacity(), myvc2.capacity());
		ASSERT_EQUAL(contToString(g_vc2), contToString(myvc2));

		std::vector<std::string> vc3(10, "Kto tut?");
		ft::vector<std::string> myvc3(10, "Kto tut?");
		ASSERT_EQUAL(vc3.size(), myvc3.size());
		ASSERT_EQUAL(vc3.capacity(), myvc3.capacity());
		ASSERT_EQUAL(contToString(vc3), contToString(myvc3));
	}

	void constructorRange_test() {

		ft::vector<int> myvc1(g_vc.begin(), g_vc.end());		// vector from std::vector
		ASSERT_EQUAL(g_vc.size(), myvc1.size());
		ASSERT_EQUAL(g_vc.capacity(), myvc1.capacity());
		ASSERT_EQUAL(contToString(g_vc), contToString(myvc1));

		ft::vector<int> myvc2(g_ls.begin(), g_ls.end());		// vector from std::list
		ASSERT_EQUAL(g_ls.size(), myvc2.size());
		ASSERT_EQUAL(contToString(g_ls), contToString(myvc2));

		ft::vector<int> myvc3(g_dq.begin(), g_dq.end());		// vector from std::deque
		ASSERT_EQUAL(g_dq.size(), myvc3.size());
		ASSERT_EQUAL(contToString(g_dq), contToString(myvc3));

		ft::vector<std::string> myvc4(g_str.begin(), g_str.end());		// vector from std::vector
		ASSERT_EQUAL(g_str.size(), myvc4.size());
		ASSERT_EQUAL(g_str.capacity(), myvc4.capacity());
		ASSERT_EQUAL(contToString(g_str), contToString(myvc4));
	}

	void size_test() {

		ft::vector<int> myvc1;
		ASSERT_EQUAL(0u, myvc1.size());

		ft::vector<int> myvc2(g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(g_vc.size(), myvc2.size());
	}

	void empty_test() {

		ft::vector<int> myvc1;
		ASSERT_EQUAL(true, myvc1.empty());

		ft::vector<int> myvc2(g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(false, myvc2.empty());
	}

	void max_size_test() {
		
		ft::vector<int> myvc;
		ASSERT_EQUAL(g_vc.max_size(), myvc.max_size());

		std::vector<double> g_vc2;
		ft::vector<double> myvc2;
		ASSERT_EQUAL(g_vc2.max_size(), myvc2.max_size());

		std::vector<std::string> vc3;
		ft::vector<std::string> myvc3;
		ASSERT_EQUAL(vc3.max_size(), myvc3.max_size());
	}

	void begin_test() {
		
		ft::vector<int> myvc(g_vc.begin(), g_vc.end());
		ft::vector<int>::iterator myit = myvc.begin();
		std::vector<int>::iterator it = g_vc.begin();
		ASSERT_EQUAL(*it, *myit);

		*it = 100;
		*myit = 100;
		ASSERT_EQUAL(*it, *myit);

		const ft::vector<int> myvc2(g_vc.begin(), g_vc.end());
		ft::vector<int>::const_iterator myit2 = myvc.begin();
		ASSERT_EQUAL(*myit2, 100);
		*it = 15;
	}

	void rbegin_rend_test() {

		ft::vector<int> myvc(g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(contToString(g_vc), contToString(myvc));

		ft::vector<int> myrvc(g_vc.rbegin(), g_vc.rend());
		std::vector<int> rvc(g_vc.rbegin(), g_vc.rend());
		ASSERT_EQUAL(*rvc.rbegin(), *myrvc.rbegin());
		ASSERT_EQUAL(contToString(rvc), contToString(myrvc));
	}

	void front_back_test() {

		ft::vector<int> myvc(g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(contToString(g_vc), contToString(myvc));

		ASSERT_EQUAL(g_vc.front(), myvc.front());
		ASSERT_EQUAL(g_vc.back(), myvc.back());
	}

	void assign_range_test() {

		ft::vector<int> myvc;								// assign to empty vector
		myvc.assign(g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(contToString(g_vc), contToString(myvc));

		myvc.assign(g_vc.rbegin(), g_vc.rend());				// assign from equal size vector
		std::vector<int> rvc;
		rvc.assign(g_vc.rbegin(), g_vc.rend());
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

		myvc.assign(g_ls.begin(), g_ls.end());					// assign from std::list
		ASSERT_EQUAL(contToString(g_ls), contToString(myvc));

		myvc.assign(g_dq.begin(), g_dq.end());					// assign from std::deque
		ASSERT_EQUAL(contToString(g_dq), contToString(myvc));

		ft::vector<std::string> mystr;						// assign to empty vector
		std::vector<std::string> str1;
		mystr.assign(g_str.begin(), g_str.end());
		str1.assign(g_str.begin(), g_str.end());
		ASSERT_EQUAL(contToString(str1), contToString(mystr));
	}

	void assign_fill_test() {

		std::vector<int> avc;								// assign to empty vector
		avc.assign(18, 100);
		ft::vector<int> myvc;
		myvc.assign(18, 100);
		ASSERT_EQUAL(avc.size(), myvc.size());
		ASSERT_EQUAL(avc.capacity(), myvc.capacity());
		ASSERT_EQUAL(contToString(avc), contToString(myvc));

		avc.assign(28, 200);								// assign to smaller vector
		myvc.assign(28, 200);
		ASSERT_EQUAL(avc.size(), myvc.size());
		ASSERT_EQUAL(avc.capacity(), myvc.capacity());
		ASSERT_EQUAL(contToString(avc), contToString(myvc));

		avc.assign(8, 300);									// assign to bigger vector
		myvc.assign(8, 300);
		ASSERT_EQUAL(avc.size(), myvc.size());
		ASSERT_EQUAL(avc.capacity(), myvc.capacity());
		ASSERT_EQUAL(contToString(avc), contToString(myvc));

		std::vector<double> avc2;
		avc2.assign(20, 100.);
		ft::vector<double> myvc2;
		myvc2.assign(20, 100.);
		ASSERT_EQUAL(avc2.size(), myvc2.size());
		ASSERT_EQUAL(avc2.capacity(), myvc2.capacity());
		ASSERT_EQUAL(contToString(avc2), contToString(myvc2));

		std::vector<std::string> avc3;
		avc3.assign(22, "Fart");
		ft::vector<std::string> myvc3;
		myvc3.assign(22, "Fart");
		ASSERT_EQUAL(avc3.size(), myvc3.size());
		ASSERT_EQUAL(avc3.capacity(), myvc3.capacity());
		ASSERT_EQUAL(contToString(avc3), contToString(myvc3));
	}

	void at_test() {
		std::vector<int> g_vc;
		ft::vector<int> myvc;

		int except_count = 0;
		try { g_vc.at(0); } 
		catch (std::out_of_range& ex) { except_count++; }
		try { myvc.at(0); } 
		catch (std::out_of_range& ex) { except_count++; }
		ASSERT_EQUAL(except_count, 2);

		g_vc.assign(18, 100);
		myvc.assign(18, 100);
		ASSERT_EQUAL(g_vc.at(0), myvc.at(0));
		ASSERT_EQUAL(g_vc.at(10), myvc.at(10));
		ASSERT_EQUAL(g_vc.at(17), myvc.at(17));

		ASSERT_EQUAL(g_vc[0], myvc[0]);
		ASSERT_EQUAL(g_vc[5], myvc[5]);
		ASSERT_EQUAL(g_vc[17], myvc[17]);

		try { g_vc.at(18); } 
		catch (std::out_of_range& ex) { except_count++; }
		try { myvc.at(18); } 
		catch (std::out_of_range& ex) { except_count++; }
		ASSERT_EQUAL(except_count, 4);
	}

	void insert_range_test() {
		std::vector<int> src_3(3, 0);
		std::vector<int> src_50(50, 0);
		std::vector<int> src_15(15, 0);
		std::vector<int> src_10(10, 0);
		std::vector<int> src_25(25, 0);
		std::vector<int> src_200(200, 0);

		std::vector<int> vc1;
		ft::vector<int> myvc1;

	// insert (iterator position, InputIterator first, InputIterator last)
	// size() && capacity() at the beginning == 0
		vc1.insert(vc1.begin(), src_3.begin(), src_3.end());
		myvc1.insert(myvc1.begin(), src_3.begin(), src_3.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

	// total size() == capacity(), first size() == 0
		vc1.clear();
		myvc1.clear();
		vc1.insert(vc1.begin(), src_3.begin(), src_3.end());
		myvc1.insert(myvc1.begin(), src_3.begin(), src_3.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.clear();
		myvc1.clear();
		vc1.insert(vc1.end(), src_3.begin(), src_3.end());
		myvc1.insert(myvc1.end(), src_3.begin(), src_3.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

	// total size() > capacity(), size() != 0
		vc1.insert(vc1.begin(), src_10.begin(), src_10.end());
		myvc1.insert(myvc1.begin(), src_10.begin(), src_10.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

		vc1.insert(++vc1.begin(), src_3.begin(), src_3.end());
		myvc1.insert(++myvc1.begin(), src_3.begin(), src_3.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

		vc1.insert(vc1.end(), src_10.begin(), src_10.end());
		myvc1.insert(myvc1.end(), src_10.begin(), src_10.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	
	// total size() > capacity(), first size() == 0
		vc1.clear();
		myvc1.clear();
		vc1.insert(vc1.begin(), src_50.begin(), src_50.end());
		myvc1.insert(myvc1.begin(), src_50.begin(), src_50.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.clear();
		myvc1.clear();
		vc1.insert(vc1.end(), src_50.begin(), src_50.end());
		myvc1.insert(myvc1.end(), src_50.begin(), src_50.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

	// total size() < capacity(), first size() == 0
		vc1.clear();
		myvc1.clear();
		vc1.insert(vc1.begin(), src_3.begin(), src_3.end());
		myvc1.insert(myvc1.begin(), src_3.begin(), src_3.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.clear();
		myvc1.clear();
		vc1.insert(vc1.end(), src_3.begin(), src_3.end());
		myvc1.insert(myvc1.end(), src_3.begin(), src_3.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

	// total size() < capacity(), first size() != 0
		vc1.insert(vc1.begin(), src_15.begin(), src_15.end());
		myvc1.insert(myvc1.begin(), src_15.begin(), src_15.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.insert(vc1.end(), src_15.begin(), src_15.end());
		myvc1.insert(myvc1.end(), src_15.begin(), src_15.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

	// total size() == capacity(), first size() != 0
		vc1.clear();
		myvc1.clear();
		vc1.insert(vc1.begin(), src_25.begin(), src_25.end());
		myvc1.insert(myvc1.begin(), src_25.begin(), src_25.end());
		vc1.insert(vc1.begin(), src_25.begin(), src_25.end());
		myvc1.insert(myvc1.begin(), src_25.begin(), src_25.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.clear();
		myvc1.clear();
		vc1.insert(vc1.begin(), src_25.begin(), src_25.end());
		myvc1.insert(myvc1.begin(), src_25.begin(), src_25.end());
		vc1.insert(vc1.end(), src_25.begin(), src_25.end());
		myvc1.insert(myvc1.end(), src_25.begin(), src_25.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.insert(vc1.end(), src_25.begin(), src_25.end());
		myvc1.insert(myvc1.end(), src_25.begin(), src_25.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		vc1.insert(vc1.end(), src_200.begin(), src_200.end());
		myvc1.insert(myvc1.end(), src_200.begin(), src_200.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		std::vector<std::string> str1;
		ft::vector<std::string> mystr;
		str1.insert(str1.begin(), g_str.begin(), g_str.end());
		mystr.insert(mystr.begin(), g_str.begin(), g_str.end());
		ASSERT_EQUAL(str1.size(), mystr.size());
		ASSERT_EQUAL(str1.capacity(), mystr.capacity());
		ASSERT_EQUAL(contToString(str1), contToString(mystr));

		str1.clear();
		mystr.clear();
		str1.insert(str1.begin(), g_str.begin(), g_str.end());
		mystr.insert(mystr.begin(), g_str.begin(), g_str.end());
		ASSERT_EQUAL(str1.size(), mystr.size());
		ASSERT_EQUAL(str1.capacity(), mystr.capacity());
		ASSERT_EQUAL(contToString(str1), contToString(mystr));

		str1.insert(str1.begin(), g_str.begin(), g_str.end());
		mystr.insert(mystr.begin(), g_str.begin(), g_str.end());
		ASSERT_EQUAL(str1.size(), mystr.size());
		ASSERT_EQUAL(str1.capacity(), mystr.capacity());
		ASSERT_EQUAL(contToString(str1), contToString(mystr));
	}

	void insert_fill_test() {
		std::vector<int> vc1;
		ft::vector<int> myvc1;

		vc1.insert(vc1.begin(), 5, 0);
		myvc1.insert(myvc1.begin(), 5, 0);
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

		vc1.clear();
		myvc1.clear();
		vc1.insert(vc1.begin(), 5, 0);
		myvc1.insert(myvc1.begin(), 5, 0);
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

		vc1.insert(vc1.begin(), 3, 0);
		myvc1.insert(myvc1.begin(), 3, 0);
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

		vc1.insert(vc1.begin(), 12, 0);
		myvc1.insert(myvc1.begin(), 12, 0);
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

		vc1.insert(++(vc1.begin()), 10, 0);
		myvc1.insert(++(myvc1.begin()), 10, 0);
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

		vc1.insert(++(vc1.begin()), 60, 0);
		myvc1.insert(++(myvc1.begin()), 60, 0);
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

		vc1.insert(vc1.end(), 300, 0);
		myvc1.insert(myvc1.end(), 300, 0);
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

		vc1.insert(vc1.end(), 10, 0);
		myvc1.insert(myvc1.end(), 10, 0);
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
	}

	void insert_element_test() {
		std::vector<int> vc1;
		std::vector<int>::iterator it1;
		ft::vector<int> myvc1;
		ft::vector<int>::iterator it2;

		for (int i = 0; i < 5; i++) {
			it1 = vc1.insert(vc1.begin(), 0);
			it2 = myvc1.insert(myvc1.begin(), 0);

			ASSERT_EQUAL(*it1, *it2);
			ASSERT_EQUAL(vc1.size(), myvc1.size());
			ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
			ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		}

		for (int i = 0; i < 5; i++) {
			it1 = vc1.insert(++(vc1.begin()), 0);
			it2 = myvc1.insert(++(myvc1.begin()), 0);
			ASSERT_EQUAL(*it1, *it2);
			ASSERT_EQUAL(vc1.size(), myvc1.size());
			ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
			ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		}

		for (int i = 0; i < 5; i++) {
			it1 = vc1.insert(--vc1.end(), 0);
			it2 = myvc1.insert(--myvc1.end(), 0);
			ASSERT_EQUAL(*it1, *it2);
			ASSERT_EQUAL(vc1.size(), myvc1.size());
			ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
			ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		}

		std::vector<std::string> g_vc2;
		std::vector<std::string>::iterator it3;
		ft::vector<std::string> myvc2;
		ft::vector<std::string>::iterator it4;
		std::string str("Burunduk");

		for (int i = 0; i < 5; i++) {
			it3 = g_vc2.insert(g_vc2.begin(), str);
			it4 = myvc2.insert(myvc2.begin(), str);
			ASSERT_EQUAL(*it3, *it4);
			ASSERT_EQUAL(g_vc2.size(), myvc2.size());
			ASSERT_EQUAL(g_vc2.capacity(), myvc2.capacity());
			ASSERT_EQUAL(contToString(g_vc2), contToString(myvc2));
		}
	}

	void push_back_test() {
		std::vector<int> vc1;
		ft::vector<int> myvc1;
		for (int i = 0; i < 14; i++) {
			vc1.push_back(i);
			myvc1.push_back(i);
			ASSERT_EQUAL(vc1.size(), myvc1.size());
			ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
			ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		}
	}

	void pop_back_test() {
		std::vector<int> vc1;
		ft::vector<int> myvc1;

		vc1.assign(g_vc.begin(), g_vc.end());
		myvc1.assign(g_vc.begin(), g_vc.end());

		vc1.pop_back();
		myvc1.pop_back();
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.pop_back();
		myvc1.pop_back();
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.pop_back();
		myvc1.pop_back();
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.pop_back();
		myvc1.pop_back();
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
	}

	void reserve_test() {
		std::vector<int> vc1;
		ft::vector<int> myvc1;
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.reserve(2);
		myvc1.reserve(2);
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.reserve(12);
		myvc1.reserve(12);
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		
		vc1.reserve(5);
		myvc1.reserve(5);
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.insert(vc1.begin(), g_vc.begin(), g_vc.end());
		myvc1.insert(myvc1.begin(), g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.reserve(5);
		myvc1.reserve(5);
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		
		vc1.reserve(15);
		myvc1.reserve(15);
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
	}

	void resize_test() {
		std::vector<int> vc1;
		ft::vector<int> myvc1;

		vc1.resize(2, 0);
		myvc1.resize(2, 0);
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.resize(12, 1);
		myvc1.resize(12, 1);
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.assign(g_vc.begin(), g_vc.end());
		myvc1.assign(g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.resize(17, 2);
		myvc1.resize(17, 2);
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.insert(vc1.begin(), g_vc.begin(), g_vc.end());
		myvc1.insert(myvc1.begin(), g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.resize(8, 3);
		myvc1.resize(8, 3);
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.resize(18, 4);
		myvc1.resize(18, 4);
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.resize(19, 5);
		myvc1.resize(19, 5);
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.resize(36, 6);
		myvc1.resize(36, 6);
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		std::vector<std::string> g_vc2;
		ft::vector<std::string> myvc2;

		g_vc2.resize(2, "1_zero");
		myvc2.resize(2, "1_zero");
		ASSERT_EQUAL(contToString(g_vc2), contToString(myvc2));
		ASSERT_EQUAL(g_vc2.size(), myvc2.size());
		ASSERT_EQUAL(g_vc2.capacity(), myvc2.capacity());

		g_vc2.resize(12, "2_one");
		myvc2.resize(12, "2_one");
		ASSERT_EQUAL(contToString(g_vc2), contToString(myvc2));
		ASSERT_EQUAL(g_vc2.size(), myvc2.size());
		ASSERT_EQUAL(g_vc2.capacity(), myvc2.capacity());

		g_vc2.assign(g_str.begin(), g_str.end());
		myvc2.assign(g_str.begin(), g_str.end());
		ASSERT_EQUAL(contToString(g_vc2), contToString(myvc2));
		ASSERT_EQUAL(g_vc2.size(), myvc2.size());
		ASSERT_EQUAL(g_vc2.capacity(), myvc2.capacity());

		g_vc2.resize(17, "3_two");
		myvc2.resize(17, "3_two");
		ASSERT_EQUAL(contToString(g_vc2), contToString(myvc2));
		ASSERT_EQUAL(g_vc2.size(), myvc2.size());
		ASSERT_EQUAL(g_vc2.capacity(), myvc2.capacity());

		g_vc2.insert(g_vc2.begin(), g_str.begin(), g_str.end());
		myvc2.insert(myvc2.begin(), g_str.begin(), g_str.end());
		ASSERT_EQUAL(contToString(g_vc2), contToString(myvc2));
		ASSERT_EQUAL(g_vc2.size(), myvc2.size());
		ASSERT_EQUAL(g_vc2.capacity(), myvc2.capacity());

		g_vc2.resize(8, "4_three");
		myvc2.resize(8, "4_three");
		ASSERT_EQUAL(contToString(g_vc2), contToString(myvc2));
		ASSERT_EQUAL(g_vc2.size(), myvc2.size());
		ASSERT_EQUAL(g_vc2.capacity(), myvc2.capacity());
	}

	void clear_test() {
		std::vector<int> vc1(g_vc.begin(), g_vc.end());
		ft::vector<int> myvc1(g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.clear();
		myvc1.clear();
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());

		vc1.clear();
		myvc1.clear();
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
	}

	void erase_test() {
		std::vector<int> vc1(g_vc.begin(), g_vc.end());
		ft::vector<int> myvc1(g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

		std::vector<int>::iterator it1 = vc1.erase(++(vc1.begin()));
		ft::vector<int>::iterator it2 = myvc1.erase(++(myvc1.begin()));
		ASSERT_EQUAL(*it1, *it2);
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());

		it1 = vc1.erase(--(vc1.end()));
		it2 = myvc1.erase(--(myvc1.end()));
		ASSERT_EQUAL(true, it1 == vc1.end());
		ASSERT_EQUAL(true, it2 == myvc1.end());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));

		it1 = vc1.erase(vc1.begin() + 4, vc1.end());
		it2 = myvc1.erase(myvc1.begin() + 4, myvc1.end());
		ASSERT_EQUAL(*it1, *it2);
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());

		it1 = vc1.erase(++(vc1.begin()), vc1.end());
		it2 = myvc1.erase(++(myvc1.begin()), myvc1.end());
		ASSERT_EQUAL(*it1, *it2);
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());

		it1 = vc1.erase(vc1.begin(), vc1.end());
		it2 = myvc1.erase(myvc1.begin(), myvc1.end());
		ASSERT_EQUAL(true, it1 == vc1.end());
		ASSERT_EQUAL(true, it2 == myvc1.end());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(vc1.size(), myvc1.size());
	}

	void swap_test() {
		std::vector<int> vc1(g_vc.rbegin(), g_vc.rend());
		ft::vector<int> myvc1(g_vc.rbegin(), g_vc.rend());
		std::vector<int> g_vc2(g_vc.begin(), g_vc.end());
		ft::vector<int> myvc2(g_vc.begin(), g_vc.end());
		vc1.pop_back();
		myvc1.pop_back();

		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		ASSERT_EQUAL(g_vc2.size(), myvc2.size());
		ASSERT_EQUAL(g_vc2.capacity(), myvc2.capacity());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(contToString(g_vc2), contToString(myvc2));

		vc1.swap(g_vc2);
		myvc1.swap(myvc2);
		ASSERT_EQUAL(vc1.size(), myvc1.size());
		ASSERT_EQUAL(vc1.capacity(), myvc1.capacity());
		ASSERT_EQUAL(g_vc2.size(), myvc2.size());
		ASSERT_EQUAL(g_vc2.capacity(), myvc2.capacity());
		ASSERT_EQUAL(contToString(vc1), contToString(myvc1));
		ASSERT_EQUAL(contToString(g_vc2), contToString(myvc2));
	}

	void operators_test() {
		std::vector<int> vc1, g_vc2;
		ft::vector<int> myvc1, myvc2;

		int arr_str[][7] = {{1,2,3,4,-1}, {1,2,3,4,4,-1},
								{1,2,3,1,4,1,-1}, {1,2,3,4,5,-1},
								{0,2,3,4,5,6,-1}, {0,-1}};
		std::vector<int> v[6];
		for (int i = 0; i < 6; i++) {
			for (int j = 0; arr_str[i][j] != -1; j++) {
				v[i].push_back(arr_str[i][j]);
			}
		}

		// cout << contToString(v[0]) << endl;
		// cout << contToString(v[1]) << endl;
		// cout << contToString(v[2]) << endl;
		// cout << contToString(v[3]) << endl;
		// cout << contToString(v[4]) << endl;
		// cout << contToString(v[5]) << endl;

		vc1.assign(v[1].begin(), v[1].end());
		myvc1.assign(v[1].begin(), v[1].end());
		g_vc2.assign(v[1].begin(), v[1].end());
		myvc2.assign(v[1].begin(), v[1].end());
		for (int i = 0; i < 6; i++) {
			vc1.assign(v[i].begin(), v[i].end());
			myvc1.assign(v[i].begin(), v[i].end());
		for (int j = 0; j < 6; j++) {
				g_vc2.assign(v[j].begin(), v[j].end());
				myvc2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(vc1 == g_vc2, myvc1 == myvc2);
			}
		}

		for (int i = 0; i < 6; i++) {
			vc1.assign(v[i].begin(), v[i].end());
			myvc1.assign(v[i].begin(), v[i].end());
			for (int j = 0; j < 6; j++) {
				g_vc2.assign(v[j].begin(), v[j].end());
				myvc2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(vc1 != g_vc2, myvc1 != myvc2);
			}
		}

		for (int i = 0; i < 6; i++) {
			vc1.assign(v[i].begin(), v[i].end());
			myvc1.assign(v[i].begin(), v[i].end());
			for (int j = 0; j < 6; j++) {
				g_vc2.assign(v[j].begin(), v[j].end());
				myvc2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(vc1 < g_vc2, myvc1 < myvc2);
			}
		}

		for (int i = 0; i < 6; i++) {
			vc1.assign(v[i].begin(), v[i].end());
			myvc1.assign(v[i].begin(), v[i].end());
			for (int j = 0; j < 6; j++) {
				g_vc2.assign(v[j].begin(), v[j].end());
				myvc2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(vc1 <= g_vc2, myvc1 <= myvc2);
			}
		}

		for (int i = 0; i < 6; i++) {
			vc1.assign(v[i].begin(), v[i].end());
			myvc1.assign(v[i].begin(), v[i].end());
			for (int j = 0; j < 6; j++) {
				g_vc2.assign(v[j].begin(), v[j].end());
				myvc2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(vc1 > g_vc2, myvc1 > myvc2);
			}
		}

			for (int i = 0; i < 6; i++) {
			vc1.assign(v[i].begin(), v[i].end());
			myvc1.assign(v[i].begin(), v[i].end());
			for (int j = 0; j < 6; j++) {
				g_vc2.assign(v[j].begin(), v[j].end());
				myvc2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(vc1 >= g_vc2, myvc1 >= myvc2);
			}
		}
		
	}
}