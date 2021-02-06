#pragma once

#include <limits>
#include <memory>
#include <cstddef>
#include "cpp_type_traits.hpp"
#include "list_iterator.hpp"


namespace ft {
/********************************** List class ***************************************/

	  template<typename T, typename Alloc = std::allocator<T> >
	class list {

	protected:

// Supporting structure list_node ---------------------------------------------

		struct _list_node {
			T _data;
			_list_node* _prev;
			_list_node* _next;

			_list_node (T new_data = T(),
					  _list_node* new_prev = NULL,
					  _list_node* new_next = NULL) throw()
					: _data(new_data), _prev(new_prev), _next(new_next) {}
		};
// ============================================================================


	public:

		typedef Alloc					allocator_type;
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;
		typedef T						value_type;
		typedef T*						pointer;
		typedef const T*				const_pointer;
		typedef T&						reference;
		typedef const T&				const_reference;

		typedef ft::list_iterator<T, _list_node>				iterator;
		typedef ft::const_list_iterator<T, _list_node>			const_iterator;
		typedef ft::list_reverse_iterator<T, _list_node>		reverse_iterator;
		typedef ft::const_list_reverse_iterator<T, _list_node>	const_reverse_iterator;

	protected:

		size_type	_list_size;
		_list_node*	_head;
		Alloc		_alloc;

// Supporting functions -------------------------------------------------------

		void
		_list_init () throw() {
			_head = new _list_node;
			_head->_prev = _head->_next = _head;
		}

		/* 'insert' node placed to current position, 'current' moved to _next position */
		void
		_node_insert (_list_node* current, _list_node* insert) {
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

// List constructors ----------------------------------------------------------

		explicit
		list (const allocator_type& x = allocator_type())
					: _list_size(0), _alloc(x) { _list_init(); }

		explicit
		list (size_type n, value_type val = value_type(), const allocator_type& x = allocator_type()): _list_size(0), _alloc(x) {
			_list_init();
			while (n--) { push_back(val); }
		}
		

		  template<typename InputIterator>
		list (InputIterator first, InputIterator last, const allocator_type& x = allocator_type()): _list_size(0), _alloc(x) {
			_list_init();
			assign(first, last);
		}

		list (const list& x): _list_size(0) { 
			_list_init();
			*this = x;
		}

		list&
		operator= (const list& x) {
			clear();

			const_iterator temp = x.begin();
			while (temp != x.end()) {
				push_back(temp.ptr->_data);
				temp++;
			}
			return *this;
		}

// List destructor --------------------------------------------------------------

		~list() {
			clear();
			delete _head;
		}
	
// List methods ---------------------------------------------------------------------

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
		empty () const throw()		{ return _list_size == 0; }

		size_type
		size () const throw()		{ return _list_size; }

		size_type
		max_size () const throw()	{ return std::numeric_limits<size_type>::max() / sizeof(_list_node); }

	// Element access -------------------------

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
			_list_node* temp = new _list_node(data, _head, _head->_next);
			_head->_next = _head->_next->_prev = temp;
			_list_size++;
		}

		void
		pop_front () throw() { erase(begin()); }

		void
		push_back (const value_type& data) {
			if (!_list_size) {
				_list_node* temp = new _list_node(data);
				_head->_prev = _head->_next = temp;
				temp->_prev = temp->_next = _head;
			} else {
				_list_node* temp = new _list_node(data, _head->_prev, _head);
				_head->_prev->_next = temp;
				_head->_prev = temp;
			}
			_list_size++;
		}

		void
		pop_back () throw() { erase(iterator(_head->_prev)); }

