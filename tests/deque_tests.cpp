#include <deque>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "tests.hpp"
#include "test_runner.h"
#include "deque.hpp"

/*********************************************************************/
/*								TESTS								 */
/*********************************************************************/
namespace ft_deque
{
	void constructorDefault_test() {

		ft::deque<int> mydq1;
		ASSERT_EQUAL(0u, mydq1.size());

		ft::deque<int> mydq2(mydq1);
		ASSERT_EQUAL(0u, mydq2.size());

		ft::deque<int> mydq3 = mydq1;
		ASSERT_EQUAL(0u, mydq3.size());
	}

	void constructorFill_test() {
		
		std::deque<int> dq1(10, 15);
		ft::deque<int> mydq1(10, 15);
		ASSERT_EQUAL(dq1.size(), mydq1.size());
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));

		std::deque<char> dq2(10, 'X');
		ft::deque<char> mydq2(10, 'X');
		ASSERT_EQUAL(dq2.size(), mydq2.size());
		ASSERT_EQUAL(contToString(dq2), contToString(mydq2));

		std::deque<std::string> dq3(10, "Kto tut?");
		ft::deque<std::string> mydq3(10, "Kto tut?");
		ASSERT_EQUAL(dq3.size(), mydq3.size());
		ASSERT_EQUAL(contToString(dq3), contToString(mydq3));
	}

	void constructorRange_test() {

		ft::deque<int> mydq1(g_dq.begin(), g_dq.end());		// deque from std::deque
		ASSERT_EQUAL(g_dq.size(), mydq1.size());
		ASSERT_EQUAL(contToString(g_dq), contToString(mydq1));

		ft::deque<int> mydq2(g_vc.begin(), g_vc.end());		// deque from std::vector
		ASSERT_EQUAL(g_vc.size(), mydq2.size());
		ASSERT_EQUAL(contToString(g_vc), contToString(mydq2));

		ft::deque<int> mydq3(g_dq.begin(), g_dq.end());		// deque from std::deque
		ASSERT_EQUAL(g_dq.size(), mydq3.size());
		ASSERT_EQUAL(contToString(g_dq), contToString(mydq3));
	}

	void size_test() {

		ft::deque<int> mydq1;
		ASSERT_EQUAL(0u, mydq1.size());

		ft::deque<int> mydq2(g_dq.begin(), g_dq.end());
		ASSERT_EQUAL(g_dq.size(), mydq2.size());
	}

	void empty_test() {

		ft::deque<int> mydq1;
		ASSERT_EQUAL(true, mydq1.empty());

		ft::deque<int> mydq2(g_dq.begin(), g_dq.end());
		ASSERT_EQUAL(false, mydq2.empty());
	}

	void max_size_test() {
		
		ft::deque<int> mydq;
		ASSERT_EQUAL(g_dq.max_size(), mydq.max_size());
	}

	void begin_test() {
		
		ft::deque<int> mydq(g_dq.begin(), g_dq.end());
		ft::deque<int>::iterator myit = mydq.begin();
		std::deque<int>::iterator it = g_dq.begin();
		ASSERT_EQUAL(*myit, *it);

		*it = 100;
		*myit = 100;
		ASSERT_EQUAL(*it, *myit);

		const ft::deque<int> mydq2(g_dq.begin(), g_dq.end());
		ft::deque<int>::const_iterator myit2 = mydq.begin();
		ASSERT_EQUAL(*myit2, 100);
		*it = 0;
	}

	void rbegin_rend_test() {

		ft::deque<int> mydq(g_dq.begin(), g_dq.end());
		ASSERT_EQUAL(contToString(g_dq), contToString(mydq));

		ft::deque<int> myrdq(g_dq.rbegin(), g_dq.rend());
		std::deque<int> rdq(g_dq.rbegin(), g_dq.rend());
		ASSERT_EQUAL(contToString(rdq), contToString(myrdq));
	}

	void front_back_test() {

		ft::deque<int> mydq(g_dq.begin(), g_dq.end());
		ASSERT_EQUAL(contToString(g_dq), contToString(mydq));

		ASSERT_EQUAL(g_dq.front(), mydq.front());
		ASSERT_EQUAL(g_dq.back(), mydq.back());
	}

	void assign_range_test() {

		ft::deque<int> mydq;
		mydq.assign(g_dq.begin(), g_dq.end());
		ASSERT_EQUAL(contToString(g_dq), contToString(mydq));

		mydq.assign(g_dq.rbegin(), g_dq.rend());
		std::deque<int> rdq;
		rdq.assign(g_dq.rbegin(), g_dq.rend());
		ASSERT_EQUAL(contToString(rdq), contToString(mydq));

		mydq.assign(g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(contToString(g_vc), contToString(mydq));

		mydq.assign(g_dq.begin(), g_dq.end());
		ASSERT_EQUAL(contToString(g_dq), contToString(mydq));
	}

	void assign_fill_test() {

		std::deque<int> adq;
		adq.assign(18, 100);
		ft::deque<int> mydq;
		mydq.assign(18, 100);
		ASSERT_EQUAL(contToString(adq), contToString(mydq));

		std::deque<double> adq2;
		adq2.assign(20, 100.);
		ft::deque<double> mydq2;
		mydq2.assign(20, 100.);
		ASSERT_EQUAL(contToString(adq2), contToString(mydq2));

		std::deque<std::string> adq3;
		adq3.assign(22, "Fart");
		ft::deque<std::string> mydq3;
		mydq3.assign(22, "Fart");
		ASSERT_EQUAL(contToString(adq3), contToString(mydq3));
	}

	void insert_test() {
		std::deque<int> dq1(g_dq.begin(), g_dq.end());
		ft::deque<int> mydq1(g_dq.begin(), g_dq.end());

	// insert (iterator position, const T& data)
		std::deque<int>::iterator it = dq1.insert(++(dq1.begin()), 100);
		ft::deque<int>::iterator  myit = mydq1.insert(++(mydq1.begin()), 100);
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));
		ASSERT_EQUAL(*it, *myit);

	// insert (iterator position, size_t n, const T& val)
		dq1.insert(++(dq1.begin()), 10, 150);
		mydq1.insert(++(mydq1.begin()), 10, 150);
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));

	// insert (iterator position, InputIterator first, InputIterator last)
		dq1.insert(dq1.begin(), g_dq.begin(), g_dq.end());
		mydq1.insert(mydq1.begin(), g_dq.begin(), g_dq.end());
	}

	void push_back_front_test() {
		std::deque<int> dq1;
		ft::deque<int> mydq1;

		dq1.push_back(12);
		mydq1.push_back(12);
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));

		dq1.push_back(17);
		mydq1.push_back(17);
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));

		dq1.push_front(11);
		mydq1.push_front(11);
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));
	}

	void pop_back_front_test() {
		std::deque<int> dq1;
		ft::deque<int> mydq1;

	// test with empty deque
		// dq1.pop_front();
		// mydq1.pop_front();
		// ASSERT_EQUAL(dq1.size(), mydq1.size());

		// dq1.pop_back();
		// mydq1.pop_back();
		// ASSERT_EQUAL(dq1.size(), mydq1.size());

	// test with not empty deque
		dq1.assign(g_dq.begin(), g_dq.end());
		mydq1.assign(g_dq.begin(), g_dq.end());

		dq1.pop_back();
		mydq1.pop_back();
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));
		ASSERT_EQUAL(dq1.size(), mydq1.size());

		dq1.pop_front();
		mydq1.pop_front();
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));
		ASSERT_EQUAL(dq1.size(), mydq1.size());
	}

	void resize_test() {
		std::deque<int> dq1;
		ft::deque<int> mydq1;

		dq1.resize(12, 1);
		mydq1.resize(12, 1);
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));
		ASSERT_EQUAL(dq1.size(), mydq1.size());

		dq1.resize(17, 2);
		mydq1.resize(17, 2);
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));
		ASSERT_EQUAL(dq1.size(), mydq1.size());

		dq1.resize(8, 3);
		mydq1.resize(8, 3);
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));
		ASSERT_EQUAL(dq1.size(), mydq1.size());
	}

	void clear_test() {
		std::deque<int> dq1(g_dq.begin(), g_dq.end());
		ft::deque<int> mydq1(g_dq.begin(), g_dq.end());

		dq1.clear();
		mydq1.clear();
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));
		ASSERT_EQUAL(dq1.size(), mydq1.size());

		dq1.clear();
		mydq1.clear();
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));
		ASSERT_EQUAL(dq1.size(), mydq1.size());
	}

	void erase_test() {
		std::deque<int> dq1(g_dq.begin(), g_dq.end());
		ft::deque<int> mydq1(g_dq.begin(), g_dq.end());

		dq1.erase(++(dq1.begin()));
		mydq1.erase(++(mydq1.begin()));
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));

		dq1.erase(--(dq1.end()));
		mydq1.erase(--(mydq1.end()));
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));

		dq1.erase(++(dq1.begin()), dq1.end());
		mydq1.erase(++(mydq1.begin()), mydq1.end());
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));
		ASSERT_EQUAL(dq1.size(), mydq1.size());
	}

	void swap_test() {
		std::deque<int> dq1(g_dq.begin(), g_dq.end());
		std::deque<int> dq2(g_vc.begin(), g_vc.end());
		ft::deque<int> mydq1(g_dq.begin(), g_dq.end());
		ft::deque<int> mydq2(g_vc.begin(), g_vc.end());

		dq1.swap(dq2);
		mydq1.swap(mydq2);
		ASSERT_EQUAL(contToString(dq1), contToString(mydq1));
		ASSERT_EQUAL(contToString(dq2), contToString(mydq2));
	}

	void oper_sq_braces_test() {
		std::deque<int> dq(g_dq.begin(), g_dq.end());
		ft::deque<int> mydq(g_dq.begin(), g_dq.end());

		ASSERT_EQUAL(dq[0], mydq[0]);
		ASSERT_EQUAL(dq[1], mydq[1]);
		ASSERT_EQUAL(dq[8], mydq[8]);
		ASSERT_EQUAL(dq[14], mydq[14]);
		// ASSERT_EQUAL(contToString(dq[16], contToString(mydq[16]));	// out of range
	}

	void at_test() {
		std::deque<int> dq(g_dq.begin(), g_dq.end());
		ft::deque<int> mydq(g_dq.begin(), g_dq.end());

		ASSERT_EQUAL(dq.at(0), mydq.at(0));
		ASSERT_EQUAL(dq.at(1), mydq.at(1));
		ASSERT_EQUAL(dq.at(8), mydq.at(8));
		ASSERT_EQUAL(dq.at(14), mydq.at(14));

		try { dq.at(20); }
		catch (std::out_of_range& ex) { std::cout << ex.what() << std::endl; }
		
		try { mydq.at(20); }
		catch (std::out_of_range& ex) { std::cout << ex.what() << std::endl; }
	}

	void operators_test() {
		std::deque<int> dq1, dq2;
		ft::deque<int> mydq1, mydq2;

		int arr_str[][7] = {{1,2,3,4,-1}, {1,2,3,4,4,-1},
						{1,2,3,1,4,1,-1}, {1,2,3,4,5,-1},
						{0,2,3,4,5,6,-1}, {0,-1}};
		std::vector<int> v[6];
		for (int i = 0; i < 6; i++) {
			for (int j = 0; arr_str[i][j] != -1; j++) {
				v[i].push_back(arr_str[i][j]);
			}
		}

		for (int i = 0; i < 6; i++) {
			dq1.assign(v[i].begin(), v[i].end());
			mydq1.assign(v[i].begin(), v[i].end());
		for (int j = 0; j < 6; j++) {
				dq2.assign(v[j].begin(), v[j].end());
				mydq2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(dq1 == dq2, mydq1 == mydq2);
			}
		}

		for (int i = 0; i < 6; i++) {
			dq1.assign(v[i].begin(), v[i].end());
			mydq1.assign(v[i].begin(), v[i].end());
			for (int j = 0; j < 6; j++) {
				dq2.assign(v[j].begin(), v[j].end());
				mydq2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(dq1 != dq2, mydq1 != mydq2);
			}
		}

		for (int i = 0; i < 6; i++) {
			dq1.assign(v[i].begin(), v[i].end());
			mydq1.assign(v[i].begin(), v[i].end());
			for (int j = 0; j < 6; j++) {
				dq2.assign(v[j].begin(), v[j].end());
				mydq2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(dq1 < dq2, mydq1 < mydq2);
			}
		}

		for (int i = 0; i < 6; i++) {
			dq1.assign(v[i].begin(), v[i].end());
			mydq1.assign(v[i].begin(), v[i].end());
			for (int j = 0; j < 6; j++) {
				dq2.assign(v[j].begin(), v[j].end());
				mydq2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(dq1 <= dq2, mydq1 <= mydq2);
			}
		}

		for (int i = 0; i < 6; i++) {
			dq1.assign(v[i].begin(), v[i].end());
			mydq1.assign(v[i].begin(), v[i].end());
			for (int j = 0; j < 6; j++) {
				dq2.assign(v[j].begin(), v[j].end());
				mydq2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(dq1 > dq2, mydq1 > mydq2);
			}
		}

			for (int i = 0; i < 6; i++) {
			dq1.assign(v[i].begin(), v[i].end());
			mydq1.assign(v[i].begin(), v[i].end());
			for (int j = 0; j < 6; j++) {
				dq2.assign(v[j].begin(), v[j].end());
				mydq2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(dq1 >= dq2, mydq1 >= mydq2);
			}
		}
		
	}
}