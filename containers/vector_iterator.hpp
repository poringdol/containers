#pragma once

#include <iterator>

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

		vector_iterator() throw() : ptr(NULL) {}
		vector_iterator(pointer new_ptr) throw() : ptr(new_ptr) {}

		  template<typename Iterator>
		iterator
		operator= (const Iterator& x)			{ return iterator(x.ptr); }

		reference
		operator*() const throw()				{ return *ptr; }

		pointer
		operator->() const throw()				{ return ptr; }

		iterator
		operator++ () throw() 					{ ++ptr; return *this; }

		iterator
		operator++ (int) throw()				{ return iterator(ptr++); }

		iterator
		operator-- () throw()					{ --ptr; return *this; }

		iterator
		operator-- (int) throw() 				{ return iterator(ptr--); }

		reference
		operator[] (int n) const throw()		{ return ptr[n]; }
		
		iterator
		operator+= (int n) throw()				{ ptr += n; return *this; }
		
		iterator
		operator+ (int n) throw()				{ return iterator(ptr + n); }
		
		iterator
		operator-= (int n) throw()				{ ptr -= n; return *this; }

		iterator
		operator- (int n) throw()				{ return iterator(ptr - n); }
		
		T*
		base()		 throw()					{ return ptr; }

		const T*
		base() const throw()					{ return ptr; }
	
		bool
		operator== (const iterator& x) throw() { return ptr == x.ptr; }

		bool
		operator!= (const iterator& x) throw() { return ptr != x.ptr; }
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

		vector_reverse_iterator() throw() : base_iterator() {}
		vector_reverse_iterator(pointer new_ptr) throw() : base_iterator(new_ptr) {}

		  template<typename Iterator>
		reverse_iterator
		operator= (Iterator& x)					{ return reverse_iterator(x.ptr); }

		reverse_iterator
		operator++ () throw() 					{ --(this->ptr); return *this; }

		reverse_iterator
		operator++ (int) throw()				{ return reverse_iterator(this->ptr--); }

		reverse_iterator
		operator-- () throw()					{ ++(this->ptr); return *this; }

		reverse_iterator
		operator-- (int) throw() 				{ return reverse_iterator(this->ptr++); }

		reverse_iterator
		operator+= (int n) throw()				{ this->ptr -= n; return *this; }
		
		reverse_iterator
		operator+ (int n) throw()				{ return reverse_iterator(this->ptr - n); }
		
		reverse_iterator
		operator-= (int n) throw()				{ this->ptr += n; return *this; }

		reverse_iterator
		operator- (int n) throw()				{ return reverse_iterator(this->ptr + n); }
		
	};
// ============================================================================

// Non-member relations for vector iterator
	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator==(const vector_iterator<IteratorL>& lhs,
				const vector_iterator<IteratorR>& rhs) throw()
	{ return lhs.base() == rhs.base(); }
	
	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator!=(const vector_iterator<IteratorL>& lhs,
				const vector_iterator<IteratorR>& rhs) throw()
	{ return lhs.base() != rhs.base(); }

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator<(const vector_iterator<IteratorL>& lhs,
				const vector_iterator<IteratorR>& rhs) throw()
	{ return lhs.base() < rhs.base(); }

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator>(const vector_iterator<IteratorL>& lhs,
				const vector_iterator<IteratorR>& rhs) throw()
	{ return lhs.base() > rhs.base(); }

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator<=(const vector_iterator<IteratorL>& lhs,
				const vector_iterator<IteratorR>& rhs) throw()
	{ return lhs.base() <= rhs.base(); }

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator>=(const vector_iterator<IteratorL>& lhs,
				const vector_iterator<IteratorR>& rhs) throw()
	{ return lhs.base() >= rhs.base(); }

	  template<typename Iterator>
	Iterator
	operator-(const vector_iterator<Iterator>& lhs,
			const vector_iterator<Iterator>& rhs) throw()
	{ return lhs.base() - rhs.base(); }

	  template<typename Iterator>
	Iterator
	operator+(Iterator n, const vector_iterator<Iterator>& i) throw()
	{ return vector_iterator<Iterator>(i.base() + n); }

// Non-member relations for reverse vector iterator

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator<(const vector_reverse_iterator<IteratorL>& lhs,
				const vector_reverse_iterator<IteratorR>& rhs) throw()
	{ return lhs.base() > rhs.base(); }

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator>(const vector_reverse_iterator<IteratorL>& lhs,
				const vector_reverse_iterator<IteratorR>& rhs) throw()
	{ return lhs.base() < rhs.base(); }

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator<=(const vector_reverse_iterator<IteratorL>& lhs,
				const vector_reverse_iterator<IteratorR>& rhs) throw()
	{ return lhs.base() >= rhs.base(); }

	  template<typename IteratorL, typename IteratorR>
	inline bool
	operator>=(const vector_reverse_iterator<IteratorL>& lhs,
				const vector_reverse_iterator<IteratorR>& rhs) throw()
	{ return lhs.base() <= rhs.base(); }

	  template<typename Iterator>
	Iterator
	operator-(const vector_reverse_iterator<Iterator>& lhs,
			const vector_reverse_iterator<Iterator>& rhs) throw()
	{ return rhs.base() - lhs.base(); }

	  template<typename Iterator>
	Iterator
	operator+(Iterator n, const vector_reverse_iterator<Iterator>& i) throw()
	{ return vector_reverse_iterator<Iterator>(i.base() - n); }
}