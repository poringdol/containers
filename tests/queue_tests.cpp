#include <queue>
#include <deque>
#include <iostream>
#include <sstream>
#include "tests.hpp"
#include "test_runner.h"
#include "queue.hpp"

/*********************************************************************/
/*								TESTS								 */
/*********************************************************************/
namespace ft_queue
{
	void constructorDefault_test() {

		std::queue<int, std::list<int> > qu1;
		ft::queue<int, std::list<int> > myqu1;

		std::queue<int, std::deque<int> > qu2;
		ft::queue<int, std::deque<int> > myqu2;

		std::queue<int, ft::list<int> > qu4;
		ft::queue<int, ft::list<int> > myqu4;
	}

	void size_test() {

		std::queue<int, std::list<int> > qu1;
		ft::queue<int, std::list<int> > myqu1;
		ASSERT_EQUAL(qu1.size(), myqu1.size());

		std::queue<int, std::deque<int> > qu2;
		ft::queue<int, std::deque<int> > myqu2;
		ASSERT_EQUAL(qu2.size(), myqu2.size());

		std::queue<int, ft::list<int> > qu4;
		ft::queue<int, ft::list<int> > myqu4;
		ASSERT_EQUAL(qu4.size(), myqu4.size());
	}

	void empty_test() {

		std::queue<int, std::list<int> > myqu1;
		ASSERT_EQUAL(true, myqu1.empty());
		myqu1.push(1);
		ASSERT_EQUAL(false, myqu1.empty());
		myqu1.pop();
		ASSERT_EQUAL(true, myqu1.empty());

		std::queue<int, ft::list<int> > myqu2;
		ASSERT_EQUAL(true, myqu2.empty());
		myqu2.push(1);
		ASSERT_EQUAL(false, myqu2.empty());
		myqu2.pop();
		ASSERT_EQUAL(true, myqu2.empty());

		std::queue<int, std::deque<int> > myqu3;
		ASSERT_EQUAL(true, myqu3.empty());
		myqu3.push(1);
		ASSERT_EQUAL(false, myqu3.empty());
		myqu3.pop();
		ASSERT_EQUAL(true, myqu3.empty());
	}

	void push_test() {
		std::queue<int, std::list<int> > qu1;
		ft::queue<int, std::list<int> > myqu1;

		qu1.push(21);
		myqu1.push(21);
		qu1.push(3);
		myqu1.push(3);
		qu1.push(11);
		myqu1.push(11);
		ASSERT_EQUAL(qu1.size(), myqu1.size());
		ASSERT_EQUAL(queueToString(qu1), queueToString(myqu1));

		std::queue<int, ft::list<int> > qu2;
		ft::queue<int, ft::list<int> > myqu2;

		qu2.push(17);
		myqu2.push(17);
		qu2.push(7);
		myqu2.push(7);
		qu2.push(12);
		myqu2.push(12);
		ASSERT_EQUAL(queueToString(qu2), queueToString(myqu2));
		ASSERT_EQUAL(qu2.size(), myqu2.size());
		ASSERT_EQUAL(qu2.empty(), myqu2.empty());

		std::queue<int, std::deque<int> > qu3;
		ft::queue<int, std::deque<int> > myqu3;
		qu3.push(37);
		myqu3.push(37);
		qu3.push(14);
		myqu3.push(14);
		qu3.push(13);
		myqu3.push(13);
		ASSERT_EQUAL(queueToString(qu3), queueToString(myqu3));
		ASSERT_EQUAL(qu3.size(), myqu3.size());
		ASSERT_EQUAL(qu3.empty(), myqu3.empty());

	}

	void front_test() {
		
		{
			std::queue<int, std::list<int> > qu1;
			ft::queue<int, std::list<int> > myqu1;
			qu1.push(10);
			myqu1.push(10);
			qu1.push(110);
			myqu1.push(110);
			ASSERT_EQUAL(qu1.front(), myqu1.front());
			ASSERT_EQUAL(queueToString(qu1), queueToString(myqu1));
		}
		
		{
			std::queue<int, ft::list<int> > qu1;
			ft::queue<int, ft::list<int> > myqu1;
			qu1.push(11);
			myqu1.push(11);
			qu1.push(211);
			myqu1.push(211);
			ASSERT_EQUAL(qu1.front(), myqu1.front());
			ASSERT_EQUAL(queueToString(qu1), queueToString(myqu1));
		}
		
		{
			std::queue<int, std::deque<int> > qu1;
			ft::queue<int, std::deque<int> > myqu1;
			qu1.push(12);
			myqu1.push(12);
			qu1.push(312);
			myqu1.push(312);
			ASSERT_EQUAL(qu1.front(), myqu1.front());
		}
	}

