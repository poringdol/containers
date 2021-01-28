#include <iostream>
#include <sstream>
#include <cstdlib>
#include <set>
#include "tests.hpp"
#include "test_runner.h"
#include "set.hpp"

/*********************************************************************/
/*								TESTS								 */
/*********************************************************************/
namespace ft_set
{
	void constructorDefault_test() {

		ft::set<int> my_st1;
		ASSERT_EQUAL(0u, my_st1.size());

		ft::set<ft::stack<double> > my_st2;
		ASSERT_EQUAL(0u, my_st2.size());

		// ft::set<int> my_st3 = my_st1;
		// ASSERT_EQUAL(0u, my_st3.size());
	}

	void constructorRange_test() {
		{
			std::set<int> st(g_ls.begin(), g_ls.end());		// set from std::list
			ft::set<int> my_st(g_ls.begin(), g_ls.end());
			ASSERT_EQUAL(st.size(), my_st.size());
			ASSERT_EQUAL(contToString(st), contToString(my_st));
			
		}
		{
			std::set<int> st(g_vc.begin(), g_vc.end());	// set from std::vector
			ft::set<int> my_st(g_vc.begin(), g_vc.end());
			ASSERT_EQUAL(st.size(), my_st.size());
			ASSERT_EQUAL(contToString(st), contToString(my_st));
			
		}
		{
			std::set<std::string> st(g_str.begin(), g_str.end());	// set from std::vector
			ft::set<std::string> my_st(g_str.begin(), g_str.end());
			ASSERT_EQUAL(st.size(), my_st.size());
			contToString(st);
			contToString(my_st);
			ASSERT_EQUAL(contToString(st), contToString(my_st));
			
		}
		{
			std::vector<int> v;
			for (int i = 0; i < 20; i++) v.push_back(rand() % 50);

			std::set<int> st(v.begin(), v.end());	// set from std::vector - unsorted
			ft::set<int> my_st(v.begin(), v.end());
			ASSERT_EQUAL(st.size(), my_st.size());
			ASSERT_EQUAL(contToString(st), contToString(my_st));
			
		}
	}

	void constructorCopy_test() {
		{
			ft::set<int> my_st1;
			ASSERT_EQUAL(0u, my_st1.size());

			ft::set<int> my_st2(my_st1);
			ASSERT_EQUAL(0u, my_st2.size());
		}
		{
			std::set<int> st(g_vc.begin(), g_vc.end());
			ft::set<int> my_st(g_vc.begin(), g_vc.end());

			std::set<int> st2(st);
			ft::set<int> my_st2(my_st);

			ASSERT_EQUAL(st2.size(), my_st2.size());
			ASSERT_EQUAL(contToString(st2), contToString(my_st2));

			ASSERT_EQUAL(my_st.size(), my_st2.size());
			ASSERT_EQUAL(contToString(my_st), contToString(my_st2));
		}
		{
			std::set<int> st(g_vc.begin(), g_vc.end());
			ft::set<int> my_st(g_vc.begin(), g_vc.end());

			std::set<int> st2 = st;
			ft::set<int> my_st2 = my_st;

			ASSERT_EQUAL(st2.size(), my_st2.size());
			ASSERT_EQUAL(contToString(st2), contToString(my_st2));

			ASSERT_EQUAL(my_st.size(), my_st2.size());
			ASSERT_EQUAL(contToString(my_st), contToString(my_st2));
		}
		{
			std::set<int> st(g_vc.begin(), g_vc.end());
			ft::set<int> my_st(g_vc.begin(), g_vc.end());

			std::set<int> st2; 
			st2 = st;
			ft::set<int> my_st2;
			my_st2 = my_st;

			ASSERT_EQUAL(st2.size(), my_st2.size());
			ASSERT_EQUAL(contToString(st2), contToString(my_st2));

			ASSERT_EQUAL(my_st.size(), my_st2.size());
			ASSERT_EQUAL(contToString(my_st), contToString(my_st2));
		}
	}

