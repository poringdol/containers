#include <deque>
#include <iostream>

void print(std::deque<int> g_dq) {
	for (int i : g_dq)
		std::cout << i << ", ";
	std::cout << std::endl;
}

int main() {

	std::deque<int> g_dq(10, 50);
	print(g_dq);

	g_dq.resize(8);
	print(g_dq);

	g_dq.resize(6, 4);
	print(g_dq);

	g_dq.resize(8, 0);
	print(g_dq);
}