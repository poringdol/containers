#pragma once

#include <limits>
#include <memory>
#include "map_iterator.hpp"
#include "cpp_type_traits.hpp"

#ifndef NOEXCEPT
	#if __cplusplus >= 201103L
		#define NOEXCEPT noexcept
	#else
		#define NOEXCEPT throw()
	#endif
#endif


namespace ft {

/********************************** Map class ***************************************/

	  template <typename Key,
			  typename T,
			  typename Compare = std::less<Key>,
			  typename Alloc = std::allocator<std::pair<const Key, T> > >
	class map {

	public:

		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair<const Key, T>						value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef T&											reference;
		typedef const T&									const_reference;
		typedef T*											pointer;
		typedef const T*									const_pointer;
		typedef size_t										size_type;

// Enum for coloring nodes
		enum _rb_tree_color { _black_node = false, _red_node = true };
// ----------------------------------------------------------------------------

// Supporting structure tree node
		struct _rb_tree_node {

			value_type			_data;
			_rb_tree_color		_color;
			_rb_tree_node*		_parent;
			_rb_tree_node*		_left;
			_rb_tree_node*		_right;
			bool				_last_node;

			// _rb_tree_node (): _data() _color(), _parent(),
			// 				  _left(), _right(){}

			_rb_tree_node (value_type data			= value_type(),
							_rb_tree_color color	= _red_node,
							_rb_tree_node* parent	= NULL,
							_rb_tree_node* left		= NULL,
							_rb_tree_node* right	= NULL,
							bool last_node 			= false)
								: _data(data),_color(color), _parent(parent),
								  _left(left), _right(right), _last_node(last_node) {}
			
			// inline bool
			// operator< (_rb_tree_color& x, _rb_tree_color& y) { return x->_data < y->data; }
			// inline bool
			// operator== (_rb_tree_color& x, _rb_tree_color& y) { return x->_data == y->data; }
		};
// ----------------------------------------------------------------------------

// Supporting nested class to compare elements
		class value_compare {

			friend class map;
		
		protected:
			Compare _comp;
			value_compare(Compare c) : _comp(c) {}
			friend class map<Key, T, Compare, Alloc>;

		public:
			bool operator()(const value_type& x, const value_type& y) const {
				return _comp(x.first, y.first);
			}
		};
// ----------------------------------------------------------------------------
	
		typedef _rb_tree_node								node;
		typedef map_iterator<Key, T, _rb_tree_node>			iterator;
		typedef map_iterator<Key, T, _rb_tree_node>			const_iterator;
		typedef map_reverse_iterator<Key, T, _rb_tree_node>	reverse_iterator;
		typedef map_reverse_iterator<Key, T, _rb_tree_node>	const_reverse_iterator;

	private:
	
		node*			_root;
		key_compare		_compare;
		allocator_type	_alloc;
		size_t			_node_count;
		value_compare	_comp_val;
		node*			_end;
		node*			_rend;

// Supporting functions -------------------------------------------------------
		
		// _add_node(root, node) recursively searches for a place to insert a node
		void
		// node*
		_add_node (node* root, const value_type& new_data) {
			if (!root) {
				_insert_node(root, new_data);
				_end = new node(value_type(), _red_node, _root, NULL, NULL, true);
				_rend = new node(value_type(), _red_node, _root, NULL, NULL, true);
				_root->_left = _rend;
				_root->_right = _end;
				return;
			}
			if (root->_data.first == new_data.first) {
				return;
			} else if (_comp_val(new_data, root->_data) && root->_left ) {
				_add_node(root->_left, new_data);
			} else if (_comp_val(new_data, root->_data) && !root->_left) {
				_insert_node(root->_left, new_data);
			} else if (!_comp_val(new_data, root->_data) && root->_right) {
				_add_node(root->_right, new_data);
			} else if (!_comp_val(new_data, root->_data) && !root->_right) {
				_insert_node(root->_right, new_data);
			}
		}

		void
		_insert_node (node* root, const value_type& new_data) {
			if (!root) {
				_root = new _rb_tree_node(new_data, _black_node);
			} else {
				node* new_node = new _rb_tree_node(new_data, _red_node, root);
				if (_comp_val(new_node->_data, root->_data)) {
					root->_left = new_node; 
				} else {
					root->_right = new_node;
				}
			}
			_node_count++;
		}

		bool
		_is_end(node* current) { return current->right == _root; }

	public:

// Map constructors -----------------------------------------------------------

		explicit
		map (const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type())
				: _root(),
				  _compare(comp),
				  _alloc(alloc),
				  _node_count(),
				  _comp_val(comp),
				  _end(),
				  _rend() {}

