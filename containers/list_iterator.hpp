#pragma once

#include <memory>
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

	  template<typename T, typename Node>
	struct list_iterator {

		typedef list_iterator		iterator;
		typedef size_t				size_type;
		typedef T					value_type;
		typedef T*					pointer;
		typedef const T*			const_pointer;
		typedef T&					reference;
		typedef const T&			const_reference;

		Node* ptr;

		list_iterator() NOEXCEPT : ptr(NULL) {}
		list_iterator(Node* new_ptr) NOEXCEPT : ptr(new_ptr) {}

		  template<typename Iterator>
		iterator
		operator= (const Iterator& x)	{ return iterator(x.ptr); }

		reference
		operator*() const NOEXCEPT		{ return this->ptr->_data; }

		pointer
		operator->() const NOEXCEPT 		{ return &this->ptr->_data; }

		iterator
		operator++ () NOEXCEPT {
			this->ptr = this->ptr->_next;
			return *this;
		}

		iterator
		operator++ (int) NOEXCEPT {
			iterator tmp = *this;
			this->ptr = this->ptr->_next;
			return tmp;
		}

		iterator
		operator-- () NOEXCEPT {
			this->ptr = this->ptr->_prev;
			return *this;
		}

		iterator
		operator-- (int) NOEXCEPT {
			iterator tmp = *this;
			this->ptr = this->ptr->_prev;
			return tmp;
		}

		bool
		operator== (const iterator& x) NOEXCEPT { return this->ptr == x.ptr; }

		bool
		operator!= (const iterator& x) NOEXCEPT { return this->ptr != x.ptr; }
	};
// ============================================================================

// Reverse iterator class -----------------------------------------------------

	  template<typename T, typename Node>
	struct list_reverse_iterator : list_iterator<T, Node> {

		typedef list_reverse_iterator	reverse_iterator;
		typedef size_t						size_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef const T*					const_pointer;
		typedef T&							reference;
		typedef const T&					const_reference;
		typedef list_iterator<T, Node>	base_iterator;

		list_reverse_iterator() NOEXCEPT : base_iterator() {}
		list_reverse_iterator(Node* new_ptr) NOEXCEPT : base_iterator(new_ptr) {}

		  template<typename Iterator>
		reverse_iterator
		operator= (Iterator& x) { return reverse_iterator(x.ptr); }

		reverse_iterator
		operator++ () NOEXCEPT {
			this->ptr = this->ptr->_prev;
			return *this;
		}

		reverse_iterator
		operator++ (int) NOEXCEPT {
			reverse_iterator tmp = *this;
			this->ptr = this->ptr->_prev;
			return tmp;
		}

		reverse_iterator
		operator-- () NOEXCEPT {
			this->ptr = this->ptr->_next;
			return *this;
		}

		reverse_iterator
		operator-- (int) NOEXCEPT {
			reverse_iterator tmp = *this;
			this->ptr = this->ptr->_next;
			return tmp;
		}
	};
}
// ============================================================================