	void begin_end_test() {

		std::set<int> st(g_vc.begin(), g_vc.end());
		std::set<int>::iterator it;
		std::set<int>::reverse_iterator r_it;

		ft::set<int> my_st(g_vc.begin(), g_vc.end());
		ft::set<int>::iterator my_it;
		ft::set<int>::reverse_iterator my_r_it;

		it = st.begin();
		my_it = my_st.begin();
		ASSERT_EQUAL(*it, *my_it);

		it = ++st.begin();
		my_it = ++my_st.begin();
		ASSERT_EQUAL(*it, *my_it);

		it = st.begin()++;
		my_it = my_st.begin()++;
		ASSERT_EQUAL(*it, *my_it);

		it = --st.end();
		my_it = --my_st.end();
		ASSERT_EQUAL(*it, *my_it);

		// reverse iterator
		r_it = st.rbegin();
		my_r_it = my_st.rbegin();
		ASSERT_EQUAL(*r_it, *my_r_it);

		r_it = ++st.rbegin();
		my_r_it = ++my_st.rbegin();
		ASSERT_EQUAL(*r_it, *my_r_it);

		r_it = st.rbegin()++;
		my_r_it = my_st.rbegin()++;
		ASSERT_EQUAL(*r_it, *my_r_it);

		r_it = --st.rend();
		my_r_it = --my_st.rend();
		ASSERT_EQUAL(*r_it, *my_r_it);
	}