		  template <typename InputIterator>
		map (InputIterator first,
			 InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type())
				: _root(),
				  _compare(comp),
				  _alloc(alloc),
				  _node_count(),
				  _comp_val(comp),
				  _end(),
				  _rend() {
				
				while (first != last) {
					_add_node(_root, *first);
					// _balance(current);
					++first;
				}
			}

		map (const map& x) {

			typename ft::map<Key, T>::iterator first = x.begin();
			while (first != x.end()) {
					_add_node(_root, first->ptr);
					// _balance(current);
					++first;
				}
		}

// Map destructor --------------------------------------------------------------

		~map () {
			// clear();
			// delete this->_head;
		}
	
// Map methods ---------------------------------------------------------------------

	//  Iterators -------------------------------

		iterator
		begin () NOEXCEPT			{ return iterator(_rend->_parent); }

		const_iterator
		begin () const NOEXCEPT		{ return iterator(_rend->parent); }

		iterator
		end () NOEXCEPT				{ return iterator(_end); }

		const_iterator
		end () const NOEXCEPT		{ return const_iterator(_end); }

		reverse_iterator
		rbegin () NOEXCEPT			{ return reverse_iterator(_end->_parent); }

		const_reverse_iterator
		rbegin () const NOEXCEPT 	{ return reverse_iterator(_end->_parent); }

		reverse_iterator
		rend () NOEXCEPT			{ return reverse_iterator(_rend); }

		const_reverse_iterator
		rend () const NOEXCEPT		{ return const_reverse_iterator(_rend); }

		// pair<iterator,bool>
		void
		insert (const value_type& val) {
			_add_node(_root, val);
		}

		iterator
		insert (iterator position, const value_type& val);

		  template <class InputIterator>
		void
		insert (InputIterator first, InputIterator last);


	// // Capacity ----------------------------

		bool
		empty () const NOEXCEPT		{ return _node_count == 0; }

		size_type
		size () const NOEXCEPT		{ return _node_count; }

	// 	size_type
	// 	max_size () const NOEXCEPT	{ return std::numeric_limits<size_type>::max() / sizeof(Map_node) / 2; }

	// // Element access -------------------------

	// 	reference
	// 	front () NOEXCEPT			{ return *(begin()); }

	// 	value_type
	// 	front () const NOEXCEPT		{ return *(this->begin()); }

	// 	reference
	// 	back () NOEXCEPT				{ return *(-- (this->end())); }

	// 	value_type
	// 	back () const NOEXCEPT		{ return *(-- (this->end())); }

	// // Modifiers ------------------------------

	// 	  template<typename InputIterator>
	// 	void
	// 	assign (InputIterator first, InputIterator last) {
	// 		typedef typename ft::is_integer_my<InputIterator>::type_my _Integral;
	// 		_assign(first, last, _Integral());
	// 	}

	// 	void
	// 	assign (size_type n, value_type val) {
	// 		_assign(n, val, ft::true_type_my());
	// 	}

	// 	void
	// 	push_front (value_type data) {
	// 		Map_node *temp = new Map_node(data, this->_head, this->_head->_next);
	// 		this->_head->_next = this->_head->_next->_prev = temp;
	// 		_Map_size++;
	// 	}

	// 	void
	// 	pop_front () NOEXCEPT { this->erase(this->begin()); }

	// 	void
	// 	push_back (value_type data) {
	// 		if (!_Map_size) {
	// 			Map_node *temp = new Map_node(data);
	// 			this->_head->_prev = this->_head->_next = temp;
	// 			temp->_prev = temp->_next = this->_head;
	// 		} else {
	// 			Map_node *temp = new Map_node(data, this->_head->_prev, this->_head);
	// 			this->_head->_prev->_next = temp;
	// 			this->_head->_prev = temp;
	// 		}
	// 		_Map_size++;
	// 	}

	// 	void
	// 	pop_back () NOEXCEPT { this->erase(iterator(this->_head->_prev)); }

	// 	iterator
	// 	insert (iterator position, value_type data) {
	// 		if (position == this->begin()) {
	// 			push_front(data);
	// 			return this->begin();
	// 		}

	// 		Map_node *temp = new Map_node(data);
	// 		_node_insert(position.ptr, temp);
	// 		_Map_size++;
	// 		return iterator(temp);
	// 	}

	// 	void
	// 	insert (iterator position, size_type n, value_type val) {
	// 		_insert(position, n, val, ft::true_type_my());
	// 	}
		
	// 	  template<typename InputIterator>
	// 	void
	// 	insert (iterator position, InputIterator first, InputIterator last) {
	// 		typedef typename ft::is_integer_my<InputIterator>::type_my _Integral;
	// 		_insert(position, first, last, _Integral());
	// 	}

