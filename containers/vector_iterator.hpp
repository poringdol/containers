#pragma once

#include <iterator>
#include "list.hpp"

#ifndef NOEXCEPT
	#if __cplusplus >= 201103L
		#define NOEXCEPT noexcept
	#else
		#define NOEXCEPT throw()
	#endif
#endif

namespace ft {
	
// Iterator class -------------------------------------------------------------

	  template<typename T>
	struct vector_iterator {

	protected:

		T* ptr;

	public:

		typedef vector_iterator		iterator;
		typedef size_t				size_type;
		typedef T					value_type;
		typedef T*					pointer;
		typedef T&					reference;


		vector_iterator() NOEXCEPT : ptr(NULL) {}
		vector_iterator(pointer new_ptr) NOEXCEPT : ptr(new_ptr) {}

		  template<typename Iterator>
		iterator
		operator= (const Iterator& x)			{ return iterator(x.ptr); }

		reference
		operator*() const NOEXCEPT				{ return *ptr; }

		pointer
		operator->() const NOEXCEPT				{ return ptr; }

		iterator
		operator++ () NOEXCEPT 					{ ++ptr; return *this; }

		iterator
		operator++ (int) NOEXCEPT				{ return iterator(ptr++); }

		iterator
		operator-- () NOEXCEPT					{ --ptr; return *this; }

		iterator
		operator-- (int) NOEXCEPT 				{ return iterator(ptr--); }

		reference
		operator[] (int n) const NOEXCEPT		{ return ptr[n]; }
		
		iterator
		operator+= (int n) NOEXCEPT				{ ptr += n; return *this; }
		
		iterator
		operator+ (int n) NOEXCEPT				{ return iterator(ptr + n); }
		
		iterator
		operator-= (int n) NOEXCEPT				{ ptr -= n; return *this; }

		iterator
		operator- (int n) NOEXCEPT				{ return iterator(ptr - n); }
		
		T*
		base()		 NOEXCEPT					{ return ptr; }

		const T*
		base() const NOEXCEPT					{ return ptr; }
	
		bool
		operator== (const iterator& x) NOEXCEPT { return ptr == x.ptr; }

		bool
		operator!= (const iterator& x) NOEXCEPT { return ptr != x.ptr; }
	};
// ============================================================================

// Reverse iterator class -----------------------------------------------------

	  template<typename T>
	struct vector_reverse_iterator : vector_iterator<T> {

		typedef vector_reverse_iterator		reverse_iterator;
		typedef size_t						size_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef const T*					const_pointer;
		typedef T&							reference;
		typedef const T&					const_reference;
		typedef vector_iterator<T>const		base_iterator;

		vector_reverse_iterator() NOEXCEPT : base_iterator() {}
		vector_reverse_iterator(pointer new_ptr) NOEXCEPT : base_iterator(new_ptr) {}

		  template<typename Iterator>
		reverse_iterator
		operator= (Iterator& x)					{ return reverse_iterator(x.ptr); }

		reverse_iterator
		operator++ () NOEXCEPT 					{ --(this->ptr); return *this; }

		reverse_iterator
		operator++ (int) NOEXCEPT				{ return reverse_iterator(this->ptr--); }

		reverse_iterator
		operator-- () NOEXCEPT					{ ++(this->ptr); return *this; }

		reverse_iterator
		operator-- (int) NOEXCEPT 				{ return reverse_iterator(this->ptr++); }

		reverse_iterator
		operator+= (int n) NOEXCEPT				{ this->ptr -= n; return *this; }
		
		reverse_iterator
		operator+ (int n) NOEXCEPT				{ return reverse_iterator(this->ptr - n); }
		
		reverse_iterator
		operator-= (int n) NOEXCEPT				{ this->ptr += n; return *this; }

		reverse_iterator
		operator- (int n) NOEXCEPT				{ return reverse_iterator(this->ptr + n); }
		
	};
// ============================================================================

// Non-member relations for vector iterator
	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator==(const vector_iterator<IteratorL>& lhs,
				const vector_iterator<IteratorR>& rhs) NOEXCEPT
	{ return lhs.base() == rhs.base(); }
	
	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator!=(const vector_iterator<IteratorL>& lhs,
				const vector_iterator<IteratorR>& rhs) NOEXCEPT
	{ return lhs.base() != rhs.base(); }

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator<(const vector_iterator<IteratorL>& lhs,
				const vector_iterator<IteratorR>& rhs) NOEXCEPT
	{ return lhs.base() < rhs.base(); }

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator>(const vector_iterator<IteratorL>& lhs,
				const vector_iterator<IteratorR>& rhs) NOEXCEPT
	{ return lhs.base() > rhs.base(); }

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator<=(const vector_iterator<IteratorL>& lhs,
				const vector_iterator<IteratorR>& rhs) NOEXCEPT
	{ return lhs.base() <= rhs.base(); }

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator>=(const vector_iterator<IteratorL>& lhs,
				const vector_iterator<IteratorR>& rhs) NOEXCEPT
	{ return lhs.base() >= rhs.base(); }

	  template<typename Iterator>
	Iterator
	operator-(const vector_iterator<Iterator>& lhs,
			const vector_iterator<Iterator>& rhs) NOEXCEPT
	{ return lhs.base() - rhs.base(); }

	  template<typename Iterator>
	Iterator
	operator+(Iterator n, const vector_iterator<Iterator>& i) NOEXCEPT
	{ return vector_iterator<Iterator>(i.base() + n); }

// Non-member relations for reverse vector iterator

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator<(const vector_reverse_iterator<IteratorL>& lhs,
				const vector_reverse_iterator<IteratorR>& rhs) NOEXCEPT
	{ return lhs.base() > rhs.base(); }

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator>(const vector_reverse_iterator<IteratorL>& lhs,
				const vector_reverse_iterator<IteratorR>& rhs) NOEXCEPT
	{ return lhs.base() < rhs.base(); }

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator<=(const vector_reverse_iterator<IteratorL>& lhs,
				const vector_reverse_iterator<IteratorR>& rhs) NOEXCEPT
	{ return lhs.base() >= rhs.base(); }

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator>=(const vector_reverse_iterator<IteratorL>& lhs,
				const vector_reverse_iterator<IteratorR>& rhs) NOEXCEPT
	{ return lhs.base() <= rhs.base(); }

	  template<typename Iterator>
	Iterator
	operator-(const vector_reverse_iterator<Iterator>& lhs,
			const vector_reverse_iterator<Iterator>& rhs) NOEXCEPT
	{ return rhs.base() - lhs.base(); }

	  template<typename Iterator>
	Iterator
	operator+(Iterator n, const vector_reverse_iterator<Iterator>& i) NOEXCEPT
	{ return vector_reverse_iterator<Iterator>(i.base() - n); }
}