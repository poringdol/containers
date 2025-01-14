#pragma once

namespace ft {

// Iterator class -------------------------------------------------------------

	  template<typename T, typename Node>
	struct list_iterator {

		typedef list_iterator		iterator;
		typedef size_t				size_type;
		typedef T					value_type;
		typedef T*					pointer;
		typedef T&					reference;

		Node* ptr;

		list_iterator() throw() : ptr(NULL) {}
		list_iterator(Node* new_ptr) throw() : ptr(new_ptr) {}

		  template<typename Iterator>
		iterator
		operator= (const Iterator& x)	{ return iterator(x.ptr); }

		reference
		operator*() const throw()		{ return this->ptr->_data; }

		pointer
		operator->() const throw() 		{ return &this->ptr->_data; }

		iterator
		operator++ () throw() {
			this->ptr = this->ptr->_next;
			return *this;
		}

		iterator
		operator++ (int) throw() {
			iterator tmp = *this;
			this->ptr = this->ptr->_next;
			return tmp;
		}

		iterator
		operator-- () throw() {
			this->ptr = this->ptr->_prev;
			return *this;
		}

		iterator
		operator-- (int) throw() {
			iterator tmp = *this;
			this->ptr = this->ptr->_prev;
			return tmp;
		}

		bool
		operator== (const iterator& x) throw() { return this->ptr == x.ptr; }

		bool
		operator!= (const iterator& x) throw() { return this->ptr != x.ptr; }
	};
// ============================================================================

// Const Iterator class -------------------------------------------------------------

	  template<typename T, typename Node>
	struct const_list_iterator {

		typedef const_list_iterator	iterator;
		typedef size_t				size_type;
		typedef T					value_type;
		typedef const T*			pointer;
		typedef const T&			reference;

		const Node* ptr;

		const_list_iterator() throw() : ptr(NULL) {}
		const_list_iterator(Node* new_ptr) throw() : ptr(new_ptr) {}
		const_list_iterator(list_iterator<T, Node> it) throw() { this->ptr = it.ptr; }

		  template<typename Iterator>
		iterator
		operator= (const Iterator& x)	{ return iterator(x.ptr); }

		reference
		operator*() const throw()		{ return this->ptr->_data; }

		pointer
		operator->() const throw() 		{ return &this->ptr->_data; }

		iterator
		operator++ () throw() {
			this->ptr = this->ptr->_next;
			return *this;
		}

		iterator
		operator++ (int) throw() {
			iterator tmp = *this;
			this->ptr = this->ptr->_next;
			return tmp;
		}

		iterator
		operator-- () throw() {
			this->ptr = this->ptr->_prev;
			return *this;
		}

		iterator
		operator-- (int) throw() {
			iterator tmp = *this;
			this->ptr = this->ptr->_prev;
			return tmp;
		}

		bool
		operator== (const iterator& x) throw() { return this->ptr == x.ptr; }

		bool
		operator!= (const iterator& x) throw() { return this->ptr != x.ptr; }
	};
// ============================================================================

// Reverse iterator class -----------------------------------------------------

	  template<typename T, typename Node>
	struct list_reverse_iterator : list_iterator<T, Node> {

		typedef list_reverse_iterator	reverse_iterator;
		typedef list_iterator<T, Node>	base_iterator;

		list_reverse_iterator() throw() : base_iterator() {}
		list_reverse_iterator(Node* new_ptr) throw() : base_iterator(new_ptr) {}

		  template<typename Iterator>
		reverse_iterator
		operator= (Iterator& x) { return reverse_iterator(x.ptr); }

		reverse_iterator
		operator++ () throw() {
			this->ptr = this->ptr->_prev;
			return *this;
		}

		reverse_iterator
		operator++ (int) throw() {
			reverse_iterator tmp = *this;
			this->ptr = this->ptr->_prev;
			return tmp;
		}

		reverse_iterator
		operator-- () throw() {
			this->ptr = this->ptr->_next;
			return *this;
		}

		reverse_iterator
		operator-- (int) throw() {
			reverse_iterator tmp = *this;
			this->ptr = this->ptr->_next;
			return tmp;
		}
	};
// ============================================================================

// Const Reverse iterator class -----------------------------------------------------

	  template<typename T, typename Node>
	struct const_list_reverse_iterator : const_list_iterator<T, Node> {

		typedef const_list_reverse_iterator		reverse_iterator;
		typedef const_list_iterator<T, Node>	base_iterator;

		const_list_reverse_iterator() throw() : base_iterator() {}
		const_list_reverse_iterator(Node* new_ptr) throw() : base_iterator(new_ptr) {}
		const_list_reverse_iterator(list_reverse_iterator<T, Node> it) throw() { this->ptr = it.ptr; }

		  template<typename Iterator>
		reverse_iterator
		operator= (Iterator& x) { return reverse_iterator(x.ptr); }

		reverse_iterator
		operator++ () throw() {
			this->ptr = this->ptr->_prev;
			return *this;
		}

		reverse_iterator
		operator++ (int) throw() {
			reverse_iterator tmp = *this;
			this->ptr = this->ptr->_prev;
			return tmp;
		}

		reverse_iterator
		operator-- () throw() {
			this->ptr = this->ptr->_next;
			return *this;
		}

		reverse_iterator
		operator-- (int) throw() {
			reverse_iterator tmp = *this;
			this->ptr = this->ptr->_next;
			return tmp;
		}
	};
}
// ============================================================================
