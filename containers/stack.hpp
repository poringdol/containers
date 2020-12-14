#pragma once

#include <stack>
#include "list.hpp"

#ifndef NOEXCEPT
	#if __cplusplus >= 201103L
		#define NOEXCEPT throw()
	#else
		#define NOEXCEPT noexcept
	#endif
#endif

namespace ft {
/********************************** Stack container ***************************************/

 
  template<class T, class Container = ft::list<T> >
	class stack {

	private:


	public:
		Container cont;

		typedef T						value_type;
		typedef Container				container_type;
		typedef size_t					size_type;

	// Stack constructor ----------------------------------------------------------

		explicit
		stack (const container_type& ctnr = container_type()): cont(ctnr) {}

	// Stack destructor -----------------------------------------------------------

		~stack () {}

	// Vector methods -------------------------------------------------------------

		bool
		empty () const						{ return cont.empty(); }

		size_type
		size () const						{ return cont.size(); }

		value_type&
		top ()								{ return *(cont.back()); }
		
		const value_type& 
		top () const						{ return *(cont.back()); }
		
		void
		pop ()								{ cont.pop_back(); }

		void
		push (const value_type& val)		{ cont.push_back(val); }

	// Out of class operators ---------------------------------------------------------------

		template<class _T, class _Container>
		friend bool 
		operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs);

		template<class _T, class _Container>
		friend bool
		operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs);

		template<class _T, class _Container>
		friend bool
		operator<  (const stack<T, Container>& lhs, const stack<T, Container>& rhs);

		template<class _T, class _Container>
		friend bool
		operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs);

		template<class _T, class _Container>
		friend bool
		operator>  (const stack<T, Container>& lhs, const stack<T, Container>& rhs);

		template<class _T, class _Container>
		friend bool
		operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs);

	};
// ==============================================================================

/************************************ end of list class ***********************************/

// Friend functions definitions -------------------------------------------------


	template <class T, class Container>
	bool 
	operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.cont == rhs.cont;
	}

	template<class T, class Container>
	bool
	operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.cont != rhs.cont;
	}

	template<class T, class Container>
	bool
	operator<  (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.cont < rhs.cont;
	}

	template<class T, class Container>
	bool
	operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.cont <= rhs.cont;
	}

	template<class T, class Container>
	bool
	operator>  (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.cont > rhs.cont;
	}
	template<class T, class Container>
	bool
	operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.cont >= rhs.cont;
	}
}
