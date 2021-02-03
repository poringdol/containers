#pragma once

#include <limits>
#include <memory>
#include <cstddef>
#include "cpp_type_traits.hpp"
#include "deque.hpp"
#include "list_iterator.hpp"


namespace ft {
/********************************** Deque class ***************************************/

	  template<typename T, typename Alloc = std::allocator<T> >
	class deque {

	private:

	// Supporting structure deque_node ---------------------------------------------

		struct _deque_node {
			T _data;
			_deque_node* _prev;
			_deque_node* _next;

			_deque_node (T new_data = T(),
					  _deque_node* new_prev = NULL,
					  _deque_node* new_next = NULL) throw()
					: _data(new_data), _prev(new_prev), _next(new_next) {}
		};
// ============================================================================

		typedef ft::list_iterator<T, _deque_node>			deque_iterator;
		typedef ft::list_reverse_iterator<T, _deque_node>	deque_reverse_iterator;

	public:

		typedef Alloc					allocator_type;
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;
		typedef T						value_type;
		typedef T*						pointer;
		typedef const T*				const_pointer;
		typedef T&						reference;
		typedef const T&				const_reference;
		typedef deque_iterator			iterator;
		typedef deque_iterator			const_iterator;
		typedef deque_reverse_iterator	reverse_iterator;
		typedef deque_reverse_iterator	const_reverse_iterator;

	private:

		size_type		_deque_size;
		_deque_node*	_head;
		Alloc			_alloc;

// Supporting functions -------------------------------------------------------

		void
		_deque_init () throw() {
			_head = new _deque_node;
			_head->_prev = _head->_next = _head;
		}

		/* 'insert' node placed to current position, 'current' moved to _next position */
		void
		_node_insert (_deque_node* current, _deque_node* insert) {
			insert->_next = current;
			insert->_prev = current->_prev;
			current->_prev = current->_prev->_next = insert;
		}

		  template<typename InputIterator>
		void
		_insert (iterator position, InputIterator first, InputIterator last, ft::false_type_my) {
			for (; first != last; ++first) {
				insert(position, *first);
			}
		}

		  template<typename T1>
		void
		_insert (iterator position, size_type n, T1 val, ft::true_type_my) {
			while (n--) {
				iterator temp = position;
				insert(temp, val);
			}
		}

		  template<typename InputIterator>
		void
		_assign (InputIterator first, InputIterator last, ft::false_type_my) {
			clear();
			while (first != last) {
				push_back(*first);
				++first;
			}
		}

		  template<typename T1>
		void
		_assign (size_type n, T1 val, ft::true_type_my) {
			clear();
			while (n--) {
				push_back(val);
			}
		}

		static bool
		_compare (T val1, T val2) { return val1 < val2; }

		void
		_cut (iterator it) {
			it.ptr->_prev->_next = it.ptr->_next;
			it.ptr->_next->_prev = it.ptr->_prev;
		}

	public:

// Deque constructors ----------------------------------------------------------

		explicit
		deque (const allocator_type& x = allocator_type())
					: _deque_size(0), _alloc(x) { _deque_init(); }

		explicit
		deque (size_type n, value_type val = value_type(), const allocator_type& x = allocator_type()): _deque_size(0), _alloc(x) {
			_deque_init();
			while (n--) { push_back(val); }
		}
		

		  template<typename InputIterator>
		deque (InputIterator first, InputIterator last, const allocator_type& x = allocator_type()): _deque_size(0), _alloc(x) {
			_deque_init();
			assign(first, last);
		}

		deque (const deque& x): _deque_size(0) { 
			_deque_init();
			*this = x;
		}

		deque&
		operator= (const deque& x) {
			clear();

			const_iterator temp = x.begin();
			while (temp != x.end()) {
				push_back(temp.ptr->_data);
				temp++;
			}
			return *this;
		}

// Deque destructor --------------------------------------------------------------

		~deque() {
			clear();
			delete _head;
		}
	
// Deque methods ---------------------------------------------------------------------

	//  Iterators -------------------------------

		iterator
		begin () throw()			{ return iterator(_head->_next); }

		const_iterator
		begin () const throw()		{ return const_iterator(_head->_next); }

		iterator
		end () throw()				{ return iterator(_head); }

		const_iterator
		end () const throw()		{ return const_iterator(_head); }

		reverse_iterator
		rbegin () throw()			{ return reverse_iterator(_head->_prev); }

		const_reverse_iterator
		rbegin () const throw() 	{ return const_reverse_iterator(_head->_prev); }

		reverse_iterator
		rend () throw()				{ return reverse_iterator(_head); }

		const_reverse_iterator
		rend () const throw()		{ return const_reverse_iterator(_head); }

	// Capacity ----------------------------

		bool
		empty () const throw()		{ return _deque_size == 0; }

		size_type
		size () const throw()		{ return _deque_size; }

		void
		resize (size_type new_size, value_type val = value_type()) {
			
			if (new_size < _deque_size) {
				iterator it = begin();
				while (new_size--)
					++it;
				erase(it, end());
			} else {
				insert(end(), new_size - _deque_size, val);
			}
		}

		size_type
		max_size () const throw()	{ return std::numeric_limits<size_type>::max() / sizeof(_deque_node); }

	// Element access -------------------------

		reference
		operator[] (size_type n) throw() {
			iterator it = begin();
			for (size_type i = 0; i < n; it++, i++) ;
			return *it;
		}

