#pragma once

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <iomanip>

#define BW "\033[0;0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define PURPLE "\033[0;35m"

using namespace std;

  template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
//   for (const auto& x : s) {
	for (typename vector<T>::iterator it = s.begin(); it != s.end(); ++it) {
		if (!first) {
			os << ", ";
		}
		first = false;
		// os << x;
		os << *it;
	}
	return os << "}";
}

  template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	//   for (const auto& x : s) {
	for (typename vector<T>::iterator it = s.begin(); it != s.end(); ++it) {
		if (!first) {
			os << ", ";
		}
		first = false;
		// os << x;
		os << *it;
	}
	return os << "}";
}

  template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
//   for (const auto& kv : m) {
	for (typename map<K, V>::iterator it = m.begin(); it != m.end(); ++it) {
		if (!first) {
			os << ", ";
		}
		first = false;
		// os << kv.first << ": " << kv.second;
		os << m.first << ": " << m.second;
  	}
  	return os << "}";
}

  template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = string()) {
  	if (!(t == u)) {
		ostringstream os;
		os << "Assertion failed: " << "\n\t" << t << " != " << "\n\t" << u << "\n";
		if (!hint.empty()) {
			os << "\thint: " << hint;
		}
		std::cout << os.str() << endl;
   		// throw runtime_error(os.str());
 	}
}

inline void Assert(bool b, const string& hint) {
  	AssertEqual(b, true, hint);
}

inline void print_spaces(const std::string& name) {
	for (size_t i = name.size(); i < 24; i++) 
		std::cerr << "-";
}

class TestRunner {
public:
	  template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
    	try {
			func();
			cerr << YELLOW << test_name;
			print_spaces(test_name);
			cerr << GREEN << " OK" << BW << endl;
   		 } catch (exception& e) {
			++fail_count;
			cerr << test_name << RED << " fail: " << BW << e.what() << endl;
		} catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
  	}
	TestRunner(): fail_count(0) {}
	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
		//   exit(1);
    }
  }

private:
 	int fail_count;
};

#define ASSERT_EQUAL(x, y) {            \
	ostringstream os;                     \
	os << #x << " != " << #y << ", "      \
    	<< __FILE__ << ":" << __LINE__;     \
	AssertEqual(x, y, os.str());          \
}

#define ASSERT(x) {                     \
	ostringstream os;                     \
  	os << #x << " is false, "             \
    	<< __FILE__ << ":" << __LINE__;     \
  	Assert(x, os.str());                  \
}

#define RUN_TEST(tr, func) \
  	tr.RunTest(func, #func)