	// 	iterator
	// 	erase (iterator position) {
	// 		if (position != this->end()) {
	// 			_cut(position);
	// 			iterator temp = position++;
	// 			if (temp == this->begin())
	// 				this->_head->_next = temp.ptr;
	// 			delete temp.ptr;
	// 			_Map_size -= _Map_size ? 1 : 0;
	// 		}
	// 		return position;
	// 	}

	// 	iterator
	// 	erase (iterator first, iterator last) {
	// 		while (first != last) {
	// 			first = erase(first);
	// 		}
	// 		return last;
	// 	}

	// 	void
	// 	swap (Map& x) {
	// 		Map_node* temp = this->_head;
	// 		this->_head = x._head;
	// 		x._head = temp;

	// 		size_type size = this->_Map_size;
	// 		_Map_size = x._Map_size;
	// 		x._Map_size = size;
	// 	}

	// 	void
	// 	resize (size_type new_size, value_type val = value_type()) {
	// 		if (new_size < this->_Map_size) {
	// 			iterator it = this->begin();
	// 			while (new_size--)
	// 				++it;
	// 			erase(it, this->end());
	// 		} else {
	// 			insert(this->end(), new_size - this->_Map_size, val);
	// 		}
	// 	}

	// 	void
	// 	clear () NOEXCEPT {
	// 		Map_node *temp;
	// 		while (this->_Map_size) {
	// 			temp = this->_head->_next;
	// 			delete this->_head;
	// 			this->_head = temp;
	// 			this->_Map_size--;
	// 		}
	// 		this->_head->_prev = this->_head->_next = this->_head;
	// 	}

	// // Operations -----------------------------

	// 	void
	// 	splice (iterator position, Map& x) {
	// 		while (x._Map_size--) {
	// 			iterator first = x.begin();
	// 			iterator temp = ++(x.begin());
	// 			_cut(first);
	// 			_node_insert(position.ptr, first.ptr);
	// 			first = temp;
	// 			_Map_size++;
	// 		}
	// 		x._head->_next = x._head->_prev = x._head;
	// 		x._Map_size = 0;
	// 	}

	// 	void
	// 	splice (iterator position, Map& x, iterator i) {
	// 		_cut(i);
	// 		_Map_size++;
	// 		x._Map_size--;
	// 		_node_insert(position.ptr, i.ptr);
	// 	}

	// 	void
	// 	splice (iterator position, Map& x, iterator first, iterator last) {
	// 		while (first != last) {
	// 			iterator temp = first;
	// 			++temp;
	// 			_cut(first);
	// 			_node_insert(position.ptr, first.ptr);
	// 			first = temp;
	// 			_Map_size++;
	// 			x._Map_size--;
	// 		}
	// 	}

	// 	void
	// 	remove (value_type val) {
	// 		iterator it = this->begin();
	// 		while (it != this->end()) {
	// 			iterator temp = it;
	// 			++it;
	// 			if (*temp == val) {
	// 				this->erase(temp);
	// 			}
	// 		}
	// 	}

	// 	  template<typename Compare>
	// 	void
	// 	remove_if (Compare comp) {
	// 		iterator it = this->begin();
	// 		while (it != this->end()) {
	// 			iterator temp = it;
	// 			++it;
	// 			if (comp(*temp)) {
	// 				this->erase(temp);
	// 			}
	// 		}
	// 	}


	// 	void
	// 	unique() {
	// 		iterator first = this->begin();
	// 		++first;
	// 		while (first != this->end()) {
	// 			if (first.ptr->_data == first.ptr->_prev->_data) {
	// 				iterator temp = first;
	// 				++temp;
	// 				_cut(first);
	// 				delete first.ptr;
	// 				_Map_size--;
	// 				first = temp;
	// 			} else {
	// 				++first;
	// 			}
	// 		}
	// 	}

	// 	  template<typename BinaryPredicate>
	// 	void
	// 	unique (BinaryPredicate binary_pred) {
	// 					iterator first = this->begin();
	// 		++first;
	// 		while (first != this->end()) {
	// 			if (binary_pred(first.ptr->_data, first.ptr->_prev->_data)) {
	// 				iterator temp = first;
	// 				++temp;
	// 				_cut(first);
	// 				delete first.ptr;
	// 				_Map_size--;
	// 				first = temp;
	// 			} else {
	// 				++first;
	// 			}
	// 		}
	// 	}

	// 	void
	// 	merge (Map& x) { this->merge(x, _compare); }

