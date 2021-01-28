#include <map>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <map>
#include "tests.hpp"
#include "test_runner.h"
#include "multimap.hpp"

/*********************************************************************/
/*								TESTS								 */
/*********************************************************************/
namespace ft_multimap
{
	void constructorDefault_test() {

		ft::multimap<int, int> my_mp1;
		ASSERT_EQUAL(0u, my_mp1.size());

		ft::multimap<std::string, ft::stack<double> > my_mp2;
		ASSERT_EQUAL(0u, my_mp2.size());

		// ft::multimap<int, int> my_mp3 = my_mp1;
		// ASSERT_EQUAL(0u, my_mp3.size());
	}

	void constructorRange_test() {
		{
			std::multimap<int, int> mp(g_map1.begin(), g_map1.end());	// map from std::multimap<int, int> - unsorted
			ft::multimap<int, int> my_mp(g_map1.begin(), g_map1.end());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			print_tree(my_mp);
		}
		{
			std::multimap<int, int> mp(g_map2.begin(), g_map2.end());	// map from std::multimap<int, int> - sorted
			ft::multimap<int, int> my_mp(g_map2.begin(), g_map2.end());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			print_tree(my_mp);
		}
		{
			std::multimap<std::string, int> mp(g_map3.begin(), g_map3.end());	// map from std::multimap<std::string, int> - unsorted
			ft::multimap<std::string, int> my_mp(g_map3.begin(), g_map3.end());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			mapToString(mp);
			mapToString(my_mp);
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			print_tree(my_mp);
		}
		{
			std::vector<std::pair<int, int> > v;
			for (int i = 0; i < 20; i++) v.push_back(make_pair(i, rand() % 50));

			std::multimap<int, int> mp(v.begin(), v.end());	// map from std::multimap<int, int> - unsorted
			ft::multimap<int, int> my_mp(v.begin(), v.end());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			print_tree(my_mp);
		}
	}

	void constructorCopy_test() {
		{
			ft::multimap<int, int> my_mp1;
			ASSERT_EQUAL(0u, my_mp1.size());

			ft::multimap<int, int> my_mp2(my_mp1);
			ASSERT_EQUAL(0u, my_mp2.size());
		}
		{
			std::multimap<int, int> mp(g_map1.begin(), g_map1.end());
			ft::multimap<int, int> my_mp(g_map1.begin(), g_map1.end());

			std::multimap<int, int> mp2(mp);
			ft::multimap<int, int> my_mp2(my_mp);

			ASSERT_EQUAL(mp2.size(), my_mp2.size());
			ASSERT_EQUAL(mapToString(mp2), mapToString(my_mp2));

			ASSERT_EQUAL(my_mp.size(), my_mp2.size());
			ASSERT_EQUAL(mapToString(my_mp), mapToString(my_mp2));
		}
		{
			std::multimap<int, int> mp(g_map1.begin(), g_map1.end());
			ft::multimap<int, int> my_mp(g_map1.begin(), g_map1.end());

			std::multimap<int, int> mp2 = mp;
			ft::multimap<int, int> my_mp2 = my_mp;

			ASSERT_EQUAL(mp2.size(), my_mp2.size());
			ASSERT_EQUAL(mapToString(mp2), mapToString(my_mp2));

			ASSERT_EQUAL(my_mp.size(), my_mp2.size());
			ASSERT_EQUAL(mapToString(my_mp), mapToString(my_mp2));
		}
		{
			std::multimap<int, int> mp(g_map1.begin(), g_map1.end());
			ft::multimap<int, int> my_mp(g_map1.begin(), g_map1.end());

			std::multimap<int, int> mp2; 
			mp2 = mp;
			ft::multimap<int, int> my_mp2;
			my_mp2 = my_mp;

			ASSERT_EQUAL(mp2.size(), my_mp2.size());
			ASSERT_EQUAL(mapToString(mp2), mapToString(my_mp2));

			ASSERT_EQUAL(my_mp.size(), my_mp2.size());
			ASSERT_EQUAL(mapToString(my_mp), mapToString(my_mp2));
		}
	}

