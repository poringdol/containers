#pragma once

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

	protected:

		Container cont;

	public:

		typedef typename Container::value_type	value_type;
		typedef typename Container::size_type	size_type;
		typedef			 Container				container_type;

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
		top ()								{ return cont.back(); }
		
		const value_type& 
		top () const						{ return cont.back(); }
		
		void
		pop ()								{ cont.pop_back(); }

		void
		push (const value_type& val)		{ cont.push_back(val); }

		template<typename _T, typename _Container>
		bool
		qwe(const ft::stack<_T, _Container>& rhs) {
			return cont == rhs.cont;
		}

	// Non-member operators ---------------------------------------------------------------

		template<typename _T, typename _Container>
		friend bool 
		operator== (const ft::stack<_T, _Container>&, const ft::stack<_T, _Container>&);

		template<typename _T, typename _Container>
		friend bool
		operator<  (const ft::stack<_T, _Container>&, const ft::stack<_T, _Container>&);

	};
// ==============================================================================

/************************************ end of list class ***********************************/

// Friend functions definitions -------------------------------------------------


	template <typename T, typename Container>
	inline bool 
	operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return lhs.cont == rhs.cont;
	}

	template<typename T, typename Container>
	inline bool
	operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return !(lhs == rhs);
	}

	template<typename T, typename Container>
	inline bool
	operator<  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return lhs.cont < rhs.cont;
	}

	template<typename T, typename Container>
	inline bool
	operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return !(rhs < lhs);
	}

	template<typename T, typename Container>
	inline bool
	operator>  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return rhs < lhs;
	}
	template<typename T, typename Container>
	inline bool
	operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return !(lhs < rhs);
	}
}
