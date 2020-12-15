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
	void constructorDefault_test() {

		std::stack<int, std::list<int> > st1;
		ft::stack<int, std::list<int> > myst1;

		std::stack<int, std::vector<int> > st2;
		ft::stack<int, std::vector<int> > myst2;

		std::stack<int, ft::list<int> > st4;
		ft::stack<int, ft::list<int> > myst4;

		std::stack<int, ft::vector<int> > st3;
		ft::stack<int, ft::vector<int> > myst3;
	}

	void size_test() {

		std::stack<int, std::list<int> > st1;
		ft::stack<int, std::list<int> > myst1;
		ASSERT_EQUAL(st1.size(), myst1.size());

		std::stack<int, std::vector<int> > st2;
		ft::stack<int, std::vector<int> > myst2;
		ASSERT_EQUAL(st2.size(), myst2.size());

		std::stack<int, ft::list<int> > st4;
		ft::stack<int, ft::list<int> > myst4;
		ASSERT_EQUAL(st4.size(), myst4.size());

		std::stack<int, ft::vector<int> > st3;
		ft::stack<int, ft::vector<int> > myst3;
		ASSERT_EQUAL(st3.size(), myst3.size());
	}

	void empty_test() {

		std::stack<int, std::list<int> > myst1;
		ASSERT_EQUAL(true, myst1.empty());
		myst1.push(1);
		ASSERT_EQUAL(false, myst1.empty());
		myst1.pop();
		ASSERT_EQUAL(true, myst1.empty());

		std::stack<int, ft::list<int> > myst2;
		ASSERT_EQUAL(true, myst2.empty());
		myst2.push(1);
		ASSERT_EQUAL(false, myst2.empty());
		myst2.pop();
		ASSERT_EQUAL(true, myst2.empty());

		std::stack<int, std::vector<int> > myst3;
		ASSERT_EQUAL(true, myst3.empty());
		myst3.push(1);
		ASSERT_EQUAL(false, myst3.empty());
		myst3.pop();
		ASSERT_EQUAL(true, myst3.empty());

		std::stack<int, ft::vector<int> > myst4;
		ASSERT_EQUAL(true, myst4.empty());
		myst4.push(1);
		ASSERT_EQUAL(false, myst4.empty());
		myst4.pop();
		ASSERT_EQUAL(true, myst4.empty());
	}

	void push_test() {
		std::stack<int, std::list<int> > st1;
		ft::stack<int, std::list<int> > myst1;

		st1.push(21);
		myst1.push(21);
		st1.push(3);
		myst1.push(3);
		st1.push(11);
		myst1.push(11);
		ASSERT_EQUAL(stackToString(st1), stackToString(myst1));

		std::stack<int, ft::list<int> > st2;
		ft::stack<int, ft::list<int> > myst2;

		st2.push(17);
		myst2.push(17);
		st2.push(7);
		myst2.push(7);
		st2.push(12);
		myst2.push(12);
		ASSERT_EQUAL(stackToString(st2), stackToString(myst2));
		ASSERT_EQUAL(st2.empty(), myst2.empty());

		std::stack<int, std::vector<int> > st3;
		ft::stack<int, std::vector<int> > myst3;
		st3.push(37);
		myst3.push(37);
		st3.push(14);
		myst3.push(14);
		st3.push(13);
		myst3.push(13);
		ASSERT_EQUAL(stackToString(st3), stackToString(myst3));
		ASSERT_EQUAL(st3.empty(), myst3.empty());

		std::stack<int, ft::vector<int> > st4;
		ft::stack<int, ft::vector<int> > myst4;
		st4.push(45);
		myst4.push(45);
		st4.push(71);
		myst4.push(71);
		st4.push(14);
		myst4.push(14);
		ASSERT_EQUAL(stackToString(st4), stackToString(myst4));
		ASSERT_EQUAL(st4.empty(), myst4.empty());
	}

	void top_test() {
		
		{
			std::stack<int, std::list<int> > st1;
			ft::stack<int, std::list<int> > myst1;
			st1.push(10);
			myst1.push(10);
			ASSERT_EQUAL(st1.top(), myst1.top());
			ASSERT_EQUAL(stackToString(st1), stackToString(myst1));
		}
		
		{
			std::stack<int, ft::list<int> > st1;
			ft::stack<int, ft::list<int> > myst1;
			st1.push(11);
			myst1.push(11);
			ASSERT_EQUAL(st1.top(), myst1.top());
			ASSERT_EQUAL(stackToString(st1), stackToString(myst1));
		}
		
		{
			std::stack<int, std::vector<int> > st1;
			ft::stack<int, std::vector<int> > myst1;
			st1.push(12);
			myst1.push(12);
			ASSERT_EQUAL(st1.top(), myst1.top());
		}
		
		{
			std::stack<int, ft::vector<int> > st1;
			ft::stack<int, ft::vector<int> > myst1;
			st1.push(13);
			myst1.push(13);
			ASSERT_EQUAL(st1.top(), myst1.top());
		}
		
	}

	void pop_test() {
		{
			std::stack<int, std::list<int> > st1;
			ft::stack<int, std::list<int> > myst1;
			st1.push(17);
			myst1.push(17);
			st1.push(7);
			myst1.push(7);
			st1.pop();
			myst1.pop();
			st1.pop();
			myst1.pop();

			ASSERT_EQUAL(st1.size(), myst1.size());
			ASSERT_EQUAL(st1.size(), myst1.size());
		}

		{
			std::stack<int, ft::list<int> > st1;
			ft::stack<int, ft::list<int> > myst1;
			st1.push(17);
			myst1.push(17);
			st1.push(7);
			myst1.push(7);
			st1.pop();
			myst1.pop();
			st1.pop();
			myst1.pop();

			ASSERT_EQUAL(st1.size(), myst1.size());
			ASSERT_EQUAL(st1.size(), myst1.size());
		}

		{
			std::stack<int, std::vector<int> > st1;
			ft::stack<int, std::vector<int> > myst1;
			st1.push(17);
			myst1.push(17);
			st1.push(7);
			myst1.push(7);
			st1.pop();
			myst1.pop();
			st1.pop();
			myst1.pop();

			ASSERT_EQUAL(st1.size(), myst1.size());
			ASSERT_EQUAL(st1.size(), myst1.size());
		}

		{
			std::stack<int, ft::vector<int> > st1;
			ft::stack<int, ft::vector<int> > myst1;
			st1.push(17);
			myst1.push(17);
			st1.push(7);
			myst1.push(7);
			st1.pop();
			myst1.pop();
			st1.pop();
			myst1.pop();

			ASSERT_EQUAL(st1.size(), myst1.size());
			ASSERT_EQUAL(st1.size(), myst1.size());
		}
	}

	void operators_test() {
		std::stack<int> st1, st2, st3, st4;
		ft::stack<int> myst1, myst2, myst3, myst4;

		st1.push(0);
		st2.push(0); st2.push(1);
		st3.push(0); st3.push(0); st3.push(4); st3.push(5);
		st4.push(0); st4.push(1); st4.push(4);

		myst1.push(0);
		myst2.push(0); myst2.push(1);
		myst3.push(0); myst3.push(0); myst3.push(4); myst3.push(5);
		myst4.push(0); myst4.push(1); myst4.push(4);

		ASSERT_EQUAL(st1 == st1, myst1 == myst1);
		ASSERT_EQUAL(st1 == st2, myst1 == myst2);
		ASSERT_EQUAL(st2 == st3, myst2 == myst3);
		ASSERT_EQUAL(st2 == st4, myst2 == myst4);
		ASSERT_EQUAL(st3 == st4, myst3 == myst4);

		ASSERT_EQUAL(st1 != st1, myst1 != myst1);
		ASSERT_EQUAL(st1 != st2, myst1 != myst2);
		ASSERT_EQUAL(st2 != st3, myst2 != myst3);
		ASSERT_EQUAL(st2 != st4, myst2 != myst4);
		ASSERT_EQUAL(st3 != st4, myst3 != myst4);

		ASSERT_EQUAL(st1 <= st1, myst1 <= myst1);
		ASSERT_EQUAL(st1 <= st2, myst1 <= myst2);
		ASSERT_EQUAL(st2 <= st3, myst2 <= myst3);
		ASSERT_EQUAL(st2 <= st4, myst2 <= myst4);
		ASSERT_EQUAL(st3 <= st4, myst3 <= myst4);

		ASSERT_EQUAL(st1 >= st1, myst1 >= myst1);
		ASSERT_EQUAL(st1 >= st2, myst1 >= myst2);
		ASSERT_EQUAL(st2 >= st3, myst2 >= myst3);
		ASSERT_EQUAL(st2 >= st4, myst2 >= myst4);
		ASSERT_EQUAL(st3 >= st4, myst3 >= myst4);

		ASSERT_EQUAL(st1 > st1, myst1 > myst1);
		ASSERT_EQUAL(st1 > st2, myst1 > myst2);
		ASSERT_EQUAL(st2 > st3, myst2 > myst3);
		ASSERT_EQUAL(st2 > st4, myst2 > myst4);
		ASSERT_EQUAL(st3 > st4, myst3 > myst4);

		ASSERT_EQUAL(st1 < st1, myst1 < myst1);
		ASSERT_EQUAL(st1 < st2, myst1 < myst2);
		ASSERT_EQUAL(st2 < st3, myst2 < myst3);
		ASSERT_EQUAL(st2 < st4, myst2 < myst4);
		ASSERT_EQUAL(st3 < st4, myst3 < myst4);
	}
}