	void begin_end_test() {

		std::multimap<int, int> mp(g_map1.begin(), g_map1.end());
		std::multimap<int, int>::iterator it;
		std::multimap<int, int>::reverse_iterator r_it;

		ft::multimap<int, int> my_mp(g_map1.begin(), g_map1.end());
		ft::multimap<int, int>::iterator my_it;
		ft::multimap<int, int>::reverse_iterator my_r_it;

		it = mp.begin();
		my_it = my_mp.begin();
		ASSERT_EQUAL(it->first, my_it->first);
		ASSERT_EQUAL(it->second, my_it->second);

		it = ++mp.begin();
		my_it = ++my_mp.begin();
		ASSERT_EQUAL(it->first, my_it->first);
		ASSERT_EQUAL(it->second, my_it->second);

		it = mp.begin()++;
		my_it = my_mp.begin()++;
		ASSERT_EQUAL(it->first, my_it->first);
		ASSERT_EQUAL(it->second, my_it->second);

		it = --mp.end();
		my_it = --my_mp.end();
		ASSERT_EQUAL(it->first, my_it->first);
		ASSERT_EQUAL(it->second, my_it->second);

		// reverse iterator
		r_it = mp.rbegin();
		my_r_it = my_mp.rbegin();
		ASSERT_EQUAL(r_it->first, my_r_it->first);
		ASSERT_EQUAL(r_it->second, my_r_it->second);

		r_it = ++mp.rbegin();
		my_r_it = ++my_mp.rbegin();
		ASSERT_EQUAL(r_it->first, my_r_it->first);
		ASSERT_EQUAL(r_it->second, my_r_it->second);

		r_it = mp.rbegin()++;
		my_r_it = my_mp.rbegin()++;
		ASSERT_EQUAL(r_it->first, my_r_it->first);
		ASSERT_EQUAL(r_it->second, my_r_it->second);

		r_it = --mp.rend();
		my_r_it = --my_mp.rend();
		ASSERT_EQUAL(r_it->first, my_r_it->first);
		ASSERT_EQUAL(r_it->second, my_r_it->second);
	}


	void size_test() {

		ft::multimap<int, int> my_mp1;
		ASSERT_EQUAL(0u, my_mp1.size());

		std::multimap<int, int> mp2(g_map1.begin(), g_map1.end());
		ft::multimap<int, int> my_mp2(g_map1.begin(), g_map1.end());
		ASSERT_EQUAL(mp2.size(), my_mp2.size());
	}

	void max_size_test() {
		
		std::multimap<int, int> mp;
		ft::multimap<int, int> my_mp;
		ASSERT_EQUAL(mp.max_size(), my_mp.max_size());
	}

	void empty_test() {

		ft::multimap<int, int> my_mp1;
		ASSERT_EQUAL(true, my_mp1.empty());

		ft::multimap<int, int> my_mp2(g_map1.begin(), g_map1.end());
		ASSERT_EQUAL(false, my_mp2.empty());
	}

	void find_test() {
		std::multimap<int, int> mp(g_map1.begin(), g_map1.end());
		ft::multimap<int, int> my_mp(g_map1.begin(), g_map1.end());

		std::multimap<int, int>::iterator it;
		ft::multimap<int, int>::iterator my_it;

		it = mp.find(19);
		my_it = my_mp.find(19);
		ASSERT_EQUAL(it == mp.end(), my_it == my_mp.end());			// value not found

		it = mp.find(75);
		my_it = my_mp.find(75);
		ASSERT_EQUAL(it->first, my_it->first);
		ASSERT_EQUAL(it->second, my_it->second);
	}

	void count_test() {
	
		std::multimap<int, int> mp(g_map2.begin(), g_map2.end());
		ft::multimap<int, int> my_mp(g_map2.begin(), g_map2.end());

		ASSERT_EQUAL(mp.count(16),   my_mp.count(16));			// value not found
		ASSERT_EQUAL(mp.count(-1),   my_mp.count(-1));
		ASSERT_EQUAL(mp.count(0),    my_mp.count(0));
		ASSERT_EQUAL(mp.count(1000), my_mp.count(1000));

		ASSERT_EQUAL(mp.count(25),  my_mp.count(25));
		ASSERT_EQUAL(mp.count(1),   my_mp.count(1));
		ASSERT_EQUAL(mp.count(100), my_mp.count(100));
		ASSERT_EQUAL(mp.count(60),  my_mp.count(60));
		ASSERT_EQUAL(mp.count(80),  my_mp.count(80));
	}

