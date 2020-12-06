#pragma once

// #include <iostream>
// #include <memory>
#include <iterator>
#include <limits>

#if __cplusplus <= 199711L
	#define NOEXCEPT throw()
#else
	#define NOEXCEPT noexcept
#endif

namespace ft {

	template<typename T>
	class list {

	private:

// Supporting structure list_node ---------------------------------------------
		struct list_node {
			T data;
			list_node *prev;
			list_node *next;

			list_node(const T& new_data = T(),
					  list_node *new_prev = NULL,
					  list_node *new_next = NULL) NOEXCEPT
					: data(new_data), prev(new_prev), next(new_next) {}
		};
// ============================================================================

	

// Iterator class for list ----------------------------------------------------
	public:
		struct iterator : std::bidirectional_iterator_tag {
			list_node* ptr;

			iterator() NOEXCEPT : ptr(NULL) {}
			iterator(list_node* new_ptr) NOEXCEPT : ptr(new_ptr) {}
			iterator(const iterator& new_it) NOEXCEPT : ptr(new_it.ptr) {} 

			T&			operator*() const NOEXCEPT {
				return this->ptr->data;
			}
			
			T*	operator->() const NOEXCEPT {
				return &this->ptr->data;
			}

			iterator	operator++() NOEXCEPT {
				ptr = ptr->next;
				return *this;
			}

			iterator	operator++(int) const NOEXCEPT {
				iterator tmp = *this;
				ptr = ptr->next;
				return tmp;
			}
			
			iterator	operator--() NOEXCEPT {
				ptr = ptr->prev;
				return *this;
			}

			iterator	operator--(int) const NOEXCEPT {
				iterator tmp = *this;
				ptr = ptr->prev;
				return tmp;
			}

			iterator	operator++(int) NOEXCEPT {
				iterator tmp = *this;
				ptr = ptr->next;
				return tmp;
			}

			iterator	operator--(int) NOEXCEPT {
				iterator tmp = *this;
				ptr = ptr->prev;
				return tmp;
			}

			bool		operator==(const iterator& x) NOEXCEPT {
				return this->ptr == x.ptr;
			}

			bool		operator!=(const iterator& x) NOEXCEPT {
				return this->ptr != x.ptr;
			}
		};
// ============================================================================

// Const iterator class for list ----------------------------------------------------
	public:
		struct const_iterator : std::bidirectional_iterator_tag {
			typedef const_iterator iterator;

			const list_node* ptr;

			const_iterator() NOEXCEPT : ptr(NULL) {}
			const_iterator(const list_node* new_ptr) NOEXCEPT : ptr(new_ptr) {}
			const_iterator(const iterator& new_it) NOEXCEPT : ptr(new_it.ptr) {} 

			const T&	operator*() const NOEXCEPT {
				return this->ptr->data;
			}
			
			const T*	operator->() const NOEXCEPT {
				return &this->ptr->data;
			}

			iterator	operator++() NOEXCEPT {
				ptr = ptr->next;
				return *this;
			}

			iterator	operator++(int) const NOEXCEPT {
				iterator tmp = *this;
				ptr = ptr->next;
				return tmp;
			}
			
			iterator	operator--() NOEXCEPT {
				ptr = ptr->prev;
				return *this;
			}

			iterator	operator--(int) const NOEXCEPT {
				iterator tmp = *this;
				ptr = ptr->prev;
				return tmp;
			}

			iterator	operator++(int) NOEXCEPT {
				iterator tmp = *this;
				ptr = ptr->next;
				return tmp;
			}

			iterator	operator--(int) NOEXCEPT {
				iterator tmp = *this;
				ptr = ptr->prev;
				return tmp;
			}

			bool		operator==(const iterator& x) NOEXCEPT {
				return this->ptr == x.ptr;
			}

			bool		operator!=(const iterator& x) NOEXCEPT {
				return this->ptr != x.ptr;
			}
		};
// ============================================================================

	private:
		size_t list_size;
		list_node *head;