	void back_test() {
		
		{
			std::queue<int, std::list<int> > qu1;
			ft::queue<int, std::list<int> > myqu1;
			qu1.push(10);
			myqu1.push(10);
			qu1.push(110);
			myqu1.push(110);
			ASSERT_EQUAL(qu1.back(), myqu1.back());
			ASSERT_EQUAL(queueToString(qu1), queueToString(myqu1));
		}
		
		{
			std::queue<int, ft::list<int> > qu1;
			ft::queue<int, ft::list<int> > myqu1;
			qu1.push(11);
			myqu1.push(11);
			qu1.push(211);
			myqu1.push(211);
			ASSERT_EQUAL(qu1.back(), myqu1.back());
			ASSERT_EQUAL(queueToString(qu1), queueToString(myqu1));
		}
		
		{
			std::queue<int, std::deque<int> > qu1;
			ft::queue<int, std::deque<int> > myqu1;
			qu1.push(12);
			myqu1.push(12);
			qu1.push(312);
			myqu1.push(312);
			ASSERT_EQUAL(qu1.back(), myqu1.back());
		}
	}

	void pop_test() {
		{
			std::queue<int, std::list<int> > qu1;
			ft::queue<int, std::list<int> > myqu1;
			qu1.push(17);
			myqu1.push(17);
			qu1.push(7);
			myqu1.push(7);
			qu1.pop();
			myqu1.pop();
			qu1.pop();
			myqu1.pop();

			ASSERT_EQUAL(qu1.size(), myqu1.size());
			ASSERT_EQUAL(qu1.size(), myqu1.size());
		}

		{
			std::queue<int, ft::list<int> > qu1;
			ft::queue<int, ft::list<int> > myqu1;
			qu1.push(17);
			myqu1.push(17);
			qu1.push(7);
			myqu1.push(7);
			qu1.pop();
			myqu1.pop();
			qu1.pop();
			myqu1.pop();

			ASSERT_EQUAL(qu1.size(), myqu1.size());
			ASSERT_EQUAL(qu1.size(), myqu1.size());
		}

		{
			std::queue<int, std::deque<int> > qu1;
			ft::queue<int, std::deque<int> > myqu1;
			qu1.push(17);
			myqu1.push(17);
			qu1.push(7);
			myqu1.push(7);
			qu1.pop();
			myqu1.pop();
			qu1.pop();
			myqu1.pop();

			ASSERT_EQUAL(qu1.size(), myqu1.size());
			ASSERT_EQUAL(qu1.size(), myqu1.size());
		}
	}

	void operators_test() {
		std::queue<int> qu1, qu2, qu3, qu4;
		ft::queue<int> myqu1, myqu2, myqu3, myqu4;

		qu1.push(0);
		qu2.push(0); qu2.push(1);
		qu3.push(0); qu3.push(0); qu3.push(4); qu3.push(5);
		qu4.push(0); qu4.push(1); qu4.push(4);

		myqu1.push(0);
		myqu2.push(0); myqu2.push(1);
		myqu3.push(0); myqu3.push(0); myqu3.push(4); myqu3.push(5);
		myqu4.push(0); myqu4.push(1); myqu4.push(4);

		ASSERT_EQUAL(qu1 == qu1, myqu1 == myqu1);
		ASSERT_EQUAL(qu1 == qu2, myqu1 == myqu2);
		ASSERT_EQUAL(qu2 == qu3, myqu2 == myqu3);
		ASSERT_EQUAL(qu2 == qu4, myqu2 == myqu4);
		ASSERT_EQUAL(qu3 == qu4, myqu3 == myqu4);

		ASSERT_EQUAL(qu1 != qu1, myqu1 != myqu1);
		ASSERT_EQUAL(qu1 != qu2, myqu1 != myqu2);
		ASSERT_EQUAL(qu2 != qu3, myqu2 != myqu3);
		ASSERT_EQUAL(qu2 != qu4, myqu2 != myqu4);
		ASSERT_EQUAL(qu3 != qu4, myqu3 != myqu4);

		ASSERT_EQUAL(qu1 <= qu1, myqu1 <= myqu1);
		ASSERT_EQUAL(qu1 <= qu2, myqu1 <= myqu2);
		ASSERT_EQUAL(qu2 <= qu3, myqu2 <= myqu3);
		ASSERT_EQUAL(qu2 <= qu4, myqu2 <= myqu4);
		ASSERT_EQUAL(qu3 <= qu4, myqu3 <= myqu4);

		ASSERT_EQUAL(qu1 >= qu1, myqu1 >= myqu1);
		ASSERT_EQUAL(qu1 >= qu2, myqu1 >= myqu2);
		ASSERT_EQUAL(qu2 >= qu3, myqu2 >= myqu3);
		ASSERT_EQUAL(qu2 >= qu4, myqu2 >= myqu4);
		ASSERT_EQUAL(qu3 >= qu4, myqu3 >= myqu4);

		ASSERT_EQUAL(qu1 > qu1, myqu1 > myqu1);
		ASSERT_EQUAL(qu1 > qu2, myqu1 > myqu2);
		ASSERT_EQUAL(qu2 > qu3, myqu2 > myqu3);
		ASSERT_EQUAL(qu2 > qu4, myqu2 > myqu4);
		ASSERT_EQUAL(qu3 > qu4, myqu3 > myqu4);

		ASSERT_EQUAL(qu1 < qu1, myqu1 < myqu1);
		ASSERT_EQUAL(qu1 < qu2, myqu1 < myqu2);
		ASSERT_EQUAL(qu2 < qu3, myqu2 < myqu3);
		ASSERT_EQUAL(qu2 < qu4, myqu2 < myqu4);
		ASSERT_EQUAL(qu3 < qu4, myqu3 < myqu4);
	}
}