	// 	  template<typename Compare>
	// 	void
	// 	merge (Map& x, Compare comp) {
	// 		if (&x == this)
	// 			return;
	// 		iterator first1 = this->begin(), first2 = x.begin(),
	// 				  last1 = this->end(),	  last2 = x.end();
	// 		while (first1 != last1 && first2 != last2) {
	// 			if (comp(*first2, *first1)) {
	// 				iterator temp = first2;
	// 				temp++;
	// 				_node_insert(first1.ptr, first2.ptr);
	// 				first2 = temp;
	// 				this->_Map_size++;
	// 			}
	// 			else
	// 				++first1;
	// 		}
	// 		while (first2 != last2) {
	// 			iterator temp = first2;
	// 			temp++;
	// 			_node_insert(first1.ptr, first2.ptr);
	// 			first2 = temp;
	// 			this->_Map_size++;;
	// 		}
	// 		x._head->_next = x._head->_prev = x._head;
	// 		x._Map_size = 0;
	// 	}

	// 	void
	// 	sort() { this->sort(_compare); }

	// 	  template<typename Compare>
	// 	void
	// 	sort (Compare comp) {
	// 		for (iterator it = begin(); it != end(); ) {
	// 			iterator it_min;
	// 			it_min = it;
	// 			for (iterator itt = it; itt != end(); ++itt) {
	// 				if (comp(*itt, *it_min)) {
	// 					it_min = itt;
	// 				}
	// 			}
	// 			if (it_min != it) {
	// 				_cut(it_min);
	// 				_node_insert(it.ptr, it_min.ptr);
	// 			} else {
	// 				++it;
	// 			}
	// 		}
	// 	}

	// 	void
	// 	reverse () {
	// 		iterator first = this->_head;
	// 		size_type size = this->_Map_size;
	// 		while (size--) {
	// 			iterator last = -- (this->end());
	// 			_cut(last);
				
	// 			first.ptr->_next->_prev = last.ptr;
	// 			last.ptr->_next = first.ptr->_next;
	// 			first.ptr->_next = last.ptr;
	// 			last.ptr->_prev = first.ptr;
	// 			++first;
	// 		}
	// 	}

// Friend functions -----------------------------------------------------------
		//   template<typename _T, typename _Alloc>
		// friend bool
		// operator== (const Map<_T, _Alloc>&, const Map<_T, _Alloc>&);

		//   template<typename _T, typename _Alloc>
		// friend  bool
		// operator<  (const Map<_T, _Alloc>&, const Map<_T, _Alloc>&);

		//   template<typename _T, typename _Alloc>
		// friend void
		// swap (Map<_T, _Alloc>&, Map<_T, _Alloc>&);

	};

/************************************ end of Map class ***********************************/

// Friend functions definitions -----------------------------------------------

	//   template<typename T, typename Alloc>
	// inline bool
	// operator== (const Map<T,Alloc>& lhs, const Map<T,Alloc>& rhs) {
		
	// 	if (lhs.size() != rhs.size()) return false;
		
	// 	typename ft::Map<T>::iterator first1 = lhs.begin();
	// 	typename ft::Map<T>::iterator first2 = rhs.begin();
		
	// 	while (first1 != lhs.end()) {
	// 		if (*first1 != *first2)
	// 			return false;
	// 		++first1;
	// 		++first2;
	// 	}
	// 	return true;
	// }

	//   template<typename T, typename Alloc>
	// inline bool
	// operator!= (const Map<T,Alloc>& lhs, const Map<T,Alloc>& rhs) {
	// 	return !(lhs == rhs);
	// }

	//   template<typename T, typename Alloc>
	// inline bool
	// operator<  (const Map<T,Alloc>& lhs, const Map<T,Alloc>& rhs) {

	// 	typename ft::Map<T>::iterator first1 = lhs.begin();
	// 	typename ft::Map<T>::iterator first2 = rhs.begin();
		
	// 	while (first1 != lhs.end() && first2 != rhs.end()) {
	// 		if (*first1 < *first2)
	// 			return true;
	// 		if (*first1 > *first2)
	// 			return false;
	// 		++first1;
	// 		++first2;
	// 	}
	// 	if (lhs.size() > rhs.size() ||
	// 		(lhs.size() == rhs.size() && *(--first1) >= *(--first2)))
	// 		return false;
	// 	return true;
	// }

	//   template<typename T, typename Alloc>
	// inline bool
	// operator<= (const Map<T,Alloc>& lhs, const Map<T,Alloc>& rhs) {
	// 	return !(rhs < lhs);
	// }

	//   template<typename T, typename Alloc>
	// inline bool
	// operator>  (const Map<T,Alloc>& lhs, const Map<T,Alloc>& rhs) {
	// 	return rhs < lhs;
	// }

	//   template<typename T, typename Alloc>
	// inline bool
	// operator>= (const Map<T,Alloc>& lhs, const Map<T,Alloc>& rhs) {
	// 	return !(lhs < rhs);
	// }

	//   template<typename T, typename Alloc>
	// void
	// swap (Map<T,Alloc>& x, Map<T,Alloc>& y) {
	// 	x.swap(y);
	// }
}
