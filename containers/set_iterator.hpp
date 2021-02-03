#pragma once

#include <memory>
#include <utility>

namespace ft {

// Iterator class -------------------------------------------------------------

	  template<typename T, typename Node>
	struct set_iterator {

	protected:

		bool
		_key_comp(Node* ptr1, Node* ptr2) { return ptr1->_data < ptr2->_data; }

	public:

		typedef set_iterator			iterator;
		typedef size_t					size_type;
		typedef T						value_type;
		typedef value_type*				pointer;
		typedef const value_type*		const_pointer;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
	
		Node* ptr;
	
		set_iterator() throw() : ptr() {}
		set_iterator(Node* newptr) throw() : ptr(newptr) {}


		  template<typename Iterator>
		iterator
		operator= (const Iterator& x)	{ return iterator(x.ptr); }

		reference
		operator*() const throw()		{ return ptr->_data; }

		pointer
		operator->() const throw()	 	{ return &ptr->_data; }

		iterator
		operator++ () throw() {

			if (!ptr->_right->_null) {
				ptr = ptr->_right;
				if (ptr->_last_node)
					return iterator(ptr);
				while (!ptr->_left->_last_node && !ptr->_left->_null)
					ptr = ptr->_left;
			} else {
				if (_key_comp(ptr, ptr->_parent))
					ptr = ptr->_parent;
				else {
					while (!_key_comp(ptr, ptr->_parent))
						ptr = ptr->_parent;
					ptr = ptr->_parent;
				}
			}
			return iterator(ptr);
		}

		iterator
		operator++ (int) throw() {
			
			Node* temp = this->ptr;

			if (!ptr->_right->_null) {
				ptr = ptr->_right;
				if (ptr->_last_node)
					return iterator(ptr);
				while (!ptr->_left->_null)
					ptr = ptr->_left;
			} else {
				if (_key_comp(ptr, ptr->_parent))
					ptr = ptr->_parent;
				else {
					while (!_key_comp(ptr, ptr->_parent))
						ptr = ptr->_parent;
					ptr = ptr->_parent;
				}
			}
			return iterator(temp);
		}

		iterator
		operator-- () throw() {

			if (ptr->_last_node) {
				ptr = ptr->_parent;
			} else if (!ptr->_left->_null) {
				ptr = ptr->_left;
				if (ptr->_last_node)
					return iterator(ptr);
				while (!ptr->_right->_null)
					ptr = ptr->_right;
			} else {
				if (!_key_comp(ptr, ptr->_parent))
					ptr = ptr->_parent;
				else {
					while (_key_comp(ptr, ptr->_parent))
						ptr = ptr->_parent;
					ptr = ptr->_parent;
				}
			}
			return iterator(ptr);
		}

		iterator
		operator-- (int) throw() {

			Node* temp = this->ptr;
		
			if (ptr->_last_node) {
				ptr = ptr->_parent;
			} else if (!ptr->_left->_null) {
				ptr = ptr->_left;
				if (ptr->_last_node)
					return iterator(ptr);
				while (!ptr->_right->_null)
					ptr = ptr->_right;
			} else {
				if (!_key_comp(ptr, ptr->_parent))
					ptr = ptr->_parent;
				else {
					while (_key_comp(ptr, ptr->_parent))
						ptr = ptr->_parent;
					ptr = ptr->_parent;
				}
			}
			return iterator(temp);
		}

		bool
		operator== (const iterator& x) throw() { return this->ptr == x.ptr; }

		bool
		operator!= (const iterator& x) throw() { return this->ptr != x.ptr; }

		Node*
		base() { return ptr; }
	};

// Reverse iterator class -------------------------------------------------------------

	  template<typename T, typename Node>
	struct set_reverse_iterator {

	protected:
	
		bool
		_key_comp(Node* ptr1, Node* ptr2) { return ptr1->_data < ptr2->_data; }

	public:
	
		typedef set_reverse_iterator	reverse_iterator;
		typedef size_t					size_type;
		typedef T						value_type;
		typedef value_type*				pointer;
		typedef const value_type*		const_pointer;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;

		Node* ptr;
	
		set_reverse_iterator() throw() : ptr(NULL) {}
		set_reverse_iterator(Node* newptr) throw() : ptr(newptr) {}

		  template<typename Iterator>
		reverse_iterator
		operator= (const Iterator& x)	{ return reverse_iterator(x.ptr); }

		reference
		operator*() const throw()		{ return ptr->_data; }

		pointer
		operator->() const throw()		{ return &ptr->_data; }

		reverse_iterator
		operator++ () throw() {

			if (!ptr->_left->_null) {
				ptr = ptr->_left;
				if (ptr->_last_node)
					return reverse_iterator(ptr);
				while (!ptr->_right->_null)
					ptr = ptr->_right;
			} else {
				if (!this->_key_comp(ptr, ptr->_parent))
					ptr = ptr->_parent;
				else {
					while (this->_key_comp(ptr, ptr->_parent))
						ptr = ptr->_parent;
					ptr = ptr->_parent;
				}
			}
			return reverse_iterator(ptr);
		}

		reverse_iterator
		operator++ (int) throw() {

			Node* temp = this->ptr;

			if (!ptr->_left->_null) {
				ptr = ptr->_left;
				if (ptr->_last_node)
					return reverse_iterator(ptr);
				while (!ptr->_right->_null)
					ptr = ptr->_right;
			} else {
				if (!this->_key_comp(ptr, ptr->_parent))
					ptr = ptr->_parent;
				else {
					while (this->_key_comp(ptr, ptr->_parent))
						ptr = ptr->_parent;
					ptr = ptr->_parent;
				}
			}
			return reverse_iterator(temp);
		}

		reverse_iterator
		operator-- () throw() {

			if (ptr->_last_node) {
				ptr = ptr->_parent;
			} else if (!ptr->_right->_null) {
				ptr = ptr->_right;
				if (ptr->_last_node)
					return reverse_iterator(ptr);
				while (!ptr->_left->_null)
					ptr = ptr->_left;
			} else {
				if (this->_key_comp(ptr, ptr->_parent))
					ptr = ptr->_parent;
				else {
					while (!this->_key_comp(ptr, ptr->_parent))
						ptr = ptr->_parent;
					ptr = ptr->_parent;
				}
			}
			return reverse_iterator(ptr);
		}

		reverse_iterator
		operator-- (int) throw() {
			
			Node* temp = this->ptr;

			if (ptr->_last_node) {
				ptr = ptr->_parent;
			} else if (!ptr->_right->_null) {
				ptr = ptr->_right;
				if (ptr->_last_node)
					return reverse_iterator(ptr);
				while (!ptr->_left->_null)
					ptr = ptr->_left;
			} else {
				if (this->_key_comp(ptr, ptr->_parent))
					ptr = ptr->_parent;
				else {
					while (!this->_key_comp(ptr, ptr->_parent))
						ptr = ptr->_parent;
					ptr = ptr->_parent;
				}
			}
			return reverse_iterator(temp);
		}

		bool
		operator== (const reverse_iterator& x) throw() { return this->ptr == x.ptr; }

		bool
		operator!= (const reverse_iterator& x) throw() { return this->ptr != x.ptr; }
	};
}