		void
		list_init() NOEXCEPT {
			this->head->prev = this->head->next = this->head = new list_node;
		}

	public:
		// explicit list (const allocator_type& alloc = allocator_type());
		// explicit list (size_type n, const value_type& val = value_type(),
		// const allocator_type& alloc = allocator_type());
		// template <class InputIterator>
		// list (InputIterator first, InputIterator last,
        // 	const allocator_type& alloc = allocator_type());	

// List constructor	
		list() NOEXCEPT : list_size(0) { list_init(); }

		list(const list& x) NOEXCEPT : list_size(0) { 
			this->list_init();
			*this = x;
		}

		list&
		operator=(const list& x) {
			this->clear();

			const_iterator temp = x.begin();
			while (temp != x.end()) {
				this->push_back(temp.ptr->data);
				temp++;
			}
			return *this;
		}

// List destructor	
		~list() {
			clear();
			delete this->head;
		}
	
// List methods ---------------------------------------------------------------------
		size_t
		size() const NOEXCEPT { return list_size; }

		size_t
		max_size() const NOEXCEPT { return std::numeric_limits<size_t>::max(); }

		iterator
		begin() NOEXCEPT { return iterator(this->head->next); }

		const_iterator
		begin() const NOEXCEPT { return const_iterator(this->head->next); }

		iterator
		end() NOEXCEPT { return iterator(this->head); }

		const_iterator
		end() const NOEXCEPT { return const_iterator(this->head); }

		T&
		front() NOEXCEPT {
			iterator tmp = begin();
			return *tmp;
		}

		const T&
		front() const NOEXCEPT {
			iterator tmp = begin();
			return *tmp;
		}

		T&
		back() NOEXCEPT {
			iterator tmp = end();
			--tmp;
			return *tmp;
		}

		const T&
		back() const NOEXCEPT {
			iterator tmp = end();
			--tmp;
			return *tmp;
		}

		iterator
		insert(iterator position, const T& data);
		// {
		// 	if (!list_size) {
		// 		push_back(data);
		// 		return this->begin();
		// 	}
		// 	list_node *temp = new list_node(data);
		// 	if (position == this->begin())
		// 		this->head = temp;
		// 	temp->next = position.ptr;
		// 	temp->prev = position.ptr->prev;
		// 	position.ptr->prev->next = position.ptr->prev = temp;
		// 	return iterator(temp);
		// }

		void
		push_back(const T& data) {
			if (!list_size) {
				list_node *temp = new list_node(data);
				this->head->prev = this->head->next = temp;
				temp->prev = temp->next = this->head;
			} else {
				list_node *temp = new list_node(data, this->head->prev, this->head);
				this->head->prev->next = temp;
				this->head->prev = temp;
			}
			list_size++;
		}

		void
		push_front(const T& data) {
			list_node *temp = new list_node(data, this->head, this->head->next->next);
			this->head->next = this->head->next->prev = temp;
		}

		// void
		// merge(list&& x);

		// void
		// merge(list& x);

		void
		pop_front() NOEXCEPT {
			this->erase(this->begin());
		}

		void
		pop_back() NOEXCEPT {
			this->erase(iterator(this->head->prev));
		}

		void
		clear() NOEXCEPT {
			list_node *temp;
			while (this->list_size) {
				temp = this->head->next;
				delete this->head;
				this->head = temp;
				this->list_size--;
			}
		}

		iterator
		erase(iterator position) {
			position.ptr->prev->next = position.ptr->next;
			position.ptr->next->prev = position.ptr->prev;
			iterator temp = position++;
			if (temp == this->begin())
				this->head->next = temp.ptr;
			delete temp.ptr;
			list_size -= list_size ? 1 : 0;
			return position;
		}

		iterator
		erase(iterator first, iterator last) {
			while (first != last) {
				first = erase(first);
			}
			return last;
		}

		bool
		empty() const NOEXCEPT {
			return list_size == 0;
		}
// ============================================================================
	};
}
