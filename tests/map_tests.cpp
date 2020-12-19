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

		ft::map<int, int> my_mp1;
		ASSERT_EQUAL(0u, my_mp1.size());

		// ft::map<int, int> my_mp2(my_mp1);
		// ASSERT_EQUAL(0u, my_mp2.size());

		// ft::map<int, int> my_mp3 = my_mp1;
		// ASSERT_EQUAL(0u, my_mp3.size());
	}

	void constructorCopy_test() {
		{
			std::map<int, int> mp(map1.begin(), map1.end());
			ft::map<int, int> my_mp(map1.begin(), map1.end());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
		}
	}

	void begin_end_test() {
		std::map<int, int> mp(map1.begin(), map1.end());
		std::map<int, int>::iterator it;
		std::map<int, int>::reverse_iterator r_it;

		ft::map<int, int> my_mp(map1.begin(), map1.end());
		ft::map<int, int>::iterator my_it;
		ft::map<int, int>::reverse_iterator my_r_it;

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

	void constructorRange_test() {
		{
			std::map<int, int> mp(map1.begin(), map1.end());	// map from std::map<int, int> - unsorted
			ft::map<int, int> my_mp(map1.begin(), map1.end());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
		}
		{
			std::map<int, int> mp(map2.begin(), map2.end());	// map from std::map<int, int> - sorted
			ft::map<int, int> my_mp(map2.begin(), map2.end());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
		}
		{
			std::map<std::string, int> mp(map3.begin(), map3.end());	// map from std::map<std::string, int> - unsorted
			ft::map<std::string, int> my_mp(map3.begin(), map3.end());
			ASSERT_EQUAL(mp.size(), my_mp.size());
			ASSERT_EQUAL(mapToString(mp), mapToString(my_mp));
		}
	}

	void size_test() {

		ft::map<int, int> my_mp1;
		ASSERT_EQUAL(0u, my_mp1.size());

		std::map<int, int> mp2(map1.begin(), map1.end());
		ft::map<int, int> my_mp2(map1.begin(), map1.end());
		ASSERT_EQUAL(mp2.size(), my_mp2.size());
	}

	void empty_test() {

		ft::map<int, int> my_mp1;
		ASSERT_EQUAL(true, my_mp1.empty());

		ft::map<int, int> my_mp2(map1.begin(), map1.end());
		ASSERT_EQUAL(false, my_mp2.empty());
	}

	void find_test() {
		std::map<int, int> mp(map1.begin(), map1.end());
		ft::map<int, int> my_mp(map1.begin(), map1.end());

		std::map<int, int>::iterator it;
		ft::map<int, int>::iterator my_it;

		it = mp.find(19);
		my_it = my_mp.find(19);
		ASSERT_EQUAL(it == mp.end(), my_it == my_mp.end());			// value not found

		it = mp.find(75);
		my_it = my_mp.find(75);
		ASSERT_EQUAL(it->first, my_it->first);
		ASSERT_EQUAL(it->second, my_it->second);
	}

		void count_test() {
		std::map<int, int> mp(map1.begin(), map1.end());
		ft::map<int, int> my_mp(map1.begin(), map1.end());

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

	// void max_size_test() {
		
	// 	ft::map<int, int> my_mp;
	// 	ASSERT_EQUAL(mp.max_size(), my_mp.max_size());
	// }

	// void begin_test() {
		
	// 	ft::map<int, int> my_mp(map1.begin(), map1.end());
	// 	ft::map<int, int>::iterator myit = mymap1.begin();
	// 	std::map<int, int>::iterator it = map1.begin();
	// 	ASSERT_EQUAL(*myit, *it);

	// 	*it = 100;
	// 	*myit = 100;
	// 	ASSERT_EQUAL(*it, *myit);

	// 	const ft::map<int, int> my_mp2(map1.begin(), map1.end());
	// 	ft::map<int, int>::const_iterator myit2 = mymap1.begin();
	// 	ASSERT_EQUAL(*myit2, 100);
	// 	*it = 0;
	// }

	void insert_range_test() {

		std::map<int, int> mp1;
		ft::map<int, int> my_mp1;

		mp1.insert(map1.begin(), map1.end());
		my_mp1.insert(map1.begin(), map1.end());
		ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));

		mp1.insert(map2.begin(), map2.end());
		my_mp1.insert(map2.begin(), map2.end());
		ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));

		std::map<std::string, int> mp2;
		ft::map<std::string, int> my_mp2;
		mp2.insert(map3.begin(), map3.end());
		my_mp2.insert(map3.begin(), map3.end());
		ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));

		mp2.insert(map3.rbegin(), map3.rend());
		my_mp2.insert(map3.rbegin(), map3.rend());
		ASSERT_EQUAL(mapToString(mp2), mapToString(my_mp2));
	}

	// void clear_test() {
	// 	std::map<int, int> mp1(map1.begin(), map1.end());
	// 	ft::map<int, int> my_mp1(map1.begin(), map1.end());

	// 	mp1.clear();
	// 	my_mp1.clear();
	// 	ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));
	// 	ASSERT_EQUAL(mp1.size(), my_mp1.size());

	// 	mp1.clear();
	// 	my_mp1.clear();
	// 	ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));
	// 	ASSERT_EQUAL(mp1.size(), my_mp1.size());
	// }

	// void erase_test() {
	// 	std::map<int, int> mp1(map1.begin(), map1.end());
	// 	ft::map<int, int> my_mp1(map1.begin(), map1.end());

	// 	mp1.erase(++(mp1.begin()));
	// 	my_mp1.erase(++(my_mp1.begin()));
	// 	ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));

	// 	mp1.erase(--(mp1.end()));
	// 	my_mp1.erase(--(my_mp1.end()));
	// 	ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));

	// 	mp1.erase(++(mp1.begin()), mp1.end());
	// 	my_mp1.erase(++(my_mp1.begin()), my_mp1.end());
	// 	ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));
	// 	ASSERT_EQUAL(mp1.size(), my_mp1.size());
	// }

	// void remove_test() {
	// 	std::map<int, int> mp1(map1.begin(), map1.end());
	// 	ft::map<int, int> my_mp1(map1.begin(), map1.end());

	// 	mp1.remove(5);
	// 	my_mp1.remove(5);
	// 	ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));
	// 	ASSERT_EQUAL(mp1.size(), my_mp1.size());

	// 	mp1.remove(105);
	// 	my_mp1.remove(105);
	// 	ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));
	// 	ASSERT_EQUAL(mp1.size(), my_mp1.size());
	// }

	// bool single_digit (const int& value) { return (value<5); }

	// struct is_odd {
	// bool operator() (const int& value) { return (value%2)==1; }
	// };

	// void remove_if_test() {
	// 	std::map<int, int> mp1(map1.begin(), map1.end());
	// 	ft::map<int, int> my_mp1(map1.begin(), map1.end());

	// 	mp1.remove_if(single_digit);
	// 	my_mp1.remove_if(single_digit);
	// 	ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));

	// 	mp1.remove_if(is_odd());
	// 	my_mp1.remove_if(is_odd());
	// 	ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));
	// }

	// void swap_test() {
	// 	std::map<int, int> mp1(map1.begin(), map1.end());
	// 	std::map<int, int> mp2(vc.begin(), vc.end());
	// 	ft::map<int, int> my_mp1(map1.begin(), map1.end());
	// 	ft::map<int, int> my_mp2(vc.begin(), vc.end());

	// 	mp1.swap(mp2);
	// 	my_mp1.swap(my_mp2);
	// 	ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));
	// 	ASSERT_EQUAL(mapToString(mp2), mapToString(my_mp2));
	// }

	// void unique_test() {
	// 	std::vector<int> vec;
	// 	for (int i = 0; i < 20; i++) vec.push_back(rand() % 10);

	// 	std::map<int, int> mp1(vec.begin(), vec.end());
	// 	ft::map<int, int> my_mp1(vec.begin(), vec.end());

	// 	mp1.unique();
	// 	my_mp1.unique();
	// 	ASSERT_EQUAL(mapToString(mp1), mapToString(my_mp1));
	// 	ASSERT_EQUAL(mp1.size(), my_mp1.size());
	// }

	// void operators_test() {
	// 	std::map<int, int> mp1, mp2;
	// 	ft::map<int, int> my_mp1, my_mp2;

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
	// 		my_mp1.assign(v[i].begin(), v[i].end());
	// 	for (int j = 0; j < 6; j++) {
	// 			mp2.assign(v[j].begin(), v[j].end());
	// 			my_mp2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(mp1 == mp2, my_mp1 == my_mp2);
	// 		}
	// 	}

	// 	for (int i = 0; i < 6; i++) {
	// 		mp1.assign(v[i].begin(), v[i].end());
	// 		my_mp1.assign(v[i].begin(), v[i].end());
	// 		for (int j = 0; j < 6; j++) {
	// 			mp2.assign(v[j].begin(), v[j].end());
	// 			my_mp2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(mp1 != mp2, my_mp1 != my_mp2);
	// 		}
	// 	}

	// 	for (int i = 0; i < 6; i++) {
	// 		mp1.assign(v[i].begin(), v[i].end());
	// 		my_mp1.assign(v[i].begin(), v[i].end());
	// 		for (int j = 0; j < 6; j++) {
	// 			mp2.assign(v[j].begin(), v[j].end());
	// 			my_mp2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(mp1 < mp2, my_mp1 < my_mp2);
	// 		}
	// 	}

	// 	for (int i = 0; i < 6; i++) {
	// 		mp1.assign(v[i].begin(), v[i].end());
	// 		my_mp1.assign(v[i].begin(), v[i].end());
	// 		for (int j = 0; j < 6; j++) {
	// 			mp2.assign(v[j].begin(), v[j].end());
	// 			my_mp2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(mp1 <= mp2, my_mp1 <= my_mp2);
	// 		}
	// 	}

	// 	for (int i = 0; i < 6; i++) {
	// 		mp1.assign(v[i].begin(), v[i].end());
	// 		my_mp1.assign(v[i].begin(), v[i].end());
	// 		for (int j = 0; j < 6; j++) {
	// 			mp2.assign(v[j].begin(), v[j].end());
	// 			my_mp2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(mp1 > mp2, my_mp1 > my_mp2);
	// 		}
	// 	}

	// 		for (int i = 0; i < 6; i++) {
	// 		mp1.assign(v[i].begin(), v[i].end());
	// 		my_mp1.assign(v[i].begin(), v[i].end());
	// 		for (int j = 0; j < 6; j++) {
	// 			mp2.assign(v[j].begin(), v[j].end());
	// 			my_mp2.assign(v[j].begin(), v[j].end());
	// 			ASSERT_EQUAL(mp1 >= mp2, my_mp1 >= my_mp2);
	// 		}
	// 	}
		
	// }
}