#include <stack>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include "tests.hpp"
#include "test_runner.h"
#include "stack.hpp"

/*********************************************************************/
/*								TESTS								 */
/*********************************************************************/
namespace ft_stack
{
	// void constructorDefault_test() {

	// 	std::stack<int, std::list<int>> st1;
	// 	ft::stack<int, ft::list<int>> myst1;
	// 	ASSERT_EQUAL(true, st1 == myst1);

	// 	std::stack<int, std::vector<int>> st2;
	// 	ft::stack<int, ft::vector<int>> myst2;
	// 	ASSERT_EQUAL(true, st2 == myst2);
	// }

	// void size_test() {

	// 	std::stack<int, std::list<int>> st1;
	// 	ft::stack<int, ft::list<int>> myst1;
	// 	ASSERT_EQUAL(st1.size(), myst1.size());

	// 	std::stack<int, std::vector<int>> st2;
	// 	ft::stack<int, ft::vector<int>> myst2;
	// 	ASSERT_EQUAL(st2.size(), myst2.size());
	// }

	// void empty_test() {

	// 	std::stack<int, std::list<int>> myst2;
	// 	ASSERT_EQUAL(true, myst2.empty());

	// 	myst2.push(1);
	// 	ASSERT_EQUAL(false, myst2.empty());
	// }

	// void push_test() {
	// 	std::stack<int, std::list<int>> st1;
	// 	ft::stack<int, ft::list<int>> myst1;

	// 	st1.push(17);
	// 	myst1.push(17);

	// 	st1.push(7);
	// 	myst1.push(7);

	// 	st1.push(12);
	// 	myst1.push(12);
	// 	ASSERT_EQUAL(stackToString(st1), stackToString(myst1));
	// }

	// void begin_test() {
		
	// 	std::stack<int, std::list<int>> st1;
	// 	ft::stack<int, ft::list<int>> myst1;

	// 	st1.push(17);
	// 	myst1.push(17);

	// 	ASSERT_EQUAL(st1.top(), myst1.top());
	// }

	// void pop_test() {
	// 	std::stack<int, std::list<int>> st1;
	// 	ft::stack<int, ft::list<int>> myst1;

	// 	st1.push(17);
	// 	myst1.push(17);

	// 	st1.push(7);
	// 	myst1.push(7);

	// 	st1.pop();
	// 	myst1.pop();

	// 	st1.pop();
	// 	myst1.pop();

	// 	ASSERT_EQUAL(st1.size(), myst1.size());
	// }

	// void operators_test() {
	// 	std::stack<int> st1, st2, st3, st4;
	// 	ft::stack<int> myst1, myst2, myst3, myst4;

	// 	st1.push(0);
	// 	st2.push(0); st2.push(1);
	// 	st3.push(0); st3.push(0); st3.push(4); st3.push(5);
	// 	st4.push(0); st4.push(1); st4.push(4);

	// 	myst1.push(0);
	// 	myst2.push(0); myst2.push(1);
	// 	myst3.push(0); myst3.push(0); myst3.push(4); myst3.push(5);
	// 	myst4.push(0); myst4.push(1); myst4.push(4);

	// 	ASSERT_EQUAL(st1 == st1, myst1 == myst1);
	// 	ASSERT_EQUAL(st1 == st2, myst1 == myst2);
	// 	ASSERT_EQUAL(st2 == st3, myst2 == myst3);
	// 	ASSERT_EQUAL(st2 == st4, myst2 == myst4);
	// 	ASSERT_EQUAL(st3 == st4, myst3 == myst4);

	// 	ASSERT_EQUAL(st1 != st1, myst1 != myst1);
	// 	ASSERT_EQUAL(st1 != st2, myst1 != myst2);
	// 	ASSERT_EQUAL(st2 != st3, myst2 != myst3);
	// 	ASSERT_EQUAL(st2 != st4, myst2 != myst4);
	// 	ASSERT_EQUAL(st3 != st4, myst3 != myst4);

	// 	ASSERT_EQUAL(st1 <= st1, myst1 <= myst1);
	// 	ASSERT_EQUAL(st1 <= st2, myst1 <= myst2);
	// 	ASSERT_EQUAL(st2 <= st3, myst2 <= myst3);
	// 	ASSERT_EQUAL(st2 <= st4, myst2 <= myst4);
	// 	ASSERT_EQUAL(st3 <= st4, myst3 <= myst4);

	// 	ASSERT_EQUAL(st1 >= st1, myst1 >= myst1);
	// 	ASSERT_EQUAL(st1 >= st2, myst1 >= myst2);
	// 	ASSERT_EQUAL(st2 >= st3, myst2 >= myst3);
	// 	ASSERT_EQUAL(st2 >= st4, myst2 >= myst4);
	// 	ASSERT_EQUAL(st3 >= st4, myst3 >= myst4);

	// 	ASSERT_EQUAL(st1 > st1, myst1 > myst1);
	// 	ASSERT_EQUAL(st1 > st2, myst1 > myst2);
	// 	ASSERT_EQUAL(st2 > st3, myst2 > myst3);
	// 	ASSERT_EQUAL(st2 > st4, myst2 > myst4);
	// 	ASSERT_EQUAL(st3 > st4, myst3 > myst4);

	// 	ASSERT_EQUAL(st1 < st1, myst1 < myst1);
	// 	ASSERT_EQUAL(st1 < st2, myst1 < myst2);
	// 	ASSERT_EQUAL(st2 < st3, myst2 < myst3);
	// 	ASSERT_EQUAL(st2 < st4, myst2 < myst4);
	// 	ASSERT_EQUAL(st3 < st4, myst3 < myst4);
	// }
}