		iterator
		insert (iterator position, const value_type& data) {
			if (position == begin()) {
				push_front(data);
				return begin();
			}

			_list_node* temp = new _list_node(data);
			_node_insert(position.ptr, temp);
			_list_size++;
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
				_list_size -= _list_size ? 1 : 0;
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
		swap (list& x) {
			_list_node* temp = _head;
			_head = x._head;
			x._head = temp;

			size_type size = _list_size;
			_list_size = x._list_size;
			x._list_size = size;
		}

		void
		resize (size_type new_size, value_type val = value_type()) {
			if (new_size < _list_size) {
				iterator it = begin();
				while (new_size--)
					++it;
				erase(it, end());
			} else {
				insert(end(), new_size - _list_size, val);
			}
		}

		void
		clear () throw() {
			_list_node* temp;
			while (_list_size) {
				temp = _head->_next;
				delete _head;
				_head = temp;
				_list_size--;
			}
			_head->_prev = _head->_next = _head;
		}

	// Operations -----------------------------

		void
		splice (iterator position, list& x) {
			while (x._list_size--) {
				iterator first = x.begin();
				iterator temp = ++(x.begin());
				_cut(first);
				_node_insert(position.ptr, first.ptr);
				first = temp;
				_list_size++;
			}
			x._head->_next = x._head->_prev = x._head;
			x._list_size = 0;
		}

		void
		splice (iterator position, list& x, iterator i) {
			_cut(i);
			_list_size++;
			x._list_size--;
			_node_insert(position.ptr, i.ptr);
		}

		void
		splice (iterator position, list& x, iterator first, iterator last) {
			while (first != last) {
				iterator temp = first;
				++temp;
				_cut(first);
				_node_insert(position.ptr, first.ptr);
				first = temp;
				_list_size++;
				x._list_size--;
			}
		}

		void
		remove (const value_type& val) {
			iterator it = begin();
			while (it != end()) {
				iterator temp = it;
				++it;
				if (*temp == val) {
					erase(temp);
				}
			}
		}

		  template<typename Compare>
		void
		remove_if (Compare comp) {
			iterator it = begin();
			while (it != end()) {
				iterator temp = it;
				++it;
				if (comp(*temp)) {
					erase(temp);
				}
			}
		}

		void
		unique() {
			iterator first = begin();
			++first;
			while (first != end()) {
				if (first.ptr->_data == first.ptr->_prev->_data) {
					iterator temp = first;
					++temp;
					_cut(first);
					delete first.ptr;
					_list_size--;
					first = temp;
				} else {
					++first;
				}
			}
		}

		  template<typename BinaryPredicate>
		void
		unique (BinaryPredicate binary_pred) {
						iterator first = begin();
			++first;
			while (first != end()) {
				if (binary_pred(first.ptr->_data, first.ptr->_prev->_data)) {
					iterator temp = first;
					++temp;
					_cut(first);
					delete first.ptr;
					_list_size--;
					first = temp;
				} else {
					++first;
				}
			}
		}

		void
		merge (list& x) { merge(x, _compare); }

		  template<typename Compare>
		void
		merge (list& x, Compare comp) {
			if (&x == this)
				return;
			iterator first1 = begin(), first2 = x.begin(),
					  last1 = end(),	  last2 = x.end();
			while (first1 != last1 && first2 != last2) {
				if (comp(*first2, *first1)) {
					iterator temp = first2;
					temp++;
					_node_insert(first1.ptr, first2.ptr);
					first2 = temp;
					_list_size++;
				}
				else
					++first1;
			}
			while (first2 != last2) {
				iterator temp = first2;
				temp++;
				_node_insert(first1.ptr, first2.ptr);
				first2 = temp;
				_list_size++;;
			}
			x._head->_next = x._head->_prev = x._head;
			x._list_size = 0;
		}

		void
		sort() { sort(_compare); }

		  template<typename Compare>
		void
		sort (Compare comp) {
			for (iterator it = begin(); it != end(); ) {
				iterator it_min;
				it_min = it;
				for (iterator itt = it; itt != end(); ++itt) {
					if (comp(*itt, *it_min)) {
						it_min = itt;
					}
				}
				if (it_min != it) {
					_cut(it_min);
					_node_insert(it.ptr, it_min.ptr);
				} else {
					++it;
				}
			}
		}

		void
		reverse () {
			iterator first = _head;
			size_type size = _list_size;
			while (size--) {
				iterator last = -- (end());
				_cut(last);
				
				first.ptr->_next->_prev = last.ptr;
				last.ptr->_next = first.ptr->_next;
				first.ptr->_next = last.ptr;
				last.ptr->_prev = first.ptr;
				++first;
			}
		}

// Friend functions -----------------------------------------------------------
		  template<typename _T, typename _Alloc>
		friend bool
		operator== (const list<_T, _Alloc>&, const list<_T, _Alloc>&);

		  template<typename _T, typename _Alloc>
		friend  bool
		operator<  (const list<_T, _Alloc>&, const list<_T, _Alloc>&);

		  template<typename _T, typename _Alloc>
		friend void
		swap (list<_T, _Alloc>&, list<_T, _Alloc>&);

	};

/************************************ end of list class ***********************************/

// Friend functions definitions -----------------------------------------------

	  template<typename T, typename Alloc>
	inline bool
	operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		
		if (lhs.size() != rhs.size()) return false;
		
		typename ft::list<T>::const_iterator first1 = lhs.begin();
		typename ft::list<T>::const_iterator first2 = rhs.begin();
		
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
	operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	  template<typename T, typename Alloc>
	inline bool
	operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {

		typename ft::list<T>::const_iterator first1 = lhs.begin();
		typename ft::list<T>::const_iterator first2 = rhs.begin();
		
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
	operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return !(rhs < lhs);
	}

	  template<typename T, typename Alloc>
	inline bool
	operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return rhs < lhs;
	}

	  template<typename T, typename Alloc>
	inline bool
	operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return !(lhs < rhs);
	}

	  template<typename T, typename Alloc>
	void
	swap (list<T,Alloc>& x, list<T,Alloc>& y) {
		x.swap(y);
	}
}
