#pragma once

#include <limits>
#include "cpp_type_traits.hpp"
#include "list_iterator.hpp"

#ifndef NOEXCEPT
	#if __cplusplus >= 201103L
		#define NOEXCEPT noexcept
	#else
		#define NOEXCEPT throw()
	#endif
#endif


namespace ft {
/********************************** List class ***************************************/

	  template<typename T, typename Alloc = std::allocator<T> >
	class list {

	private:

// Supporting structure list_node ---------------------------------------------

		struct _list_node {
			T _data;
			_list_node *_prev;
			_list_node *_next;

			_list_node (T new_data = T(),
					  _list_node *new_prev = NULL,
					  _list_node *new_next = NULL) NOEXCEPT
					: _data(new_data), _prev(new_prev), _next(new_next) {}
		};
// ============================================================================

		typedef ft::list_iterator<T, _list_node>			list_iterator;
		typedef ft::list_reverse_iterator<T, _list_node>	list_reverse_iterator;

	public:

		typedef Alloc										allocator_type;
		typedef size_t										size_type;
		typedef T											value_type;
		typedef T*											pointer;
		typedef const T*									const_pointer;
		typedef T&											reference;
		typedef const T&									const_reference;
		typedef list_iterator							iterator;
		typedef list_iterator							const_iterator;
		typedef list_reverse_iterator					reverse_iterator;
		typedef list_reverse_iterator					const_reverse_iterator;

	private:

		size_type _list_size;
		_list_node* _head;
		Alloc _alloc;


// Supporting functions -------------------------------------------------------

		void
		_list_init () NOEXCEPT {
			this->_head = new _list_node;
			this->_head->_prev = this->_head->_next = this->_head;
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
				this->insert(position, *first);
			}
		}

		  template<typename T1>
		void
		_insert (iterator position, size_type n, T1 val, ft::true_type_my) {
			while (n--) {
				iterator temp = position;
				this->insert(temp, val);
			}
		}

		  template<typename InputIterator>
		void
		_assign (InputIterator first, InputIterator last, ft::false_type_my) {
			this->clear();
			while (first != last) {
				this->push_back(*first);
				++first;
			}
		}

