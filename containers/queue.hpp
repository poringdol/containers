#pragma once

#include "list.hpp"
#include <queue>

#ifndef NOEXCEPT
	#if __cplusplus >= 201103L
		#define NOEXCEPT noexcept
	#else
		#define NOEXCEPT throw()
	#endif
#endif

namespace ft {
/********************************** Queue class ***************************************/

    template<class T, class Container = ft::list<T> >
	class queue {

	protected:

		Container cont;

	public:

		typedef typename Container::value_type	value_type;
		typedef typename Container::size_type	size_type;
		typedef			 Container				container_type;

	// queue constructor ----------------------------------------------------------

		explicit
		queue (const container_type& ctnr = container_type()): cont(ctnr) {}

	// Vector methods -------------------------------------------------------------

		bool
		empty () const						{ return cont.empty(); }

		size_type
		size () const						{ return cont.size(); }

		value_type&
		front ()							{ return cont.front(); }
		
		const value_type& 
		front () const						{ return cont.front(); }

		value_type&
		back ()								{ return cont.back(); }
		
		const value_type& 
		back () const						{ return cont.back(); }

		void
		pop ()								{ cont.pop_front(); }

		void
		push (const value_type& val)		{ cont.push_back(val); }

	// Non-member operators ---------------------------------------------------------------

		  template<typename _T, typename _Container>
		friend bool 
		operator== (const ft::queue<_T, _Container>&, const ft::queue<_T, _Container>&);

		  template<typename _T, typename _Container>
		friend bool
		operator< (const ft::queue<_T, _Container>&, const ft::queue<_T, _Container>&);

	};

/************************************ end of queue class ***********************************/

// Friend functions definitions -------------------------------------------------


	  template <typename T, typename Container>
	inline bool 
	operator== (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) {
		return lhs.cont == rhs.cont;
	}

	  template<typename T, typename Container>
	inline bool
	operator!= (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) {
		return !(lhs == rhs);
	}

	  template<typename T, typename Container>
	inline bool
	operator<  (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) {
		return lhs.cont < rhs.cont;
	}

	  template<typename T, typename Container>
	inline bool
	operator<= (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) {
		return !(rhs < lhs);
	}

	  template<typename T, typename Container>
	inline bool
	operator>  (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) {
		return rhs < lhs;
	}
	  template<typename T, typename Container>
	inline bool
	operator>= (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) {
		return !(lhs < rhs);
	}
}
