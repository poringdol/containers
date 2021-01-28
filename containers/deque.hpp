#pragma once

#include <limits>
#include "cpp_type_traits.hpp"
#include "deque.hpp"
#include "deque_iterator.hpp"


namespace ft {
/********************************** Deque class ***************************************/

	  template<typename T, typename Alloc = std::allocator<T> >
	class deque : public deque<T, Alloc> {

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

		typedef ft::deque_iterator<T, _deque_node>			deque_iterator;
		typedef ft::deque_reverse_iterator<T, _deque_node>	deque_reverse_iterator;

	public:

		typedef Alloc					allocator_type;
		typedef size_t					size_type;
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
			this->_head = new _deque_node;
			this->_head->_prev = this->_head->_next = this->_head;
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

// Deque constructors ----------------------------------------------------------

		explicit
		deque (const allocator_type& x = allocator_type())
					: _deque_size(0), _alloc(x) { _deque_init(); }

		explicit
		deque (size_type n, value_type val = value_type(), const allocator_type& x = allocator_type()): _deque_size(0), _alloc(x) {
			_deque_init();
			while (n--) { this->push_back(val); }
		}
		

		  template<typename InputIterator>
		deque (InputIterator first, InputIterator last, const allocator_type& x = allocator_type()): _deque_size(0), _alloc(x) {
			_deque_init();
			this->assign(first, last);
		}

		deque (const deque& x): _deque_size(0) { 
			this->_deque_init();
			*this = x;
		}

		deque&
		operator= (const deque& x) {
			this->clear();

			const_iterator temp = x.begin();
			while (temp != x.end()) {
				this->push_back(temp.ptr->_data);
				temp++;
			}
			return *this;
		}

// Deque destructor --------------------------------------------------------------

		~deque() {
			clear();
			delete this->_head;
		}
	
// Deque methods ---------------------------------------------------------------------

	//  Iterators -------------------------------

		iterator
		begin () throw()			{ return iterator(this->_head->_next); }

		const_iterator
		begin () const throw()		{ return const_iterator(this->_head->_next); }

		iterator
		end () throw()				{ return iterator(this->_head); }

		const_iterator
		end () const throw()		{ return const_iterator(this->_head); }

		reverse_iterator
		rbegin () throw()			{ return reverse_iterator(this->_head->_prev); }

		const_reverse_iterator
		rbegin () const throw() 	{ return const_reverse_iterator(this->_head->_prev); }

		reverse_iterator
		rend () throw()				{ return reverse_iterator(this->_head); }

		const_reverse_iterator
		rend () const throw()		{ return const_reverse_iterator(this->_head); }

	// Capacity ----------------------------

		bool
		empty () const throw()		{ return _deque_size == 0; }

		size_type
		size () const throw()		{ return _deque_size; }

		size_type
		max_size () const throw()	{ return std::numeric_limits<size_type>::max() / sizeof(_deque_node) / 2; }

	// Element access -------------------------

		reference
		front () throw()			{ return *(begin()); }

		value_type
		front () const throw()		{ return *(this->begin()); }

		reference
		back () throw()				{ return *(-- (this->end())); }

		value_type
		back () const throw()		{ return *(-- (this->end())); }

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
			_deque_node* temp = new _deque_node(data, this->_head, this->_head->_next);
			this->_head->_next = this->_head->_next->_prev = temp;
			_deque_size++;
		}

		void
		pop_front () throw() { this->erase(this->begin()); }

		void
		push_back (value_type data) {
			if (!_deque_size) {
				_deque_node* temp = new _deque_node(data);
				this->_head->_prev = this->_head->_next = temp;
				temp->_prev = temp->_next = this->_head;
			} else {
				_deque_node* temp = new _deque_node(data, this->_head->_prev, this->_head);
				this->_head->_prev->_next = temp;
				this->_head->_prev = temp;
			}
			_deque_size++;
		}

		void
		pop_back () throw() { this->erase(iterator(this->_head->_prev)); }

		iterator
		insert (iterator position, value_type data) {
			if (position == this->begin()) {
				push_front(data);
				return this->begin();
			}

			_deque_node* temp = new _deque_node(data);
			_node_insert(position.ptr, temp);
			_deque_size++;
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
			_deque_node* temp = this->_head;
			this->_head = x._head;
			x._head = temp;

			size_type size = this->_deque_size;
			_deque_size = x._deque_size;
			x._deque_size = size;
		}

		void
		resize (size_type new_size, value_type val = value_type()) {
			if (new_size < this->_deque_size) {
				iterator it = this->begin();
				while (new_size--)
					++it;
				erase(it, this->end());
			} else {
				insert(this->end(), new_size - this->_deque_size, val);
			}
		}

		void
		clear () throw() {
			_deque_node* temp;
			while (this->_deque_size) {
				temp = this->_head->_next;
				delete this->_head;
				this->_head = temp;
				this->_deque_size--;
			}
			this->_head->_prev = this->_head->_next = this->_head;
		}

	// Operations -----------------------------

		void
		splice (iterator position, deque& x) {
			while (x._deque_size--) {
				iterator first = x.begin();
				iterator temp = ++(x.begin());
				_cut(first);
				_node_insert(position.ptr, first.ptr);
				first = temp;
				_deque_size++;
			}
			x._head->_next = x._head->_prev = x._head;
			x._deque_size = 0;
		}

		void
		splice (iterator position, deque& x, iterator i) {
			_cut(i);
			_deque_size++;
			x._deque_size--;
			_node_insert(position.ptr, i.ptr);
		}

		void
		splice (iterator position, deque& x, iterator first, iterator last) {
			while (first != last) {
				iterator temp = first;
				++temp;
				_cut(first);
				_node_insert(position.ptr, first.ptr);
				first = temp;
				_deque_size++;
				x._deque_size--;
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
					_deque_size--;
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
					_deque_size--;
					first = temp;
				} else {
					++first;
				}
			}
		}

		void
		merge (deque& x) { this->merge(x, _compare); }

		  template<typename Compare>
		void
		merge (deque& x, Compare comp) {
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
					this->_deque_size++;
				}
				else
					++first1;
			}
			while (first2 != last2) {
				iterator temp = first2;
				temp++;
				_node_insert(first1.ptr, first2.ptr);
				first2 = temp;
				this->_deque_size++;;
			}
			x._head->_next = x._head->_prev = x._head;
			x._deque_size = 0;
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
			size_type size = this->_deque_size;
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