		  template<typename T1>
		void
		_assign (size_type n, T1 val, ft::true_type_my) {
			this->clear();
			while (n--) {
				this->push_back(val);
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
			while (n--) { this->push_back(val); }
		}
		

		  template<typename InputIterator>
		list (InputIterator first, InputIterator last, const allocator_type& x = allocator_type()): _list_size(0), _alloc(x) {
			_list_init();
			this->assign(first, last);
		}

		list (const list& x): _list_size(0) { 
			this->_list_init();
			*this = x;
		}

		list&
		operator= (const list& x) {
			this->clear();

			const_iterator temp = x.begin();
			while (temp != x.end()) {
				this->push_back(temp.ptr->_data);
				temp++;
			}
			return *this;
		}

// List destructor --------------------------------------------------------------

		~list() {
			clear();
			delete this->_head;
		}
	
// List methods ---------------------------------------------------------------------

	//  Iterators -------------------------------

		iterator
		begin () NOEXCEPT			{ return iterator(this->_head->_next); }

		const_iterator
		begin () const NOEXCEPT		{ return const_iterator(this->_head->_next); }

		iterator
		end () NOEXCEPT				{ return iterator(this->_head); }

		const_iterator
		end () const NOEXCEPT		{ return const_iterator(this->_head); }

		reverse_iterator
		rbegin () NOEXCEPT			{ return reverse_iterator(this->_head->_prev); }

		const_reverse_iterator
		rbegin () const NOEXCEPT 	{ return const_reverse_iterator(this->_head->_prev); }

		reverse_iterator
		rend () NOEXCEPT				{ return reverse_iterator(this->_head); }

		const_reverse_iterator
		rend () const NOEXCEPT		{ return const_reverse_iterator(this->_head); }

	// Capacity ----------------------------

		bool
		empty () const NOEXCEPT		{ return _list_size == 0; }

		size_type
		size () const NOEXCEPT		{ return _list_size; }

		size_type
		max_size () const NOEXCEPT	{ return std::numeric_limits<size_type>::max() / sizeof(_list_node) / 2; }

	// Element access -------------------------

		reference
		front () NOEXCEPT			{ return *(begin()); }

		value_type
		front () const NOEXCEPT		{ return *(this->begin()); }

		reference
		back () NOEXCEPT				{ return *(-- (this->end())); }

		value_type
		back () const NOEXCEPT		{ return *(-- (this->end())); }

	// Modifiers ------------------------------

		  template<typename InputIterator>
		void
		assign (InputIterator first, InputIterator last) {
			typedef typename ft::is_integer_my<InputIterator>::type_my _Integral;
			_assign(first, last, _Integral());
		}

		void
		assign (size_type n, value_type val) {
			_assign(n, val, ft::true_type_my());
		}

		void
		push_front (value_type data) {
			_list_node *temp = new _list_node(data, this->_head, this->_head->_next);
			this->_head->_next = this->_head->_next->_prev = temp;
			_list_size++;
		}

		void
		pop_front () NOEXCEPT { this->erase(this->begin()); }

		void
		push_back (value_type data) {
			if (!_list_size) {
				_list_node *temp = new _list_node(data);
				this->_head->_prev = this->_head->_next = temp;
				temp->_prev = temp->_next = this->_head;
			} else {
				_list_node *temp = new _list_node(data, this->_head->_prev, this->_head);
				this->_head->_prev->_next = temp;
				this->_head->_prev = temp;
			}
			_list_size++;
		}

		void
		pop_back () NOEXCEPT { this->erase(iterator(this->_head->_prev)); }

		iterator
		insert (iterator position, value_type data) {
			if (position == this->begin()) {
				push_front(data);
				return this->begin();
			}

			_list_node *temp = new _list_node(data);
			_node_insert(position.ptr, temp);
			_list_size++;
			return iterator(temp);
		}

		void
		insert (iterator position, size_type n, value_type val) {
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
			if (position != this->end()) {
				_cut(position);
				iterator temp = position++;
				if (temp == this->begin())
					this->_head->_next = temp.ptr;
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
			_list_node* temp = this->_head;
			this->_head = x._head;
			x._head = temp;

			size_type size = this->_list_size;
			_list_size = x._list_size;
			x._list_size = size;
		}

		void
		resize (size_type new_size, value_type val = value_type()) {
			if (new_size < this->_list_size) {
				iterator it = this->begin();
				while (new_size--)
					++it;
				erase(it, this->end());
			} else {
				insert(this->end(), new_size - this->_list_size, val);
			}
		}

		void
		clear () NOEXCEPT {
			_list_node *temp;
			while (this->_list_size) {
				temp = this->_head->_next;
				delete this->_head;
				this->_head = temp;
				this->_list_size--;
			}
			this->_head->_prev = this->_head->_next = this->_head;
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
		remove (value_type val) {
			iterator it = this->begin();
			while (it != this->end()) {
				iterator temp = it;
				++it;
				if (*temp == val) {
					this->erase(temp);
				}
			}
		}

		  template<typename Compare>
		void
		remove_if (Compare comp) {
			iterator it = this->begin();
			while (it != this->end()) {
				iterator temp = it;
				++it;
				if (comp(*temp)) {
					this->erase(temp);
				}
			}
		}


		void
		unique() {
			iterator first = this->begin();
			++first;
			while (first != this->end()) {
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
						iterator first = this->begin();
			++first;
			while (first != this->end()) {
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
		merge (list& x) { this->merge(x, _compare); }

		  template<typename Compare>
		void
		merge (list& x, Compare comp) {
			if (&x == this)
				return;
			iterator first1 = this->begin(), first2 = x.begin(),
					  last1 = this->end(),	  last2 = x.end();
			while (first1 != last1 && first2 != last2) {
				if (comp(*first2, *first1)) {
					iterator temp = first2;
					temp++;
					_node_insert(first1.ptr, first2.ptr);
					first2 = temp;
					this->_list_size++;
				}
				else
					++first1;
			}
			while (first2 != last2) {
				iterator temp = first2;
				temp++;
				_node_insert(first1.ptr, first2.ptr);
				first2 = temp;
				this->_list_size++;;
			}
			x._head->_next = x._head->_prev = x._head;
			x._list_size = 0;
		}

		void
		sort() { this->sort(_compare); }

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
			iterator first = this->_head;
			size_type size = this->_list_size;
			while (size--) {
				iterator last = -- (this->end());
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
		
		typename ft::list<T>::iterator first1 = lhs.begin();
		typename ft::list<T>::iterator first2 = rhs.begin();
		
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

		typename ft::list<T>::iterator first1 = lhs.begin();
		typename ft::list<T>::iterator first2 = rhs.begin();
		
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
