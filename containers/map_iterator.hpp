#pragma once

#include <memory>
#include <utility>
#include "map.hpp"

#ifndef NOEXCEPT
	#if __cplusplus >= 201103L
		#define NOEXCEPT noexcept
	#else
		#define NOEXCEPT throw()
	#endif
#endif

namespace ft {

// Iterator class -------------------------------------------------------------

	  template<typename Key, typename T, typename Node>
	struct map_iterator {

	protected:
		bool
		_key_comp(Node* ptr1, Node* ptr2) { return ptr1->_data.first < ptr2->_data.first; }

	public:

		typedef map_iterator			iterator;
		typedef size_t					size_type;
		typedef std::pair<const Key, T>	value_type;
		typedef value_type*				pointer;
		typedef const value_type*		const_pointer;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
	
		Node* ptr;
	
		map_iterator() NOEXCEPT : ptr() {}
		map_iterator(Node* newptr) NOEXCEPT : ptr(newptr) {}

		  template<typename Iterator>
		iterator
		operator= (const Iterator& x)	{ return iterator(x.ptr); }

		reference
		operator*() const NOEXCEPT		{ return ptr->_data; }

		pointer
		operator->() const NOEXCEPT 	{ return &ptr->_data; }

		iterator
		operator++ () NOEXCEPT {
			
			if (ptr->_right) {
				ptr = ptr->_right;
				while (ptr->_left)
					ptr = ptr->_left;
			} else {
				if (_key_comp(ptr, ptr->_parent))
					ptr = ptr->_parent;
				else {
					// ptr = ptr->_parent;
					while (!_key_comp(ptr, ptr->_parent))
						ptr = ptr->_parent;
					ptr = ptr->_parent;
				}
			}
			return iterator(ptr);
		}

		iterator
		operator++ (int) NOEXCEPT {
			
			Node* temp = this->ptr;

			if (ptr->_right) {
				ptr = ptr->_right;
				while (ptr->_left)
					ptr = ptr->_left;
			} else {
				if (_key_comp(ptr, ptr->_parent))
					ptr = ptr->_parent;
				else {
					// ptr = ptr->_parent;
					while (!_key_comp(ptr, ptr->_parent))
						ptr = ptr->_parent;
					ptr = ptr->_parent;
				}
			}
			return iterator(temp);
		}

		iterator
		operator-- () NOEXCEPT {

			if (ptr->_last_node) {
				ptr == ptr->_parent;
			} else if (ptr->_left) {
				ptr = ptr->_left;
				while (ptr->_right)
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
		operator-- (int) NOEXCEPT {

			Node* temp = this->ptr;
		
			if (ptr->_last_node) {
				ptr == ptr->_parent;
			} else if (ptr->_left) {
				ptr = ptr->_left;
				while (ptr->_right)
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
		operator== (const iterator& x) NOEXCEPT { return this->ptr == x.ptr; }

		bool
		operator!= (const iterator& x) NOEXCEPT { return this->ptr != x.ptr; }
	};

// Reverse iterator class -------------------------------------------------------------

	  template<typename Key, typename T, typename Node>
	struct map_reverse_iterator : map_iterator<Key, T, Node> {

		typedef map_reverse_iterator	reverse_iterator;
		typedef size_t					size_type;
		typedef std::pair<const Key, T>	value_type;
		typedef value_type*				pointer;
		typedef const value_type*		const_pointer;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;

		Node* ptr;
	
		map_reverse_iterator() NOEXCEPT : ptr(NULL) {}
		map_reverse_iterator(Node* newptr) NOEXCEPT : ptr(newptr) {}

		  template<typename Iterator>
		reverse_iterator
		operator= (const Iterator& x)	{ return reverse_iterator(x.ptr); }

		reference
		operator*() const NOEXCEPT		{ return ptr->_data; }

		pointer
		operator->() const NOEXCEPT 	{ return &ptr->_data; }

		reverse_iterator
		operator++ () NOEXCEPT {

			if (ptr->_left) {
				ptr = ptr->_left;
				while (ptr->_right)
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
		operator++ (int) NOEXCEPT {

			Node* temp = this->ptr;

			if (ptr->_left) {
				ptr = ptr->_left;
				while (ptr->_right)
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
		operator-- () NOEXCEPT {

			if (ptr->_last_node) {
				ptr == ptr->_parent;
			} else if (ptr->_right) {
				ptr = ptr->_right;
				while (ptr->_left)
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
		operator-- (int) NOEXCEPT {
			
			Node* temp = this->ptr;

			if (ptr->_last_node) {
				ptr == ptr->_parent;
			} else if (ptr->_right) {
				ptr = ptr->_right;
				while (ptr->_left)
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
		operator== (const reverse_iterator& x) NOEXCEPT { return this->ptr == x.ptr; }

		bool
		operator!= (const reverse_iterator& x) NOEXCEPT { return this->ptr != x.ptr; }
	};
}