	void insert_range_test() {

		std::multimap<int, int> mp1;
		ft::multimap<int, int> my_mp1;

		mp1.insert(g_map1.begin(), g_map1.end());
		my_mp1.insert(g_map1.begin(), g_map1.end());
		ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));

		mp1.insert(g_map2.begin(), g_map2.end());
		my_mp1.insert(g_map2.begin(), g_map2.end());
		ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));
		print_tree(my_mp1);

		std::multimap<std::string, int> mp2;
		ft::multimap<std::string, int> my_mp2;
		mp2.insert(g_map3.begin(), g_map3.end());
		my_mp2.insert(g_map3.begin(), g_map3.end());
		ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));

		mp2.insert(g_map3.rbegin(), g_map3.rend());
		my_mp2.insert(g_map3.rbegin(), g_map3.rend());
		ASSERT_EQUAL(mapToString(mp2), mapToString(my_mp2));
	}

	void insert_single_test() {
		{
			std::multimap<int, int> mp;
			ft::multimap<int, int> my_mp;
			
			std::multimap<int, int>::iterator it;
			ft::multimap<int, int>::iterator my_it;

			std::multimap<int, int>::iterator pr;
			ft::multimap<int, int>::iterator my_pr;

			pr = mp.insert(std::make_pair(10, 5));
			my_pr = my_mp.insert(std::make_pair(10, 5));
			
			ASSERT_EQUAL(pr->first, my_pr->first);
			ASSERT_EQUAL(pr->second, my_pr->second);
			ASSERT_EQUAL(mp.size(), my_mp.size());

			pr = mp.insert(std::make_pair(10, 5));
			my_pr = my_mp.insert(std::make_pair(10, 5));
			ASSERT_EQUAL(pr->first, my_pr->first);
			ASSERT_EQUAL(pr->second, my_pr->second);
			ASSERT_EQUAL(mp.size(), my_mp.size());

			pr = mp.insert(std::make_pair(10, 15));
			my_pr = my_mp.insert(std::make_pair(10, 15));
			ASSERT_EQUAL(pr->first, my_pr->first);
			ASSERT_EQUAL(pr->second, my_pr->second);
			ASSERT_EQUAL(mp.size(), my_mp.size());

			pr = mp.insert(std::make_pair(15, 15));
			my_pr = my_mp.insert(std::make_pair(15, 15));
			ASSERT_EQUAL(pr->first, my_pr->first);
			ASSERT_EQUAL(pr->second, my_pr->second);
			ASSERT_EQUAL(mp.size(), my_mp.size());
		}
		{
			std::multimap<int, int> mp(g_map1.begin(), g_map1.end());
			ft::multimap<int, int> my_mp(g_map1.begin(), g_map1.end());

			std::multimap<int, int>::iterator pr;
			ft::multimap<int, int>::iterator my_pr;

			pr = mp.insert(std::make_pair(10, 5));
			my_pr = my_mp.insert(std::make_pair(10, 5));
			
			ASSERT_EQUAL(pr->first, my_pr->first);
			ASSERT_EQUAL(pr->second, my_pr->second);
			ASSERT_EQUAL(pr->second, my_pr->second);
			ASSERT_EQUAL(mp.size(), my_mp.size());

			pr = mp.insert(std::make_pair(10, 5));
			my_pr = my_mp.insert(std::make_pair(10, 5));
			ASSERT_EQUAL(pr->first, my_pr->first);
			ASSERT_EQUAL(pr->second, my_pr->second);
			ASSERT_EQUAL(mp.size(), my_mp.size());

			pr = mp.insert(std::make_pair(10, 15));
			my_pr = my_mp.insert(std::make_pair(10, 15));
			ASSERT_EQUAL(pr->first, my_pr->first);
			ASSERT_EQUAL(pr->second, my_pr->second);
			ASSERT_EQUAL(mp.size(), my_mp.size());

			pr = mp.insert(std::make_pair(15, 15));
			my_pr = my_mp.insert(std::make_pair(15, 15));
			ASSERT_EQUAL(pr->first, my_pr->first);
			ASSERT_EQUAL(pr->second, my_pr->second);
			ASSERT_EQUAL(mp.size(), my_mp.size());
		}
	}

	void insert_hint_test() {
		{
			std::pair<int, int> pr1(12, 1);
			std::pair<int, int> pr2(11, 1);

			std::multimap<int, int> mp(g_map1.begin(), g_map1.end());
			ft::multimap<int, int> my_mp(g_map1.begin(), g_map1.end());

			std::multimap<int, int>::iterator it;
			ft::multimap<int, int>::iterator my_it;

			it = mp.find(55);
			my_it = my_mp.find(55);
			it = mp.insert(it, pr1);
			my_it = my_mp.insert(my_it, pr1);
			ASSERT_EQUAL(it->first, my_it->first);
			ASSERT_EQUAL(it->second, my_it->second);
			ASSERT_EQUAL(mp.size(), my_mp.size());

			it = mp.find(100);
			my_it = my_mp.find(100);
			it = mp.insert(it, pr2);
			my_it = my_mp.insert(my_it, pr2);
			ASSERT_EQUAL(it->first, my_it->first);
			ASSERT_EQUAL(it->second, my_it->second);
			ASSERT_EQUAL(mp.size(), my_mp.size());
		}
	}

	void erase_single_test() {
		{
			std::multimap<int, int> mp(g_map1.begin(), g_map1.end());
			ft::multimap<int, int> my_mp(g_map1.begin(), g_map1.end());
			
			mp.erase(mp.begin());
			my_mp.erase(my_mp.begin());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));

			mp.erase(++mp.begin());
			my_mp.erase(++my_mp.begin());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));

			mp.erase(--mp.end());
			my_mp.erase(--my_mp.end());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));

			mp.erase(mp.begin());
			my_mp.erase(my_mp.begin());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));

			std::multimap<int, int>::iterator pr = mp.insert(make_pair(64, 1));
			ft::multimap<int, int>::iterator my_pr = my_mp.insert(make_pair(64, 1));
			print_tree(my_mp);

			std::multimap<int, int>::iterator it = pr;
			ft::multimap<int, int>::iterator my_it = my_pr;
			mp.erase(it);
			my_mp.erase(my_it);
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			print_tree(my_mp);

			it = mp.find(35);
			my_it = my_mp.find(35);
			mp.erase(it);
			my_mp.erase(my_it);
			ASSERT_EQUAL(mp.size(), my_mp.size());
			mapToString(mp);
			mapToString(my_mp);
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			print_tree(my_mp);

			mp.erase(mp.begin());
			my_mp.erase(my_mp.begin());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			print_tree(my_mp);

			mp.erase(mp.begin());
			my_mp.erase(my_mp.begin());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			print_tree(my_mp);
			
			mp.erase(mp.begin());
			my_mp.erase(my_mp.begin());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			print_tree(my_mp);
			
			mp.erase(--mp.end());
			my_mp.erase(--my_mp.end());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));

			mp.erase(--mp.end());
			my_mp.erase(--my_mp.end());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));

			mp.erase(--mp.end());
			my_mp.erase(--my_mp.end());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			print_tree(my_mp);
		}
		{
			std::multimap<std::string, int> mp(g_map3.begin(), g_map3.end());
			ft::multimap<std::string, int> my_mp(g_map3.begin(), g_map3.end());

			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			mp.erase(mp.begin());
			my_mp.erase(my_mp.begin());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));

			print_tree(my_mp);
			mp.erase(++mp.begin());
			my_mp.erase(++my_mp.begin());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			
			print_tree(my_mp);
			mp.erase(++mp.begin());
			my_mp.erase(++my_mp.begin());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));

			print_tree(my_mp);
			mp.erase(mp.begin());
			my_mp.erase(my_mp.begin());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));

			mp.erase(--mp.end());
			my_mp.erase(--my_mp.end());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));

			mp.erase(--mp.end());
			my_mp.erase(--my_mp.end());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));

			std::multimap<std::string, int>::iterator pr = mp.insert(make_pair("odin", 1));
			ft::multimap<std::string, int>::iterator my_pr = my_mp.insert(make_pair("odin", 1));

			std::multimap<std::string, int>::iterator it = pr;
			ft::multimap<std::string, int>::iterator my_it = my_pr;

			mp.erase(it);
			my_mp.erase(my_it);
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			print_tree(my_mp);

			it = mp.find("seven");
			my_it = my_mp.find("seven");
			mp.erase(it);
			my_mp.erase(my_it);
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			print_tree(my_mp);

			it = mp.find("three");
			my_it = my_mp.find("three");
			mp.erase(it);
			my_mp.erase(my_it);
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			print_tree(my_mp);

			it = mp.find("thirteen");
			my_it = my_mp.find("thirteen");
			mp.erase(it);
			my_mp.erase(my_it);
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			print_tree(my_mp);

			it = mp.find("ten");
			my_it = my_mp.find("ten");
			mp.erase(it);
			my_mp.erase(my_it);
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			print_tree(my_mp);
		}
	}

	void erase_key_test() {
		{
			std::multimap<int, int> mp(g_map1.begin(), g_map1.end());
			ft::multimap<int, int> my_mp(g_map1.begin(), g_map1.end());

			size_t t1, t2;
			
			t1 = mp.erase(100);
			t2 = my_mp.erase(100);
			ASSERT_EQUAL(t1, t2);
			ASSERT_EQUAL(mp.size(), my_mp.size());
			
			t1 = mp.erase(0);
			t2 = my_mp.erase(0);
			ASSERT_EQUAL(t1, t2);
			ASSERT_EQUAL(mp.size(), my_mp.size());

			t1 = mp.erase(12);
			t2 = my_mp.erase(12);
			ASSERT_EQUAL(t1, t2);
			ASSERT_EQUAL(mp.size(), my_mp.size());

			t1 = mp.erase(35);
			t2 = my_mp.erase(35);
			ASSERT_EQUAL(t1, t2);
			ASSERT_EQUAL(mp.size(), my_mp.size());

			t1 = mp.erase(14);
			t2 = my_mp.erase(14);
			ASSERT_EQUAL(t1, t2);
			ASSERT_EQUAL(mp.size(), my_mp.size());

			t1 = mp.erase(140);
			t2 = my_mp.erase(140);
			ASSERT_EQUAL(t1, t2);
			ASSERT_EQUAL(mp.size(), my_mp.size());
			
			t1 = mp.erase(-140);
			t2 = my_mp.erase(-140);
			ASSERT_EQUAL(t1, t2);
			ASSERT_EQUAL(mp.size(), my_mp.size());

			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));

			print_tree(my_mp);
		}
	}

	void erase_range_test() {
		{
			std::multimap<int, int> mp(g_map1.begin(), g_map1.end());
			ft::multimap<int, int> my_mp(g_map1.begin(), g_map1.end());

			std::multimap<int, int>::iterator it = mp.insert(make_pair(64, 10));
			ft::multimap<int, int>::iterator my_it = my_mp.insert(make_pair(64, 10));

			mp.erase(++mp.begin(), it);
			my_mp.erase(++my_mp.begin(), my_it);
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));

			mp.erase(it, --mp.end());
			my_mp.erase(my_it, --my_mp.end());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
			
			
			mp.erase(mp.begin(), mp.end());
			my_mp.erase(my_mp.begin(), my_mp.end());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
		}
	}

	void clear_test() {
		std::multimap<int, int> mp1(g_map1.begin(), g_map1.end());
		ft::multimap<int, int> my_mp1(g_map1.begin(), g_map1.end());

		mp1.clear();
		my_mp1.clear();
		ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));
		ASSERT_EQUAL(mp1.size(), my_mp1.size());

		mp1.clear();
		my_mp1.clear();
		ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));
		ASSERT_EQUAL(mp1.size(), my_mp1.size());
	}

	void swap_test() {
		std::multimap<int, int> mp1(g_map1.begin(), g_map1.end());
		ft::multimap<int, int> my_mp1(g_map1.begin(), g_map1.end());
		ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));

		std::multimap<int, int> mp2(g_map1.begin(), g_map1.end());
		ft::multimap<int, int> my_mp2(g_map1.begin(), g_map1.end());

		mp1.erase(mp1.begin());
		my_mp1.erase(my_mp1.begin());
		ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));
		
		mp1.erase(mp1.begin());
		my_mp1.erase(my_mp1.begin());
		ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));

		mp1.swap(mp2);
		my_mp1.swap(my_mp2);
		ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));
		ASSERT_EQUAL(mapToString(mp2), mapToString(my_mp2));
		ASSERT_EQUAL(mp1.size(), my_mp1.size());
		ASSERT_EQUAL(mp2.size(), my_mp2.size());

		swap(mp1, mp2);
		swap(my_mp1, my_mp2);
		ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));
		ASSERT_EQUAL(mapToString(mp2), mapToString(my_mp2));
		ASSERT_EQUAL(mp1.size(), my_mp1.size());
		ASSERT_EQUAL(mp2.size(), my_mp2.size());
	}

	void lower_bound_test() {
		std::multimap<int, int> mp(g_map1.begin(), g_map1.end());
		ft::multimap<int, int> my_mp(g_map1.begin(), g_map1.end());

		std::multimap<int, int>::iterator it = mp.lower_bound(12);
		ft::multimap<int, int>::iterator my_it = my_mp.lower_bound(12);

		ASSERT_EQUAL(it->first, my_it->first);
		ASSERT_EQUAL(it->second, my_it->second);

		it = mp.lower_bound(55);
		my_it = my_mp.lower_bound(55);

		ASSERT_EQUAL(it->first, my_it->first);
		ASSERT_EQUAL(it->second, my_it->second);

		std::multimap<int, int>::iterator it2 = mp.find(12);
		ft::multimap<int, int>::iterator my_it2 = my_mp.find(12);

		it2++;
		my_it2++;
		it = mp.lower_bound(14);
		my_it = my_mp.lower_bound(14);
		ASSERT_EQUAL(it->first, it2->first);
		ASSERT_EQUAL(it->second, it2->second);
		ASSERT_EQUAL(my_it->first, my_it2->first);
		ASSERT_EQUAL(my_it->second, my_it2->second);
		
		it = mp.lower_bound(100);
		my_it = my_mp.lower_bound(100);
		ASSERT_EQUAL(it->first, my_it->first);
		ASSERT_EQUAL(it->second, my_it->second);
		
		it = mp.lower_bound(150);
		my_it = my_mp.lower_bound(150);
		ASSERT_EQUAL(it == mp.end(), true);
		ASSERT_EQUAL(my_it == my_mp.end(), true);
	}

	void upper_bound_test() {
		std::multimap<int, int> mp(g_map1.begin(), g_map1.end());
		ft::multimap<int, int> my_mp(g_map1.begin(), g_map1.end());

		std::multimap<int, int>::iterator it = mp.upper_bound(12);
		ft::multimap<int, int>::iterator my_it = my_mp.upper_bound(12);

		ASSERT_EQUAL(it->first, my_it->first);
		ASSERT_EQUAL(it->second, my_it->second);

		it = mp.upper_bound(55);
		my_it = my_mp.upper_bound(55);

		ASSERT_EQUAL(it->first, my_it->first);
		ASSERT_EQUAL(it->second, my_it->second);

		std::multimap<int, int>::iterator it2 = mp.find(25);
		ft::multimap<int, int>::iterator my_it2 = my_mp.find(25);

		it = mp.upper_bound(14);
		my_it = my_mp.upper_bound(14);
		ASSERT_EQUAL(*it == *it2, true);
		ASSERT_EQUAL(*my_it == *my_it2, true);
		
		it = mp.upper_bound(100);
		my_it = my_mp.upper_bound(100);
		ASSERT_EQUAL(it == mp.end(), true);
		ASSERT_EQUAL(my_it == my_mp.end(), true);
		
		it = mp.upper_bound(150);
		my_it = my_mp.upper_bound(150);
		ASSERT_EQUAL(it == mp.end(), true);
		ASSERT_EQUAL(my_it == my_mp.end(), true);

		it = mp.upper_bound(-2);
		my_it = my_mp.upper_bound(-2);
		ASSERT_EQUAL(it->first, my_it->first);
		ASSERT_EQUAL(it->second, my_it->second);
	}

	void equal_range_test() {

		std::multimap<int, int> mp(g_map1.begin(), g_map1.end());
		ft::multimap<int, int> my_mp(g_map1.begin(), g_map1.end());

		std::multimap<int, int>::iterator it;
		ft::multimap<int, int>::iterator my_it;

		std::pair<std::multimap<int, int>::iterator, std::multimap<int, int>::iterator> pr;
		std::pair<ft::multimap<int, int>::iterator, ft::multimap<int, int>::iterator> my_pr;

		{
			it = mp.lower_bound(0);
			my_it = my_mp.lower_bound(0);
			pr = mp.equal_range(0);
			my_pr = my_mp.equal_range(0);

			ASSERT_EQUAL(pr.first == pr.second, true);
			ASSERT_EQUAL(pr.first == it, true);

			ASSERT_EQUAL(my_pr.first == my_pr.second, true);
			ASSERT_EQUAL(my_pr.first == my_it, true);
		}
		{
			it = mp.lower_bound(1);
			my_it = my_mp.lower_bound(1);
			pr = mp.equal_range(1);
			my_pr = my_mp.equal_range(1);

			ASSERT_EQUAL(pr.first == it, true);
			ASSERT_EQUAL(my_pr.first == my_it, true);
		}
		{
			it = mp.lower_bound(5);
			my_it = my_mp.lower_bound(5);
			pr = mp.equal_range(5);
			my_pr = my_mp.equal_range(5);

			ASSERT_EQUAL(pr.first == it, true);
			ASSERT_EQUAL(my_pr.first == my_it, true);
		}
		{
			it = mp.lower_bound(50);
			my_it = my_mp.lower_bound(50);
			pr = mp.equal_range(50);
			my_pr = my_mp.equal_range(50);

			ASSERT_EQUAL(pr.first == it, true);
			ASSERT_EQUAL(my_pr.first == my_it, true);
		}
		{
			it = mp.lower_bound(51);
			my_it = my_mp.lower_bound(51);
			pr = mp.equal_range(51);
			my_pr = my_mp.equal_range(51);

			ASSERT_EQUAL(pr.first == it, true);
			ASSERT_EQUAL(my_pr.first == my_it, true);
		}
		{
			it = mp.lower_bound(100);
			my_it = my_mp.lower_bound(100);
			pr = mp.equal_range(100);
			my_pr = my_mp.equal_range(100);

			ASSERT_EQUAL(pr.first == it, true);
			ASSERT_EQUAL(my_pr.first == my_it, true);
		}
		{
			it = mp.lower_bound(101);
			my_it = my_mp.lower_bound(101);
			pr = mp.equal_range(101);
			my_pr = my_mp.equal_range(101);

			ASSERT_EQUAL(pr.first == mp.end(), true);
			ASSERT_EQUAL(my_pr.first == my_mp.end(), true);
		}
		{
			it = mp.lower_bound(1100);
			my_it = my_mp.lower_bound(1100);
			pr = mp.equal_range(1100);
			my_pr = my_mp.equal_range(1100);

			ASSERT_EQUAL(pr.first == mp.end(), true);
			ASSERT_EQUAL(my_pr.first == my_mp.end(), true);
		}

	}

	void print_vect(std::vector<std::pair<int, int> > v) {

		if (ENABLE_LOGS) {
			for (std::vector<pair<int, int> >::iterator it = v.begin(); it != v.end(); ++it)
				cout << it->first << " " << it->second << ", ";
			cout << endl;
		}
	}

	void operators_test() {
		std::multimap<int, int> mp1, mp2;
		ft::multimap<int, int> my_mp1, my_mp2;

		std::vector<pair<int, int> >src(g_map1);
		std::vector<pair<int, int> > v[6];

		v[0] = src;			// 50 1, 25 2, 8 3, 35 4, 1 5, 12 6, 30 7, 40 8, 75 9, 60 10, 90 11, 55 12, 70 13, 80 14, 100 15
		v[1] = v[0];
		print_vect(v[1]);

		v[2] = src;
		v[2][2].second = 5;
		print_vect(v[2]);	// 50 1, 25 2, 8 3, 35 4, 1 5, 12 6, 30 7, 40 8, 75 9, 60 10, 90 11, 55 12, 70 13, 80 14, 100 15

		v[3] = src;
		v[3][2] = make_pair(15, 3);
		print_vect(v[3]);	// 50 1, 25 2, 15 3, 35 4, 1 5, 12 6, 30 7, 40 8, 75 9, 60 10, 90 11, 55 12, 70 13, 80 14, 100 15

		v[4] = src;
		v[4].pop_back();
		print_vect(v[4]);	// 50 1, 25 2, 8 3, 35 4, 1 5, 12 6, 30 7, 40 8, 75 9, 60 10, 90 11, 55 12, 70 13, 80 14

		v[5] = src;
		v[5].push_back(make_pair(0, 0));
		print_vect(v[5]);	// 50 1, 25 2, 8 3, 35 4, 1 5, 12 6, 30 7, 40 8, 75 9, 60 10, 90 11, 55 12, 70 13, 80 14, 100 15, 0 0

		{
			for (int i = 0; i < 6; i++) {
				mp1.insert(v[i].begin(), v[i].end());
				my_mp1.insert(v[i].begin(), v[i].end());
				for (int j = 0; j < 6; j++) {
					mp2.insert(v[j].begin(), v[j].end());
					my_mp2.insert(v[j].begin(), v[j].end());
					ASSERT_EQUAL(mp1 == mp2, my_mp1 == my_mp2);
				}
				mp1.clear();
				my_mp1.clear();
				mp2.clear();
				my_mp2.clear();
			}
		}
		{
			for (int i = 0; i < 6; i++) {
				mp1.insert(v[i].begin(), v[i].end());
				my_mp1.insert(v[i].begin(), v[i].end());
				for (int j = 0; j < 6; j++) {
					mp2.insert(v[j].begin(), v[j].end());
					my_mp2.insert(v[j].begin(), v[j].end());
					ASSERT_EQUAL(mp1 != mp2, my_mp1 != my_mp2);
				}
			}
		}
		{
			for (int i = 0; i < 6; i++) {
				mp1.insert(v[i].begin(), v[i].end());
				my_mp1.insert(v[i].begin(), v[i].end());
				for (int j = 0; j < 6; j++) {
					mp2.insert(v[j].begin(), v[j].end());
					my_mp2.insert(v[j].begin(), v[j].end());
					ASSERT_EQUAL(mp1 < mp2, my_mp1 < my_mp2);
				}
			}
		}
		{
			for (int i = 0; i < 6; i++) {
				mp1.insert(v[i].begin(), v[i].end());
				my_mp1.insert(v[i].begin(), v[i].end());
				for (int j = 0; j < 6; j++) {
					mp2.insert(v[j].begin(), v[j].end());
					my_mp2.insert(v[j].begin(), v[j].end());
					ASSERT_EQUAL(mp1 <= mp2, my_mp1 <= my_mp2);
				}
			}
		}
		{
			for (int i = 0; i < 6; i++) {
				mp1.insert(v[i].begin(), v[i].end());
				my_mp1.insert(v[i].begin(), v[i].end());
				for (int j = 0; j < 6; j++) {
					mp2.insert(v[j].begin(), v[j].end());
					my_mp2.insert(v[j].begin(), v[j].end());
					ASSERT_EQUAL(mp1 > mp2, my_mp1 > my_mp2);
				}
			}
		}
		{
			for (int i = 0; i < 6; i++) {
				mp1.insert(v[i].begin(), v[i].end());
				my_mp1.insert(v[i].begin(), v[i].end());
				for (int j = 0; j < 6; j++) {
					mp2.insert(v[j].begin(), v[j].end());
					my_mp2.insert(v[j].begin(), v[j].end());
					ASSERT_EQUAL(mp1 >= mp2, my_mp1 >= my_mp2);
				}
			}
		}
	}
}