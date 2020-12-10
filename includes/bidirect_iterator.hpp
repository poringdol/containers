#pragma once

#include <iterator>
#include "list.hpp"

namespace ft {
// Iterator class -------------------------------------------------------------
	template<typename T, typename Node>
	struct iterator : std::bidirectional_iterator_tag {

		typedef size_t				size_type;
		typedef T					value_type;
		typedef T*					pointer;
		typedef const T*			const_pointer;
		typedef T&					reference;
		typedef const T&			const_reference;

		Node* ptr;

		iterator() throw() : ptr(NULL) {}
		iterator(Node* new_ptr) throw() : ptr(new_ptr) {}

		template<typename Iterator>
		iterator
		operator= (const Iterator& x) { return iterator(x.ptr); }

		reference
		operator*() const throw() {
			return this->ptr->data;
		}

		pointer
		operator->() const throw() {
			return &this->ptr->data;
		}

		iterator
		operator++ () throw() {
			this->ptr = this->ptr->next;
			return *this;
		}

		iterator
		operator++ (int) throw() {
			iterator tmp = *this;
			this->ptr = this->ptr->next;
			return tmp;
		}

		iterator
		operator-- () throw() {
			this->ptr = this->ptr->prev;
			return *this;
		}

		iterator
		operator-- (int) throw() {
			iterator tmp = *this;
			this->ptr = this->ptr->prev;
			return tmp;
		}

		bool
		operator== (const iterator& x) throw() {
			return this->ptr == x.ptr;
		}

		bool
		operator!= (const iterator& x) throw() {
			return this->ptr != x.ptr;
		}
	};
// ============================================================================

// Reverse iterator class -----------------------------------------------------
	template<typename T, typename Node>
	struct reverse_iterator : iterator<T, Node> {

		typedef size_t					size_type;
		typedef T						value_type;
		typedef T*						pointer;
		typedef const T*				const_pointer;
		typedef T&						reference;
		typedef const T&				const_reference;
		typedef iterator<T, Node>		base_iterator;

		reverse_iterator() throw() : base_iterator() {}
		reverse_iterator(Node* new_ptr) throw() : base_iterator(new_ptr) {}

		template<typename Iterator>
		reverse_iterator
		operator= (Iterator& x) { return reverse_iterator(x.ptr); }

		reverse_iterator
		operator++ () throw() {
			this->ptr = this->ptr->prev;
			return *this;
		}

		reverse_iterator
		operator++ (int) throw() {
			reverse_iterator tmp = *this;
			this->ptr = this->ptr->prev;
			return tmp;
		}

		reverse_iterator
		operator-- () throw() {
			this->ptr = this->ptr->next;
			return *this;
		}

		reverse_iterator
		operator-- (int) throw() {
			reverse_iterator tmp = *this;
			this->ptr = this->ptr->next;
			return tmp;
		}
	};
}
// ============================================================================