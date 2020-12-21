#pragma once

#include <limits>
#include <memory>
#include <cstring>
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
		enum _rb_tree_color { _BLACK = false, _RED = true };
// ----------------------------------------------------------------------------

// Supporting structure tree node
		struct _rb_tree_node {

			value_type				_data;
			_rb_tree_color			_color;
			_rb_tree_node*			_parent;
			_rb_tree_node*			_left;
			_rb_tree_node*			_right;
			bool					_last_node;
			bool					_null;

			_rb_tree_node (value_type data			= value_type(),
							_rb_tree_color color	= _RED,
							_rb_tree_node* parent	= NULL,
							_rb_tree_node* left		= NULL,
							_rb_tree_node* right	= NULL,
							bool last_node 			= false,
							bool null	 			= false)
								: _data(data),_color(color), _parent(parent),
								  _left(left), _right(right), _last_node(last_node), _null(null) {}
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
		node*			_null;

// Supporting functions -------------------------------------------------------
		
		bool
		_is_key_equal (const value_type& k1, const value_type& k2) const {
			return !_comp_val(k1, k2) &&
				   !_comp_val(k2, k1);
		}

		// _add_node(root, node) recursively searches for a place to insert a node
		void
		// node*
		_add_node (node* root, const value_type& new_data) {
		
			if (!root) {
				_insert_node(root, new_data);
				_end->_parent = _root;
				_rend->_parent = _root;
				_root->_left = _rend;
				_root->_right = _end;
				return;
			}
			while ((root->_left != _null
					&& !root->_left->_last_node
					&& _comp_val(new_data, root->_data))
				|| (root->_right != _null
					&& !root->_right->_last_node
					&& !_comp_val(new_data, root->_data))) {
				
				if (_is_key_equal(new_data, root->_data))
					return;

				if (_comp_val(new_data, root->_data))
					root = root->_left;
				else
					root = root->_right;
			}
			if (_is_key_equal(new_data, root->_data))
				return;
			_insert_node(root, new_data);
		}

		node*
		_insert_node (node* root, const value_type& new_data) {
			
			node* res;

			if (!root) {
				_root = new _rb_tree_node(new_data, _BLACK, _null, _rend, _end);
				res = _root;
			} else if (_is_key_equal(new_data, root->_data)) {
				return (root);
			} else if (_comp_val(new_data, root->_data)) {			// new_data < current root data
				if (root->_left != _null) {									// root->_left == rend
					root->_left = new _rb_tree_node(new_data, _RED, root, _rend, _null);
					_rend->_parent = root->_left;
					res = root->_left;
				} else {
					root->_left = new _rb_tree_node(new_data, _RED, root, _null, _null);
					res = root->_left;
				}
			} else {												// new_data > current root data
				if (root->_right != _null) {									// root->_right == end
					root->_right = new _rb_tree_node(new_data, _RED, root, _null, _end);
					_end->_parent = root->_right;
					res = root->_right;
				} else {
					root->_right = new _rb_tree_node(new_data, _RED, root, _null, _null);
					res = root->_right;
				}
			}
			_balance(res);
			_node_count++;
			return (res);
		}

		node*
		_find (const key_type& k) const {

			iterator it = begin();
			value_type temp(k, 0);
			while (it != end()) {
				if (_is_key_equal(*it, temp))
					return it.base();
				++it;
			}
			return it.base();
		}

		void
		_erase (iterator position) {
			(void)position;
			_delete_node(position.base());
			_node_count--;
		}

		void
		_clear () { erase(begin(), end()); }

		void
		_print (node* p, int indent = 0) {
			if(p != _null) {
				if (indent)
					std::cout << std::setw(indent) << ' ';
				std::cout << (p->_color ? "\033[1;31m" : "") <<
					"[" << p->_data.first << " "	 << p->_data.second << "]" <<
					"\033[0;0m" << "\n ";
				if(p->_left && p->_left != _rend)
					_print(p->_left, indent + 5);
				if(p->_right && p->_right != _end)
					_print(p->_right, indent + 5);
			}
		}

		void
		_set_rend(node* n) {
			while (n->_left != _null)
				n = n->_left;
			if (n != _rend) {
				n->_left = _rend;
				_rend->_parent = n;
			}
		}

		void
		_set_end(node* n) {
			while (n->_right != _null)
				n = n->_right;
			if (n != _end) {
				n->_right = _end;
				_end->_parent = n;
			}
		}

		void
		_print_tree () { std::cout << "\n"; _print(_root); std::cout << "\n"; }

	// Balancing ----------------------------------------------------------------

		node*
		_grand_parent (node* n) {
			if (n != _null && n->_parent != _null)
				return n->_parent->_parent;
			return _null;
		}

		node*
		_uncle (node* n) {
			node* g = _grand_parent(n);
			if (g == _null)
				return _null;			// No grandparent means no uncle
			if (n->_parent == g->_left)
				return g->_right;
			return g->_left;
		}

		void
		_rotate_left (node *n) {

			node *pivot = n->_right;
			
			pivot->_parent = n->_parent; // pivot может стать корнем дерева
			if (n->_parent != _null) {
				if (n->_parent->_left == n)
					n->_parent->_left = pivot;
				else
					n->_parent->_right = pivot;
			} else {
				_root = pivot;
			}
			n->_right = pivot->_left;
			if (pivot->_left != _null)
				pivot->_left->_parent = n;

			n->_parent = pivot;
			pivot->_left = n;
		}

		void
		_rotate_right (node *n) {

			node *pivot = n->_left;
			
			pivot->_parent = n->_parent; /* при этом, возможно, pivot становится корнем дерева */
			if (n->_parent != _null) {
				if (n->_parent->_left == n)
					n->_parent->_left = pivot;
				else
					n->_parent->_right = pivot;
			} else {
				_root = pivot;
			}
			n->_left = pivot->_right;
			if (pivot->_right != _null)
				pivot->_right->_parent = n;

			n->_parent = pivot;
			pivot->_right = n;
		}

		void
		_balance (node *n) { 
			_insert_case1(n);
		}

		void
		_insert_case1 (node *n) {

			if (n->_parent == _null)
				n->_color = _BLACK;
			else
				_insert_case2(n);
		}

		void
		_insert_case2 (node *n) {

			if (n->_parent->_color == _BLACK)
				return; 				// Tree is still valid
			_insert_case3(n);
		}


		void
		_insert_case3 (node* n) {
			node* u = _uncle(n);
			node* g;

			if (u != _null && !u->_last_node && u->_color == _RED) {		 // && (n->_parent->_color == _RED) проверяется в insert_case2
				n->_parent->_color = _BLACK;
				u->_color = _BLACK;
				g = _grand_parent(n);
				g->_color = _RED;
				_insert_case1(g);
			} else {
				_insert_case4(n);
			}
		}

		void
		_insert_case4 (node* n) {

			node* g = _grand_parent(n);
 
			if ((n == n->_parent->_right) && (n->_parent == g->_left)) {
				_rotate_left(n->_parent);
				n = n->_left;
			} else if ((n == n->_parent->_left) && (n->_parent == g->_right)) {
				_rotate_right(n->_parent);
				n = n->_right;
			}
			_insert_case5(n);
		}

		void
		_insert_case5 (node* n) {
			node* g = _grand_parent(n);

			n->_parent->_color = _BLACK;
			g->_color = _RED;
			if ((n == n->_parent->_left) && (n->_parent == g->_left)) {
				_rotate_right(g);
			} else { 				// (n == n->_parent->_right) && (n->_parent == g->_right)
				_rotate_left(g);
			}
		}

	// Deleting ----------------------------------------------------------------

		void 
		_replace_node(node* n, node* child) {
			child->_parent = n->_parent;
			if (n == n->_parent->_left) {
				n->_parent->_left = child;
			} else {
				n->_parent->_right = child;
			}
			child->_left = n->_left;
			child->_right = n->_right;

			child->_left->_parent = child;
			child->_right->_parent = child;

			_rb_tree_color temp = child->_color;
			child->_color = n->_color;
			n->_color = temp;
			if (n == _root)
				_root = child;
		}

		void _delete_balance(node* x) {

			while (x != _root && x->_color == _BLACK) {
				if (x == x->_parent->_left) {
					node *w = x->_parent->_right;
					if (w->_color == _RED) {
						w->_color = _BLACK;
						x->_parent->_color = _RED;
						_rotate_left (x->_parent);
						w = x->_parent->_right;
					}
					if (w->_left->_color == _BLACK && w->_right->_color == _BLACK) {
						w->_color = _RED;
						x = x->_parent;
					} else {
						if (w->_right->_color == _BLACK) {
							w->_left->_color = _BLACK;
							w->_color = _RED;
							_rotate_right (w);
							w = x->_parent->_right;
						}
						w->_color = x->_parent->_color;
						x->_parent->_color = _BLACK;
						w->_right->_color = _BLACK;
						_rotate_left (x->_parent);
						x = _root;
					}
				} else {
					node *w = x->_parent->_left;
					if (w->_color == _RED) {
						w->_color = _BLACK;
						x->_parent->_color = _RED;
						_rotate_right (x->_parent);
						w = x->_parent->_left;
					}
					if (w->_right->_color == _BLACK && w->_left->_color == _BLACK) {
						w->_color = _RED;
						x = x->_parent;
					} else {
						if (w->_left->_color == _BLACK) {
							w->_right->_color = _BLACK;
							w->_color = _RED;
							_rotate_left (w);
							w = x->_parent->_left;
						}
						w->_color = x->_parent->_color;
						x->_parent->_color = _BLACK;
						w->_left->_color = _BLACK;
						_rotate_right (x->_parent);
						x = _root;
					}
				}
			}
			x->_color = _BLACK;
		}

		void _delete_node(node* n) {
			node* child;
			node* child_child;

			if (!n || n == _null) return;

			if (n->_left == _null || (n->_left->_last_node)
			 || n->_right == _null || (n->_right->_last_node)) {		// n has a _null node as a child
				child = n;
			} else {
				child = n->_right;
				while (child->_left != _null)
					child = child->_left;
			}

			if (child->_left != _null)							/* child_child is child's only child */
				child_child = child->_left;
			else
				child_child = child->_right;

			child_child->_parent = child->_parent;
			if (child->_parent != _null)
				if (child == child->_parent->_left)
					child->_parent->_left = child_child;
				else
					child->_parent->_right = child_child;
			else
				_root = child_child;

			if (child != n)
				_replace_node(n, child);


			if (n->_color == _BLACK)
				_delete_balance (child_child);
			_set_end(_root);
			_set_rend(_root);
			delete n;
		}

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
				  _rend() {

			_end = new node(value_type(), _BLACK, NULL, NULL, NULL, true);
			_rend = new node(value_type(), _BLACK, NULL, NULL, NULL, true);
			_null = new node(value_type(), _BLACK, NULL, NULL, NULL, false, true);
		}

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
				
				_null = new node(value_type(), _BLACK, NULL, NULL, NULL, false, true);
				_end  = new node(value_type(), _BLACK, _null, _null, _null, true);
				_rend = new node(value_type(), _BLACK, _null, _null, _null, true);

				while (first != last) {
					_add_node(_root, *first);
					++first;
				}
			}

		// map (const map& x) {

		// 	typename ft::map<Key, T>::iterator first = x.begin();
	
		// 	while (first != x.end()) {
		// 			_add_node(_root, first->ptr);
		// 			// _balance(current);
		// 			++first;
		// 		}
		// }