	void size_test() {

		ft::set<int> my_st1;
		ASSERT_EQUAL(0u, my_st1.size());

		std::set<int> st2(g_vc.begin(), g_vc.end());
		ft::set<int> my_st2(g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(st2.size(), my_st2.size());
	}

	void max_size_test() {
		
		std::set<int> st;
		ft::set<int> my_st;
		ASSERT_EQUAL(st.max_size(), my_st.max_size());
	}

	void empty_test() {

		ft::set<int> my_st1;
		ASSERT_EQUAL(true, my_st1.empty());

		ft::set<int> my_st2(g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(false, my_st2.empty());
	}

	void find_test() {
		std::set<int> st(g_vc.begin(), g_vc.end());
		ft::set<int> my_st(g_vc.begin(), g_vc.end());

		std::set<int>::iterator it;
		ft::set<int>::iterator my_it;

		it = st.find(19);
		my_it = my_st.find(19);
		ASSERT_EQUAL(it == st.end(), my_it == my_st.end());			// value not found

		it = st.find(8);
		my_it = my_st.find(8);
		ASSERT_EQUAL(*it, *my_it);
		ASSERT_EQUAL(*it, *my_it);
	}

	void count_test() {
	
		std::set<int> st(g_vc.begin(), g_vc.end());
		ft::set<int> my_st(g_vc.begin(), g_vc.end());

		ASSERT_EQUAL(st.count(16),   my_st.count(16));			// value not found
		ASSERT_EQUAL(st.count(-1),   my_st.count(-1));
		ASSERT_EQUAL(st.count(0),    my_st.count(0));
		ASSERT_EQUAL(st.count(1000), my_st.count(1000));

		ASSERT_EQUAL(st.count(25),  my_st.count(25));
		ASSERT_EQUAL(st.count(1),   my_st.count(1));
		ASSERT_EQUAL(st.count(100), my_st.count(100));
		ASSERT_EQUAL(st.count(60),  my_st.count(60));
		ASSERT_EQUAL(st.count(80),  my_st.count(80));
	}

	void insert_range_test() {

		std::set<int> st1;
		ft::set<int> my_st1;

		st1.insert(g_vc.begin(), g_vc.end());
		my_st1.insert(g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(contToString(st1), contToString(my_st1));

		st1.insert(g_vc2.begin(), g_vc2.end());
		my_st1.insert(g_vc2.begin(), g_vc2.end());
		ASSERT_EQUAL(contToString(st1), contToString(my_st1));

		std::set<std::string> st2;
		ft::set<std::string> my_st2;
		st2.insert(g_str.begin(), g_str.end());
		my_st2.insert(g_str.begin(), g_str.end());
		ASSERT_EQUAL(contToString(st1), contToString(my_st1));

		st2.insert(g_str.rbegin(), g_str.rend());
		my_st2.insert(g_str.rbegin(), g_str.rend());
		ASSERT_EQUAL(contToString(st2), contToString(my_st2));
	}

	void insert_single_test() {
		{
			std::set<int> st;
			ft::set<int> my_st;

			std::pair<std::set<int>::iterator, bool> pr;
			std::pair<ft::set<int>::iterator, bool> my_pr;

			pr = st.insert(5);
			my_pr = my_st.insert(5);
			
			ASSERT_EQUAL(*(pr.first), *(my_pr.first));
			ASSERT_EQUAL(pr.second, my_pr.second);
			ASSERT_EQUAL(st.size(), my_st.size());

			pr = st.insert(5);
			my_pr = my_st.insert(5);
			ASSERT_EQUAL(*(pr.first), *(my_pr.first));
			ASSERT_EQUAL(pr.second, my_pr.second);
			ASSERT_EQUAL(st.size(), my_st.size());

			pr = st.insert(15);
			my_pr = my_st.insert(15);
			ASSERT_EQUAL(*(pr.first), *(my_pr.first));
			ASSERT_EQUAL(pr.second, my_pr.second);
			ASSERT_EQUAL(st.size(), my_st.size())

			pr = st.insert(15);
			my_pr = my_st.insert(15);
			ASSERT_EQUAL(*(pr.first), *(my_pr.first));
			ASSERT_EQUAL(pr.second, my_pr.second);
			ASSERT_EQUAL(st.size(), my_st.size())
		}
		{
			std::set<int> st(g_vc.begin(), g_vc.end());
			ft::set<int> my_st(g_vc.begin(), g_vc.end());

			std::pair<std::set<int>::iterator, bool> pr;
			std::pair<ft::set<int>::iterator, bool> my_pr;

			pr = st.insert(5);
			my_pr = my_st.insert(5);
			
			ASSERT_EQUAL(*(pr.first), *(my_pr.first));
			ASSERT_EQUAL(pr.second, my_pr.second);
			ASSERT_EQUAL(st.size(), my_st.size());

			pr = st.insert(5);
			my_pr = my_st.insert(5);
			ASSERT_EQUAL(*(pr.first), *(my_pr.first));
			ASSERT_EQUAL(pr.second, my_pr.second);
			ASSERT_EQUAL(st.size(), my_st.size());

			pr = st.insert(15);
			my_pr = my_st.insert(15);
			ASSERT_EQUAL(*(pr.first), *(my_pr.first));
			ASSERT_EQUAL(pr.second, my_pr.second);
			ASSERT_EQUAL(st.size(), my_st.size())

			pr = st.insert(15);
			my_pr = my_st.insert(15);
			ASSERT_EQUAL(*(pr.first), *(my_pr.first));
			ASSERT_EQUAL(pr.second, my_pr.second);
			ASSERT_EQUAL(st.size(), my_st.size())
		}
	}

	void insert_hint_test() {
		{
			std::set<int> st(g_vc.begin(), g_vc.end());
			ft::set<int> my_st(g_vc.begin(), g_vc.end());

			std::set<int>::iterator it;
			ft::set<int>::iterator my_it;

			it = st.find(55);
			my_it = my_st.find(55);
			it = st.insert(it, 12);
			my_it = my_st.insert(my_it, 12);
			if (it != st.end() && my_it != my_st.end())
				ASSERT_EQUAL(*it, *my_it);
			ASSERT_EQUAL(st.size(), my_st.size());


			it = st.find(0);
			my_it = my_st.find(0);
			it = st.insert(it, 3);
			my_it = my_st.insert(my_it, 3);
			if (it != st.end() && my_it != my_st.end())
				ASSERT_EQUAL(*it, *my_it);
			ASSERT_EQUAL(st.size(), my_st.size());

			it = st.find(-1);
			my_it = my_st.find(-1);
			it = st.insert(it, 3);
			my_it = my_st.insert(my_it, 3);
			if (it != st.end() && my_it != my_st.end())
				ASSERT_EQUAL(*it, *my_it);
			ASSERT_EQUAL(st.size(), my_st.size());

			it = st.find(0);
			my_it = my_st.find(0);
			it = st.insert(it, -1);
			my_it = my_st.insert(my_it, -1);
			if (it != st.end() && my_it != my_st.end())
				ASSERT_EQUAL(*it, *my_it);
			ASSERT_EQUAL(st.size(), my_st.size());

			it = st.find(9);
			my_it = my_st.find(9);
			it = st.insert(it, -10);
			my_it = my_st.insert(my_it, -10);
			if (it != st.end() && my_it != my_st.end())
				ASSERT_EQUAL(*it, *my_it);
			ASSERT_EQUAL(st.size(), my_st.size());

			it = st.find(9);
			my_it = my_st.find(9);
			it = st.insert(it, 20);
			my_it = my_st.insert(my_it, 20);
			if (it != st.end() && my_it != my_st.end())
				ASSERT_EQUAL(*it, *my_it);
			ASSERT_EQUAL(st.size(), my_st.size());
		}
	}

	void erase_single_test() {
		{
			std::set<int> st(g_vc.begin(), g_vc.end());
			ft::set<int> my_st(g_vc.begin(), g_vc.end());
			
			st.erase(st.begin());
			my_st.erase(my_st.begin());
			ASSERT_EQUAL(st.size(), my_st.size());
			ASSERT_EQUAL(contToString(st), contToString(my_st));

			st.erase(++st.begin());
			my_st.erase(++my_st.begin());
			ASSERT_EQUAL(st.size(), my_st.size());
			ASSERT_EQUAL(contToString(st), contToString(my_st));

			st.erase(--st.end());
			my_st.erase(--my_st.end());
			ASSERT_EQUAL(st.size(), my_st.size());
			ASSERT_EQUAL(contToString(st), contToString(my_st));

			st.erase(st.begin());
			my_st.erase(my_st.begin());
			ASSERT_EQUAL(st.size(), my_st.size());
			ASSERT_EQUAL(contToString(st), contToString(my_st));
	
			st.erase(st.find(5));
			my_st.erase(my_st.find(5));
			ASSERT_EQUAL(st.size(), my_st.size());
			ASSERT_EQUAL(contToString(st), contToString(my_st));

			st.erase(st.find(7));
			my_st.erase(my_st.find(7));
			ASSERT_EQUAL(st.size(), my_st.size());
			contToString(st);
			contToString(my_st);
			ASSERT_EQUAL(contToString(st), contToString(my_st));
			

			st.erase(st.begin());
			my_st.erase(my_st.begin());
			ASSERT_EQUAL(st.size(), my_st.size());
			ASSERT_EQUAL(contToString(st), contToString(my_st));
			

			st.erase(st.begin());
			my_st.erase(my_st.begin());
			ASSERT_EQUAL(st.size(), my_st.size());
			ASSERT_EQUAL(contToString(st), contToString(my_st));
			
			
			st.erase(st.begin());
			my_st.erase(my_st.begin());
			ASSERT_EQUAL(st.size(), my_st.size());
			ASSERT_EQUAL(contToString(st), contToString(my_st));
			
			
			st.erase(--st.end());
			my_st.erase(--my_st.end());
			ASSERT_EQUAL(st.size(), my_st.size());
			ASSERT_EQUAL(contToString(st), contToString(my_st));			
		}
		{
			std::set<std::string> st(g_str.begin(), g_str.end());
			ft::set<std::string> my_st(g_str.begin(), g_str.end());

			ASSERT_EQUAL(contToString(st), contToString(my_st));
			st.erase(st.begin());
			my_st.erase(my_st.begin());
			ASSERT_EQUAL(contToString(st), contToString(my_st));

			
			st.erase(++st.begin());
			my_st.erase(++my_st.begin());
			ASSERT_EQUAL(contToString(st), contToString(my_st));
			
			
			st.erase(++st.begin());
			my_st.erase(++my_st.begin());
			ASSERT_EQUAL(contToString(st), contToString(my_st));

			
			st.erase(st.begin());
			my_st.erase(my_st.begin());
			ASSERT_EQUAL(contToString(st), contToString(my_st));

			st.erase(--st.end());
			my_st.erase(--my_st.end());
			ASSERT_EQUAL(contToString(st), contToString(my_st));

			st.erase(--st.end());
			my_st.erase(--my_st.end());
			ASSERT_EQUAL(contToString(st), contToString(my_st));

			std::pair<std::set<std::string>::iterator, bool> pr = st.insert("odin");
			std::pair<ft::set<std::string>::iterator, bool> my_pr = my_st.insert("odin");

			std::set<std::string>::iterator it = pr.first;
			ft::set<std::string>::iterator my_it = my_pr.first;

			st.erase(it);
			my_st.erase(my_it);
			ASSERT_EQUAL(st.size(), my_st.size());
			ASSERT_EQUAL(contToString(st), contToString(my_st));
			

			it = st.find("seven_1");
			my_it = my_st.find("seven_1");
			st.erase(it);
			my_st.erase(my_it);
			ASSERT_EQUAL(st.size(), my_st.size());
			ASSERT_EQUAL(contToString(st), contToString(my_st));
			

			it = st.find("three_1");
			my_it = my_st.find("three_1");
			st.erase(it);
			my_st.erase(my_it);
			ASSERT_EQUAL(st.size(), my_st.size());
			ASSERT_EQUAL(contToString(st), contToString(my_st));
		}
	}

	void erase_key_test() {
		{
			std::set<int> st(g_vc.begin(), g_vc.end());
			ft::set<int> my_st(g_vc.begin(), g_vc.end());

			size_t t1, t2;
			
			t1 = st.erase(9);
			t2 = my_st.erase(9);
			ASSERT_EQUAL(t1, t2);
			ASSERT_EQUAL(st.size(), my_st.size());
			
			t1 = st.erase(0);
			t2 = my_st.erase(0);
			ASSERT_EQUAL(t1, t2);
			ASSERT_EQUAL(st.size(), my_st.size());

			t1 = st.erase(2);
			t2 = my_st.erase(2);
			ASSERT_EQUAL(t1, t2);
			ASSERT_EQUAL(st.size(), my_st.size());

			t1 = st.erase(3);
			t2 = my_st.erase(3);
			ASSERT_EQUAL(t1, t2);
			ASSERT_EQUAL(st.size(), my_st.size());

			t1 = st.erase(14);
			t2 = my_st.erase(14);
			ASSERT_EQUAL(t1, t2);
			ASSERT_EQUAL(st.size(), my_st.size());

			t1 = st.erase(7);
			t2 = my_st.erase(7);
			ASSERT_EQUAL(t1, t2);
			ASSERT_EQUAL(st.size(), my_st.size());
			
			t1 = st.erase(-7);
			t2 = my_st.erase(-7);
			ASSERT_EQUAL(t1, t2);
			ASSERT_EQUAL(st.size(), my_st.size());

			ASSERT_EQUAL(contToString(st), contToString(my_st));
		}
	}

	void erase_range_test() {
		{
			std::set<int> st(g_vc.begin(), g_vc.end());
			ft::set<int> my_st(g_vc.begin(), g_vc.end());

			std::pair<std::set<int>::iterator, bool> it = st.insert(5);
			std::pair<ft::set<int>::iterator, bool> my_it = my_st.insert(5);

			st.erase(++st.begin(), it.first);
			my_st.erase(++my_st.begin(), my_it.first);
			ASSERT_EQUAL(contToString(st), contToString(my_st));

			st.erase(it.first, --st.end());
			my_st.erase(my_it.first, --my_st.end());
			ASSERT_EQUAL(contToString(st), contToString(my_st));
			
			
			st.erase(st.begin(), st.end());
			my_st.erase(my_st.begin(), my_st.end());
			ASSERT_EQUAL(contToString(st), contToString(my_st));
		}
	}

	void clear_test() {
		std::set<int> st1(g_vc.begin(), g_vc.end());
		ft::set<int> my_st1(g_vc.begin(), g_vc.end());

		st1.clear();
		my_st1.clear();
		ASSERT_EQUAL(contToString(st1), contToString(my_st1));
		ASSERT_EQUAL(st1.size(), my_st1.size());

		st1.clear();
		my_st1.clear();
		ASSERT_EQUAL(contToString(st1), contToString(my_st1));
		ASSERT_EQUAL(st1.size(), my_st1.size());
	}

	void swap_test() {

		std::set<int> st1(g_vc.begin(), g_vc.end());
		ft::set<int> my_st1(g_vc.begin(), g_vc.end());
		ASSERT_EQUAL(contToString(st1), contToString(my_st1));

		std::set<int> st2(g_vc.begin(), g_vc.end());
		ft::set<int> my_st2(g_vc.begin(), g_vc.end());

		st1.erase(st1.begin());
		my_st1.erase(my_st1.begin());
		ASSERT_EQUAL(contToString(st1), contToString(my_st1));
		
		st1.erase(st1.begin());
		my_st1.erase(my_st1.begin());
		ASSERT_EQUAL(contToString(st1), contToString(my_st1));

		st1.swap(st2);
		my_st1.swap(my_st2);
		ASSERT_EQUAL(contToString(st1), contToString(my_st1));
		ASSERT_EQUAL(contToString(st2), contToString(my_st2));
		ASSERT_EQUAL(st1.size(), my_st1.size());
		ASSERT_EQUAL(st2.size(), my_st2.size());

		swap(st1, st2);
		swap(my_st1, my_st2);
		ASSERT_EQUAL(contToString(st1), contToString(my_st1));
		ASSERT_EQUAL(contToString(st2), contToString(my_st2));
		ASSERT_EQUAL(st1.size(), my_st1.size());
		ASSERT_EQUAL(st2.size(), my_st2.size());
	}

	void lower_bound_test() {
		std::set<int> st(g_vc.begin(), g_vc.end());
		ft::set<int> my_st(g_vc.begin(), g_vc.end());

		std::set<int>::iterator it = st.lower_bound(2);
		ft::set<int>::iterator my_it = my_st.lower_bound(2);

		ASSERT_EQUAL(*it, *my_it);

		it = st.lower_bound(55);
		my_it = my_st.lower_bound(55);
		ASSERT_EQUAL(it == st.end(), true);
		ASSERT_EQUAL(my_it == my_st.end(), true);

		std::set<int>::iterator it2 = st.find(0);
		ft::set<int>::iterator my_it2 = my_st.find(0);

		it2++;
		my_it2++;
		it = st.lower_bound(0);
		my_it = my_st.lower_bound(0);
		ASSERT_EQUAL(*it, *my_it);
		ASSERT_EQUAL(*it2, *my_it2);
		
		it = st.lower_bound(9);
		my_it = my_st.lower_bound(9);
		ASSERT_EQUAL(*it, *my_it);
		
		it = st.lower_bound(8);
		my_it = my_st.lower_bound(8);
		ASSERT_EQUAL(*it, *my_it);
	}

	void upper_bound_test() {
		std::set<int> st(g_vc.begin(), g_vc.end());
		ft::set<int> my_st(g_vc.begin(), g_vc.end());

		std::set<int>::iterator it = st.upper_bound(5);
		ft::set<int>::iterator my_it = my_st.upper_bound(5);
		ASSERT_EQUAL(*it, *my_it);

		it = st.upper_bound(0);
		my_it = my_st.upper_bound(0);
		ASSERT_EQUAL(*it, *my_it);

		std::set<int>::iterator it2 = st.find(6);
		ft::set<int>::iterator my_it2 = my_st.find(6);

		it = st.upper_bound(5);
		my_it = my_st.upper_bound(5);
		ASSERT_EQUAL(*it, *it2);
		ASSERT_EQUAL(*my_it, *my_it2);
		
		it = st.upper_bound(9);
		my_it = my_st.upper_bound(9);
		ASSERT_EQUAL(it == st.end(), true);
		ASSERT_EQUAL(my_it == my_st.end(), true);
		
		it = st.upper_bound(150);
		my_it = my_st.upper_bound(150);
		ASSERT_EQUAL(it == st.end(), true);
		ASSERT_EQUAL(my_it == my_st.end(), true);
	}

	void equal_range_test() {

		std::set<int> st(g_vc.begin(), g_vc.end());
		ft::set<int> my_st(g_vc.begin(), g_vc.end());

		std::set<int>::iterator it;
		ft::set<int>::iterator my_it;

		std::pair<std::set<int>::iterator, std::set<int>::iterator> pr;
		std::pair<ft::set<int>::iterator, ft::set<int>::iterator> my_pr;

		{
			pr = st.equal_range(0);
			my_pr = my_st.equal_range(0);
			ASSERT_EQUAL(*(pr.first), *(my_pr.first));
		}
		{
			it = st.lower_bound(1);
			my_it = my_st.lower_bound(1);
			pr = st.equal_range(1);
			my_pr = my_st.equal_range(1);

			ASSERT_EQUAL(pr.first == it, true);
			ASSERT_EQUAL(my_pr.first == my_it, true);
		}
		{
			it = st.lower_bound(5);
			my_it = my_st.lower_bound(5);
			pr = st.equal_range(5);
			my_pr = my_st.equal_range(5);

			ASSERT_EQUAL(pr.first == it, true);
			ASSERT_EQUAL(my_pr.first == my_it, true);
		}
		{
			it = st.lower_bound(8);
			my_it = my_st.lower_bound(8);
			pr = st.equal_range(8);
			my_pr = my_st.equal_range(8);

			ASSERT_EQUAL(pr.first == it, true);
			ASSERT_EQUAL(my_pr.first == my_it, true);
		}
		{
			it = st.lower_bound(9);
			my_it = my_st.lower_bound(9);
			pr = st.equal_range(9);
			my_pr = my_st.equal_range(9);

			ASSERT_EQUAL(pr.first == it, true);
			ASSERT_EQUAL(my_pr.first == my_it, true);
		}
		{
			it = st.lower_bound(101);
			my_it = my_st.lower_bound(101);
			pr = st.equal_range(101);
			my_pr = my_st.equal_range(101);

			ASSERT_EQUAL(pr.first == st.end(), true);
			ASSERT_EQUAL(my_pr.first == my_st.end(), true);
		}
		{
			it = st.lower_bound(1100);
			my_it = my_st.lower_bound(1100);
			pr = st.equal_range(1100);
			my_pr = my_st.equal_range(1100);

			ASSERT_EQUAL(pr.first == st.end(), true);
			ASSERT_EQUAL(my_pr.first == my_st.end(), true);
		}
	}

	void print_vect(std::vector<int> v) {

		if (ENABLE_LOGS) {
			for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
				cout << *it << ", ";
			cout << endl;
		}
	}

	void operators_test() {
		std::set<int> st1, st2;
		ft::set<int> my_st1, my_st2;

		std::vector<int> src(g_vc);
		std::vector<int> v[6];

		v[0] = src;			// 1,2,3,4,5,6,7,8,9,0,1,2,3,1,3,-1
		v[1] = v[0];
		print_vect(v[1]);

		v[2] = src;
		v[2][2] = 5;
		print_vect(v[2]);	// 1,2,5,4,5,6,7,8,9,0,1,2,3,1,3,-1

		v[3] = src;
		v[3][2] = 4;
		print_vect(v[3]);	// 1,2,4,4,5,6,7,8,9,0,1,2,3,1,3,-1

		v[4] = src;
		v[4].pop_back();
		print_vect(v[4]);	// 1,2,3,4,5,6,7,8,9,0,1,2,3,1,3

		v[5] = src;
		v[5].push_back(0);
		print_vect(v[5]);	// 1,2,3,4,5,6,7,8,9,0,1,2,3,1,3,-1,0

		{
			for (int i = 0; i < 6; i++) {
				st1.insert(v[i].begin(), v[i].end());
				my_st1.insert(v[i].begin(), v[i].end());
				for (int j = 0; j < 6; j++) {
					st2.insert(v[j].begin(), v[j].end());
					my_st2.insert(v[j].begin(), v[j].end());
					ASSERT_EQUAL(st1 != st2, my_st1 != my_st2);
				}
				st1.clear();
				my_st1.clear();
				st2.clear();
				my_st2.clear();
			}
		}
		{
			for (int i = 0; i < 6; i++) {
				st1.insert(v[i].begin(), v[i].end());
				my_st1.insert(v[i].begin(), v[i].end());
				for (int j = 0; j < 6; j++) {
					st2.insert(v[j].begin(), v[j].end());
					my_st2.insert(v[j].begin(), v[j].end());
					ASSERT_EQUAL(st1 != st2, my_st1 != my_st2);
				}
			}
		}
		{
			for (int i = 0; i < 6; i++) {
				st1.insert(v[i].begin(), v[i].end());
				my_st1.insert(v[i].begin(), v[i].end());
				for (int j = 0; j < 6; j++) {
					st2.insert(v[j].begin(), v[j].end());
					my_st2.insert(v[j].begin(), v[j].end());
					ASSERT_EQUAL(st1 < st2, my_st1 < my_st2);
				}
			}
		}
		{
			for (int i = 0; i < 6; i++) {
				st1.insert(v[i].begin(), v[i].end());
				my_st1.insert(v[i].begin(), v[i].end());
				for (int j = 0; j < 6; j++) {
					st2.insert(v[j].begin(), v[j].end());
					my_st2.insert(v[j].begin(), v[j].end());
					ASSERT_EQUAL(st1 <= st2, my_st1 <= my_st2);
				}
			}
		}
		{
			for (int i = 0; i < 6; i++) {
				st1.insert(v[i].begin(), v[i].end());
				my_st1.insert(v[i].begin(), v[i].end());
				for (int j = 0; j < 6; j++) {
					st2.insert(v[j].begin(), v[j].end());
					my_st2.insert(v[j].begin(), v[j].end());
					ASSERT_EQUAL(st1 > st2, my_st1 > my_st2);
				}
			}
		}
		{
			for (int i = 0; i < 6; i++) {
				st1.insert(v[i].begin(), v[i].end());
				my_st1.insert(v[i].begin(), v[i].end());
				for (int j = 0; j < 6; j++) {
					st2.insert(v[j].begin(), v[j].end());
					my_st2.insert(v[j].begin(), v[j].end());
					ASSERT_EQUAL(st1 >= st2, my_st1 >= my_st2);
				}
			}
		}
	}
}