#include <list>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "tests.hpp"
#include "test_runner.h"
#include "list.hpp"

/*********************************************************************/
/*								TESTS								 */
/*********************************************************************/
namespace ft_list
{
	void constructorDefault_test() {

		ft::list<int> myls1;
		ASSERT_EQUAL(0u, myls1.size());

		ft::list<int> myls2(myls1);
		ASSERT_EQUAL(0u, myls2.size());

		ft::list<int> myls3 = myls1;
		ASSERT_EQUAL(0u, myls3.size());
	}

	void constructorFill_test() {
		
		std::list<int> ls1(10, 15);
		ft::list<int> myls1(10, 15);
		ASSERT_EQUAL(ls1.size(), myls1.size());
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));

		std::list<char> ls2(10, 'X');
		ft::list<char> myls2(10, 'X');
		ASSERT_EQUAL(ls2.size(), myls2.size());
		ASSERT_EQUAL(contToString(ls2), contToString(myls2));

		std::list<std::string> ls3(10, "Kto tut?");
		ft::list<std::string> myls3(10, "Kto tut?");
		ASSERT_EQUAL(ls3.size(), myls3.size());
		ASSERT_EQUAL(contToString(ls3), contToString(myls3));
	}

	void constructorRange_test() {

		ft::list<int> myls1(g_ls.begin(), g_ls.end());		// list from std::list
		ASSERT_EQUAL(g_ls.size(), myls1.size());
		ASSERT_EQUAL(contToString(g_ls), contToString(myls1));

		ft::list<int> myls2(g_vc.begin(), g_vc.end());		// list from std::vector
		ASSERT_EQUAL(g_vc.size(), myls2.size());
		ASSERT_EQUAL(contToString(g_vc), contToString(myls2));

		ft::list<int> myls3(g_dq.begin(), g_dq.end());		// list from std::deque
		ASSERT_EQUAL(g_dq.size(), myls3.size());
		ASSERT_EQUAL(contToString(g_dq), contToString(myls3));
	}

	void size_test() {

		ft::list<int> myls1;
		ASSERT_EQUAL(0u, myls1.size());

		ft::list<int> myls2(g_ls.begin(), g_ls.end());
		ASSERT_EQUAL(g_ls.size(), myls2.size());
	}

	void empty_test() {

		ft::list<int> myls1;
		ASSERT_EQUAL(true, myls1.empty());

		ft::list<int> myls2(g_ls.begin(), g_ls.end());
		ASSERT_EQUAL(false, myls2.empty());
	}

	void max_size_test() {
		
		ft::list<int> myls;
		ASSERT_EQUAL(g_ls.max_size(), myls.max_size());
	}

	void begin_test() {
		
		ft::list<int> myls(g_ls.begin(), g_ls.end());
		ft::list<int>::iterator myit = myls.begin();
		std::list<int>::iterator it = g_ls.begin();
		ASSERT_EQUAL(*myit, *it);

		*it = 100;
		*myit = 100;
		ASSERT_EQUAL(*it, *myit);

		const ft::list<int> myls2(g_ls.begin(), g_ls.end());
		ft::list<int>::const_iterator myit2 = myls.begin();
		ASSERT_EQUAL(*myit2, 100);
		*it = 0;
	}

	void rbegin_rend_test() {

		ft::list<int> myls(g_ls.begin(), g_ls.end());
		ASSERT_EQUAL(contToString(g_ls), contToString(myls));

		ft::list<int> myrls(g_ls.rbegin(), g_ls.rend());
		std::list<int> rls(g_ls.rbegin(), g_ls.rend());
		ASSERT_EQUAL(contToString(rls), contToString(myrls));
	}

	void front_back_test() {

		ft::list<int> myls(g_ls.begin(), g_ls.end());
		ASSERT_EQUAL(contToString(g_ls), contToString(myls));

		ASSERT_EQUAL(g_ls.front(), myls.front());
		ASSERT_EQUAL(g_ls.back(), myls.back());
	}

	void assign_range_test() {

		ft::list<int> myls;
		myls.assign(g_ls.begin(), g_ls.end());
		ASSERT_EQUAL(contToString(g_ls), contToString(myls));

		myls.assign(g_ls.rbegin(), g_ls.rend());
		std::list<int> rls;
		rls.assign(g_ls.rbegin(), g_ls.rend());
		ASSERT_EQUAL(contToString(rls), contToString(myls));

		myls.assign(g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(contToString(g_vc), contToString(myls));

		myls.assign(g_dq.begin(), g_dq.end());
		ASSERT_EQUAL(contToString(g_dq), contToString(myls));
	}

	void assign_fill_test() {

		std::list<int> als;
		als.assign(18, 100);
		ft::list<int> myls;
		myls.assign(18, 100);
		ASSERT_EQUAL(contToString(als), contToString(myls));

		std::list<double> als2;
		als2.assign(20, 100.);
		ft::list<double> myls2;
		myls2.assign(20, 100.);
		ASSERT_EQUAL(contToString(als2), contToString(myls2));

		std::list<std::string> als3;
		als3.assign(22, "Fart");
		ft::list<std::string> myls3;
		myls3.assign(22, "Fart");
		ASSERT_EQUAL(contToString(als3), contToString(myls3));
	}

	void sort_test() {

		std::vector<int> vect;
		for (int i = 0; i < 10; i++) { vect.push_back(rand() % 100); }

		std::list<int> sls(vect.begin(), vect.end());
		ft::list<int> myls(vect.begin(), vect.end());
		ASSERT_EQUAL(contToString(sls), contToString(myls));

		sls.sort();
		myls.sort();
		ASSERT_EQUAL(contToString(sls), contToString(myls));
	}

	bool mycomparison (int first, int second) { return (first % 2) < (second % 2); }

	void sort_compare_test() {

		std::list<int> els;
		ft::list<int> myels;
		els.sort(mycomparison);
		myels.sort(mycomparison);
		ASSERT_EQUAL(contToString(els), contToString(myels));

		std::vector<int> vect;
		for (int i = 0; i < 10; i++) { vect.push_back(rand() % 100); }

		std::list<int> sls(vect.begin(), vect.end());
		ft::list<int> myls(vect.begin(), vect.end());
		ASSERT_EQUAL(contToString(sls), contToString(myls));

		sls.sort(mycomparison);
		myls.sort(mycomparison);
		ASSERT_EQUAL(contToString(sls), contToString(myls));
	}

	void reverse_test() {
		{
			std::list<int> ls;
			ft::list<int> myls;

			ls.reverse();
			myls.reverse();
			ASSERT_EQUAL(contToString(ls), contToString(myls));
		}
		{
			std::list<int> ls(g_ls.begin(), g_ls.end());
			ft::list<int> myls(g_ls.begin(), g_ls.end());
			ASSERT_EQUAL(contToString(ls), contToString(myls));

			ls.reverse();
			myls.reverse();
			ASSERT_EQUAL(contToString(ls), contToString(myls));
		}
	}

	void merge_test() {
		std::vector<int> vect1;
		std::vector<int> vect2;
		for (int i = 0; i < 10; i++) { vect1.push_back(rand() % 100); }
		for (int i = 0; i < 10; i++) { vect2.push_back(rand() % 100); }

		std::list<int> ls1(vect1.begin(), vect1.end());
		std::list<int> ls2(vect2.begin(), vect2.end());
		ls1.sort();
		ls2.sort();

		ft::list<int> myls1(vect1.begin(), vect1.end());
		ft::list<int> myls2(vect2.begin(), vect2.end());
		myls1.sort();
		myls2.sort();

		ls1.merge(ls2);
		myls1.merge(myls2);
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(contToString(ls2), contToString(myls2));

	// merge compare
		ls2.assign(vect1.begin(), vect1.end());
		myls2.assign(vect1.begin(), vect1.end());
		ls2.sort();
		myls2.sort();

		ls1.merge(ls2, mycomparison);
		myls1.merge(myls2, mycomparison);
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(contToString(ls2), contToString(myls2));
	}

	void splice_test() {

	// splice (iterator position, list& x)
		std::list<int> ls1(g_ls.begin(), g_ls.end());
		std::list<int> ls2(g_ls.begin(), g_ls.end());

		ft::list<int> myls1(g_ls.begin(), g_ls.end());
		ft::list<int> myls2(g_ls.begin(), g_ls.end());

		ls1.splice(++(ls1.begin()), ls2);
		myls1.splice(++(myls1.begin()), myls2);

		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(contToString(ls2), contToString(myls2));

	// splice (iterator position, list& x, iterator i)
		ls2.assign(g_ls.begin(), g_ls.end());
		myls2.assign(g_ls.begin(), g_ls.end());

		ls1.splice(ls1.begin(), ls2, ++(ls2.begin()));
		myls1.splice(myls1.begin(), myls2, ++(myls2.begin()));

		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(contToString(ls2), contToString(myls2));

	// splice (iterator position, list& x, iterator first, iterator last)
		ls2.assign(g_ls.begin(), g_ls.end());
		myls2.assign(g_ls.begin(), g_ls.end());

		ls1.splice(ls1.begin(), ls2, ls2.begin(), ls2.end());
		myls1.splice(myls1.begin(), myls2, myls2.begin(), myls2.end());

		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(contToString(ls2), contToString(myls2));
	}

	void insert_test() {
		std::list<int> ls1(g_ls.begin(), g_ls.end());
		ft::list<int> myls1(g_ls.begin(), g_ls.end());

	// insert (iterator position, const T& data)
		std::list<int>::iterator it = ls1.insert(++(ls1.begin()), 100);
		ft::list<int>::iterator  myit = myls1.insert(++(myls1.begin()), 100);
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(*it, *myit);

	// insert (iterator position, size_t n, const T& val)
		ls1.insert(++(ls1.begin()), 10, 150);
		myls1.insert(++(myls1.begin()), 10, 150);
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));

	// insert (iterator position, InputIterator first, InputIterator last)
		ls1.insert(ls1.begin(), g_ls.begin(), g_ls.end());
		myls1.insert(myls1.begin(), g_ls.begin(), g_ls.end());
	}

	void push_back_front_test() {
		std::list<int> ls1;
		ft::list<int> myls1;

		ls1.push_back(12);
		myls1.push_back(12);
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));

		ls1.push_back(17);
		myls1.push_back(17);
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));

		ls1.push_front(11);
		myls1.push_front(11);
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
	}

	void pop_back_front_test() {
		std::list<int> ls1;
		ft::list<int> myls1;

	// test with empty list
		// ls1.pop_front();
		// myls1.pop_front();
		// ASSERT_EQUAL(ls1.size(), myls1.size());

		// ls1.pop_back();
		// myls1.pop_back();
		// ASSERT_EQUAL(ls1.size(), myls1.size());

	// test with not empty list
		ls1.assign(g_ls.begin(), g_ls.end());
		myls1.assign(g_ls.begin(), g_ls.end());

		ls1.pop_back();
		myls1.pop_back();
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(ls1.size(), myls1.size());

		ls1.pop_front();
		myls1.pop_front();
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(ls1.size(), myls1.size());
	}

	void resize_test() {
		std::list<int> ls1;
		ft::list<int> myls1;

		ls1.resize(12, 1);
		myls1.resize(12, 1);
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(ls1.size(), myls1.size());

		ls1.resize(17, 2);
		myls1.resize(17, 2);
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(ls1.size(), myls1.size());

		ls1.resize(8, 3);
		myls1.resize(8, 3);
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(ls1.size(), myls1.size());
	}

	void clear_test() {
		std::list<int> ls1(g_ls.begin(), g_ls.end());
		ft::list<int> myls1(g_ls.begin(), g_ls.end());

		ls1.clear();
		myls1.clear();
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(ls1.size(), myls1.size());

		ls1.clear();
		myls1.clear();
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(ls1.size(), myls1.size());
	}

	void erase_test() {
		std::list<int> ls1(g_ls.begin(), g_ls.end());
		ft::list<int> myls1(g_ls.begin(), g_ls.end());

		ls1.erase(++(ls1.begin()));
		myls1.erase(++(myls1.begin()));
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));

		ls1.erase(--(ls1.end()));
		myls1.erase(--(myls1.end()));
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));

		ls1.erase(++(ls1.begin()), ls1.end());
		myls1.erase(++(myls1.begin()), myls1.end());
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(ls1.size(), myls1.size());
	}

	void remove_test() {
		std::list<int> ls1(g_ls.begin(), g_ls.end());
		ft::list<int> myls1(g_ls.begin(), g_ls.end());

		ls1.remove(5);
		myls1.remove(5);
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(ls1.size(), myls1.size());

		ls1.remove(105);
		myls1.remove(105);
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(ls1.size(), myls1.size());
	}

	bool single_digit (const int& value) { return (value<5); }

	struct is_odd {
	bool operator() (const int& value) { return (value%2)==1; }
	};

	void remove_if_test() {
		std::list<int> ls1(g_ls.begin(), g_ls.end());
		ft::list<int> myls1(g_ls.begin(), g_ls.end());

		ls1.remove_if(single_digit);
		myls1.remove_if(single_digit);
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));

		ls1.remove_if(is_odd());
		myls1.remove_if(is_odd());
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
	}

	void swap_test() {
		std::list<int> ls1(g_ls.begin(), g_ls.end());
		std::list<int> ls2(g_vc.begin(), g_vc.end());
		ft::list<int> myls1(g_ls.begin(), g_ls.end());
		ft::list<int> myls2(g_vc.begin(), g_vc.end());

		ls1.swap(ls2);
		myls1.swap(myls2);
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(contToString(ls2), contToString(myls2));
	}

	void unique_test() {
		std::vector<int> vec;
		for (int i = 0; i < 20; i++) vec.push_back(rand() % 10);

		std::list<int> ls1(vec.begin(), vec.end());
		ft::list<int> myls1(vec.begin(), vec.end());

		ls1.unique();
		myls1.unique();
		ASSERT_EQUAL(contToString(ls1), contToString(myls1));
		ASSERT_EQUAL(ls1.size(), myls1.size());
	}

	void operators_test() {
		std::list<int> ls1, ls2;
		ft::list<int> myls1, myls2;

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
			ls1.assign(v[i].begin(), v[i].end());
			myls1.assign(v[i].begin(), v[i].end());
		for (int j = 0; j < 6; j++) {
				ls2.assign(v[j].begin(), v[j].end());
				myls2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(ls1 == ls2, myls1 == myls2);
			}
		}

		for (int i = 0; i < 6; i++) {
			ls1.assign(v[i].begin(), v[i].end());
			myls1.assign(v[i].begin(), v[i].end());
			for (int j = 0; j < 6; j++) {
				ls2.assign(v[j].begin(), v[j].end());
				myls2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(ls1 != ls2, myls1 != myls2);
			}
		}

		for (int i = 0; i < 6; i++) {
			ls1.assign(v[i].begin(), v[i].end());
			myls1.assign(v[i].begin(), v[i].end());
			for (int j = 0; j < 6; j++) {
				ls2.assign(v[j].begin(), v[j].end());
				myls2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(ls1 < ls2, myls1 < myls2);
			}
		}

		for (int i = 0; i < 6; i++) {
			ls1.assign(v[i].begin(), v[i].end());
			myls1.assign(v[i].begin(), v[i].end());
			for (int j = 0; j < 6; j++) {
				ls2.assign(v[j].begin(), v[j].end());
				myls2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(ls1 <= ls2, myls1 <= myls2);
			}
		}

		for (int i = 0; i < 6; i++) {
			ls1.assign(v[i].begin(), v[i].end());
			myls1.assign(v[i].begin(), v[i].end());
			for (int j = 0; j < 6; j++) {
				ls2.assign(v[j].begin(), v[j].end());
				myls2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(ls1 > ls2, myls1 > myls2);
			}
		}

			for (int i = 0; i < 6; i++) {
			ls1.assign(v[i].begin(), v[i].end());
			myls1.assign(v[i].begin(), v[i].end());
			for (int j = 0; j < 6; j++) {
				ls2.assign(v[j].begin(), v[j].end());
				myls2.assign(v[j].begin(), v[j].end());
				ASSERT_EQUAL(ls1 >= ls2, myls1 >= myls2);
			}
		}
		
	}
}