// Map destructor --------------------------------------------------------------

		// ~map () { _clear(); }
		~map () {
			// clear();
			delete _end;
			delete _rend;
			delete _null;
		}
	
// Map methods ---------------------------------------------------------------------

	//  Iterators -------------------------------

		iterator
		begin () NOEXCEPT			{ return iterator(_rend->_parent); }

		const_iterator
		begin () const NOEXCEPT		{ return iterator(_rend->_parent); }

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

		iterator
		find (const key_type& k)		{ return iterator(_find(k)); }

		const_iterator
		find (const key_type& k) const	{ return const_iterator(_find(k)); }

		size_type
		count (const key_type& k) const	{ return (_find(k) == _end ? 0u : 1u); }

		pair<iterator,bool>
		insert (const value_type& val) {
			size_t old_size = size();
			_add_node(_root, val);
			return std::make_pair(find(val.first), old_size != size());
		}

		iterator
		insert (iterator position, const value_type& val) {
			_add_node(position.ptr, val);
			return find(val.first);
		}

		  template <class InputIterator>
		void
		insert (InputIterator first, InputIterator last) {
			while (first != last) {
				_add_node(_root, *first);
				// _balance(current);
				++first;
			}
		}

		void
		erase (iterator position) { _erase(position); }

		size_type
		erase (const key_type& k) { 
			iterator temp = find(k);
			if (temp != end()) {
				_erase(temp);
				return 1u;
			}
			return 0u;
		}

		void
		erase (iterator first, iterator last) {
			while (first != last) {
				erase(first);
				++first;
			}
		}



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

	// 	  template<typename BinaryP_REDicate>
	// 	void
	// 	unique (BinaryP_REDicate binary_p_RED) {
	// 					iterator first = this->begin();
	// 		++first;
	// 		while (first != this->end()) {
	// 			if (binary_p_RED(first.ptr->_data, first.ptr->_prev->_data)) {
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

		  template<typename U>
		friend void
		print_tree(U& tree);
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