		const_reference
		operator[] (size_type n) const throw() {
			const_iterator it = begin();
			for (size_type i = 0; i < n; it++, i++) ;
			return *it;
		}

		reference
		at (size_type n) {
			if (n >= _deque_size)
				throw std::out_of_range("deque: n >= current size of deque");
			return (*this)[n];
		}

		const_reference
		at (size_type n) const {
			if (n >= _deque_size)
				throw std::out_of_range("deque: n >= current size of deque");
			return (*this)[n];
		}

		reference
		front () throw()			{ return *begin(); }

		const_reference
		front () const throw()		{ return *begin(); }

		reference
		back () throw()				{ return *(--end()); }

		const_reference
		back () const throw()		{ return *(--end()); }

	// Modifiers ------------------------------

		  template<typename InputIterator>
		void
		assign (InputIterator first, InputIterator last) {
			typedef typename ft::is_integer_my<InputIterator>::type_my _Integral;
			_assign(first, last, _Integral());
		}

		void
		assign (size_type n, const value_type& val) {
			_assign(n, val, ft::true_type_my());
		}

		void
		push_front (const value_type& data) {
			_deque_node* temp = new _deque_node(data, _head, _head->_next);
			_head->_next = _head->_next->_prev = temp;
			_deque_size++;
		}

		void
		pop_front () throw() { erase(begin()); }

		void
		push_back (const value_type& data) {

			if (!_deque_size) {
				_deque_node* temp = new _deque_node(data);
				_head->_prev = _head->_next = temp;
				temp->_prev = temp->_next = _head;
			} else {
				_deque_node* temp = new _deque_node(data, _head->_prev, _head);
				_head->_prev->_next = temp;
				_head->_prev = temp;
			}
			_deque_size++;
		}

		void
		pop_back () throw() { erase(iterator(_head->_prev)); }

		iterator
		insert (iterator position, const value_type& data) {
			if (position == begin()) {
				push_front(data);
				return begin();
			}

			_deque_node* temp = new _deque_node(data);
			_node_insert(position.ptr, temp);
			_deque_size++;
			return iterator(temp);
		}

		void
		insert (iterator position, size_type n, const value_type& val) {
			_insert(position, n, val, ft::true_type_my());
		}
		
		  template<typename InputIterator>
		void
		insert (iterator position, InputIterator first, InputIterator last) {
			typedef typename ft::is_integer_my<InputIterator>::type_my _Integral;
			_insert(position, first, last, _Integral());
		}

		iterator
		erase (iterator position) {
			if (position != end()) {
				_cut(position);
				iterator temp = position++;
				if (temp == begin())
					_head->_next = temp.ptr;
				delete temp.ptr;
				_deque_size -= _deque_size ? 1 : 0;
			}
			return position;
		}

		iterator
		erase (iterator first, iterator last) {
			while (first != last) {
				first = erase(first);
			}
			return last;
		}

		void
		swap (deque& x) {
			_deque_node* temp = _head;
			_head = x._head;
			x._head = temp;

			size_type size = _deque_size;
			_deque_size = x._deque_size;
			x._deque_size = size;
		}

		void
		clear () throw() {
			_deque_node* temp;
			while (_deque_size) {
				temp = _head->_next;
				delete _head;
				_head = temp;
				_deque_size--;
			}
			_head->_prev = _head->_next = _head;
		}

// Friend functions -----------------------------------------------------------
		  template<typename _T, typename _Alloc>
		friend bool
		operator== (const deque<_T, _Alloc>&, const deque<_T, _Alloc>&);

		  template<typename _T, typename _Alloc>
		friend  bool
		operator<  (const deque<_T, _Alloc>&, const deque<_T, _Alloc>&);

		  template<typename _T, typename _Alloc>
		friend void
		swap (deque<_T, _Alloc>&, deque<_T, _Alloc>&);

	};

/************************************ end of deque class ***********************************/

// Friend functions definitions -----------------------------------------------

	  template<typename T, typename Alloc>
	inline bool
	operator== (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs) {
		
		if (lhs.size() != rhs.size()) return false;
		
		typename ft::deque<T>::iterator first1 = lhs.begin();
		typename ft::deque<T>::iterator first2 = rhs.begin();
		
		while (first1 != lhs.end()) {
			if (*first1 != *first2)
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	  template<typename T, typename Alloc>
	inline bool
	operator!= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	  template<typename T, typename Alloc>
	inline bool
	operator<  (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs) {

		typename ft::deque<T>::iterator first1 = lhs.begin();
		typename ft::deque<T>::iterator first2 = rhs.begin();
		
		while (first1 != lhs.end() && first2 != rhs.end()) {
			if (*first1 < *first2)
				return true;
			if (*first1 > *first2)
				return false;
			++first1;
			++first2;
		}
		if (lhs.size() > rhs.size() ||
			(lhs.size() == rhs.size() && *(--first1) >= *(--first2)))
			return false;
		return true;
	}

	  template<typename T, typename Alloc>
	inline bool
	operator<= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs) {
		return !(rhs < lhs);
	}

	  template<typename T, typename Alloc>
	inline bool
	operator>  (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs) {
		return rhs < lhs;
	}

	  template<typename T, typename Alloc>
	inline bool
	operator>= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs) {
		return !(lhs < rhs);
	}

	  template<typename T, typename Alloc>
	void
	swap (deque<T,Alloc>& x, deque<T,Alloc>& y) {
		x.swap(y);
	}
}
