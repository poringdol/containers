#pragma once

#include <limits>
#include <memory>
#include "stack.hpp"
#include "set_iterator.hpp"


namespace ft {

/********************************** Set class ***************************************/

	  template <typename T,
				typename Compare = std::less<T>,
				typename Alloc = std::allocator<T> >
	class set {

	public:

		typedef T											key_type;
		typedef T											value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef T&											reference;
		typedef const T&									const_reference;
		typedef T*											pointer;
		typedef const T*									const_pointer;
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;

// ----------------------------------------------------------------------------

// Enum for coloring nodes
		enum _rb_tree_color { _BLACK = false, _RED = true };
// ----------------------------------------------------------------------------

// Supporting structure tree_node
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

			friend class set;
		
		protected:
			Compare _comp;
			value_compare(Compare c) : _comp(c) {}
			friend class set<T, Compare, Alloc>;

		public:
			typedef bool	result_type;
			typedef			value_type first_argument_type;
			typedef			value_type second_argument_type;

			bool operator()(const value_type& x, const value_type& y) const {
				return _comp(x, y);
			}
		};
// ----------------------------------------------------------------------------
	
		typedef _rb_tree_node							node;
		typedef set_iterator<T, _rb_tree_node>			iterator;
		typedef set_iterator<T, _rb_tree_node>			const_iterator;
		typedef set_reverse_iterator<T, _rb_tree_node>	reverse_iterator;
		typedef set_reverse_iterator<T, _rb_tree_node>	const_reverse_iterator;

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

				node*
		_add_node (node* root, const value_type& new_data) {
		
			iterator it = _find(new_data);
			if (it != end())
				return it.base();

			root = _root;

			if (!root) {
				_insert_node(root, new_data);
				_end->_parent = _root;
				_rend->_parent = _root;
				_root->_left = _rend;
				_root->_right = _end;
				return _root;
			}
			while (root->_parent != _null 
					&& _comp_val(new_data, root->_parent->_data)) {
				root = root->_parent;
			}
			while ((root->_left != _null
					&& !root->_left->_last_node
					&& _comp_val(new_data, root->_data))
				|| (root->_right != _null
					&& !root->_right->_last_node
					&& !_comp_val(new_data, root->_data))) {

				if (_comp_val(new_data, root->_data))
					root = root->_left;
				else
					root = root->_right;
			}
			return _insert_node(root, new_data);
		}

		node*
		_insert_node (node* root, const value_type& new_data) {
			
			node* res;

			if (!root) {
				_root = new _rb_tree_node(new_data, _BLACK, _null, _rend, _end);
				res = _root;
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
			while (it != end()) {
				if (_is_key_equal(*it, k))
					return it.base();
				++it;
			}
			return it.base();
		}

		void
		_erase (iterator position) {
			_delete_node(position.base());
		}

		void
		_clear () { erase(begin(), end()); }

		void
		_print (node* p, int indent = 0) {
			if(p != _null) {
				if (indent)
					std::cout << std::setw(indent) << ' ';
				std::cout << (p->_color ? "\033[1;31m" : "") <<
					"[" << p->_data.first << " " << p->_data.second << "]" <<
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
		_set_empty_tree() {
			_end->_parent = _rend;
			_rend->_parent = _end;
			_root = NULL;
		}

		void
		_print_tree () { std::cout << "\n"; _print(_root); std::cout << "\n"; }

	// Balancing ----------------------------------------------------------------

		node*
		_grandparent (node* n) {
			if (n != _null && n->_parent != _null)
				return n->_parent->_parent;
			return _null;
		}

		node*
		_uncle (node* n) {
			node* g = _grandparent(n);
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
				g = _grandparent(n);
				g->_color = _RED;
				_insert_case1(g);
			} else {
				_insert_case4(n);
			}
		}

		void
		_insert_case4 (node* n) {

			node* g = _grandparent(n);
 
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
			node* g = _grandparent(n);

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

		void
		_delete_balance(node* x) {

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

		void
		_delete_node(node* n) {
			node* child;
			node* grandchild;

			if (!n || n == _null || !_node_count) return;

			if (n->_left == _null || (n->_left->_last_node)
			 || n->_right == _null || (n->_right->_last_node)) {		// n has a _null node as a child
				child = n;
			} else {
				child = n->_right;
				while (child->_left != _null)
					child = child->_left;
			}

			if (child->_left != _null && !child->_left->_last_node)		// grandchild is child's only child
				grandchild = child->_left;
			else
				grandchild = child->_right;

			grandchild->_parent = child->_parent;
			if (child->_parent != _null)
				if (child == child->_parent->_left)
					child->_parent->_left = grandchild;
				else
					child->_parent->_right = grandchild;
			else
				_root = grandchild;

			if (child != n)
				_replace_node(n, child);

			if (n->_color == _BLACK)
				_delete_balance (grandchild);
			_set_end(_root);
			_set_rend(_root);
			delete n;
			_node_count--;
			if (!_node_count)
				_set_empty_tree();
		}

	public:

// Set constructors -----------------------------------------------------------

		explicit
		set (const key_compare& comp = key_compare(),
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
			_set_empty_tree();
		}

		  template <typename InputIterator>
		set (InputIterator first,
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
				_set_empty_tree();

				insert(first, last);
			}

		set (const set& x)
			  : _root(),
				_compare(x._compare),
				_alloc(x._alloc),
				_node_count(),
				_comp_val(x._comp_val),
				_end(),
				_rend() {

			_null = new node(value_type(), _BLACK, NULL, NULL, NULL, false, true);
			_end  = new node(value_type(), _BLACK, _null, _null, _null, true);
			_rend = new node(value_type(), _BLACK, _null, _null, _null, true);
			_set_empty_tree();

			insert(x.begin(), x.end());
		}

// Set destructor --------------------------------------------------------------

		~set () {
			_clear();
			delete _end;
			delete _rend;
			delete _null;
		}

// Set operators -------------------------------------------------------------------

		set&
		operator= (const set& x) {
			insert(x.begin(), x.end());
			return *this;
		}

// Set methods ---------------------------------------------------------------------

	//  Iterators -------------------------------

		iterator
		begin () throw()				{ return iterator(_rend->_parent); }

		const_iterator
		begin () const throw()			{ return iterator(_rend->_parent); }

		iterator
		end () throw()					{ return iterator(_end); }

		const_iterator
		end () const throw()			{ return const_iterator(_end); }	

		reverse_iterator
		rbegin () throw()				{ return reverse_iterator(_end->_parent); }

		const_reverse_iterator
		rbegin () const throw() 		{ return reverse_iterator(_end->_parent); }

		reverse_iterator
		rend () throw()				{ return reverse_iterator(_rend); }

		const_reverse_iterator
		rend () const throw()			{ return const_reverse_iterator(_rend); }

	//  Capacity --------------------------------

		bool
		empty () const throw()			{ return _node_count == 0u; }

		size_type
		size () const throw()			{ return _node_count; }

		size_type
		max_size () const throw()		{ return std::numeric_limits<long>::max() / sizeof(_rb_tree_node); }

	// Modifiers --------------------------------

		std::pair<iterator,bool>
		insert (const value_type& val) {

			size_t old_size = size();
			_add_node(_root, val);
			return std::make_pair(find(val), old_size != size());
		}

		iterator
		insert (iterator position, const value_type& val) {
			
			return _add_node(position.ptr, val);
		}

		  template <typename InputIterator>
		void
		insert (InputIterator first, InputIterator last) {
			
			while (first != last) {
				_add_node(_root, *first);
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
			
			ft::stack<node*> store;
			while (first != last) {
				store.push(first.base());
				++first;
			}
			while (!store.empty()) {
				_erase(store.top());
				store.pop();
			}
		}

		void
		swap (set& x) {

			node*			root = x._root;
			key_compare		compare = x._compare;
			allocator_type	alloc = x._alloc;
			size_t			node_count = x._node_count;
			value_compare	comp_val = x._comp_val;
			node*			end = x._end;
			node*			rend = x._rend;
			node*			null = x._null;
			
			x._root = _root;
			x._compare = _compare;
			x._alloc = _alloc;
			x._node_count = _node_count;
			x._comp_val = _comp_val;
			x._end = _end;
			x._rend = _rend;
			x._null = _null;

			_root = root;
			_compare = compare;
			_alloc = alloc;
			_node_count = node_count;
			_comp_val = comp_val;
			_end = end;
			_rend = rend;
			_null = null;
		}

		void
		clear () throw() { _clear(); }

	// Observers --------------------------------

		key_compare
		key_comp() const				{ return _compare; }
	
		value_compare
		value_comp() const				{ return _comp_val; }

	// Operations -------------------------------

		iterator
		find (const key_type& k)		{ return iterator(_find(k)); }

		const_iterator
		find (const key_type& k) const	{ return const_iterator(_find(k)); }

		size_type
		count (const key_type& k) const	{ return (_find(k) == _end ? 0u : 1u); }

		iterator
		lower_bound (const key_type& k) { 
			
			iterator it = begin();

			while (it != end()) {
				if (_is_key_equal(*it, k) || _comp_val(k, it.base()->_data))
					return it;
				++it;
			}
			return it;
		}

		const_iterator
		lower_bound (const key_type& k) const {

			const_iterator it = begin();
			
			while (it != end()) {
				if (_is_key_equal(*it, k) || _comp_val(k, it.base()->data))
					return it;
				++it;
			}
			return it;
		}

		iterator
		upper_bound (const key_type& k) {

			iterator it = begin();
			
			while (it != end()) {
				if (_comp_val(k, *it))
					return it;
				++it;
			}
			return it;
		}

		const_iterator
		upper_bound (const key_type& k) const {
			
			const_iterator it = begin();
			
			while (it != end()) {
				if (_comp_val(k, *it))
					return it;
				++it;
			}
			return it;
		}

		std::pair<iterator, iterator>
		equal_range (const key_type& k) {

			iterator res = lower_bound(k);
			return make_pair(res, res);
		}

		std::pair<const_iterator, const_iterator>
		equal_range (const key_type& k) const {

			const_iterator res = lower_bound(k);
			return make_pair(res, res);
		}

// Friend functions -----------------------------------------------------------
		  template <typename _T, typename _Compare, typename _Alloc>
		friend bool
		operator== (const set<_T,_Compare,_Alloc>&, const set<_T,_Compare,_Alloc>&);

		  template <typename _T, typename _Compare, typename _Alloc>
		friend  bool
		operator<  (const set<_T,_Compare,_Alloc>&, const set<_T,_Compare,_Alloc>&);

		  template <typename _T, typename _Compare, typename _Alloc>
  		void swap (set<_T,_Compare,_Alloc>& x, set<_T,_Compare,_Alloc>& y);
	};

/************************************ end of Set class ***********************************/

// Friend functions definitions -----------------------------------------------

	 template <typename T, typename Compare, typename Alloc>
	bool
	operator== (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y) {
		
		if (x.size() != y.size()) return false;
		
		typename ft::set<T>::iterator first1 = x.begin();
		typename ft::set<T>::iterator first2 = y.begin();
		
		while (first1 != x.end()) {
			if (*first1 != *first2)
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	 template <typename T, typename Compare, typename Alloc>
	bool
	operator!= (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y) {
		return !(x == y);
	}

	 template <typename T, typename Compare, typename Alloc>
	bool
	operator<  (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y) {

		typename ft::set<T>::iterator first1 = x.begin();
		typename ft::set<T>::iterator first2 = y.begin();
		
		while (first1 != x.end() && first2 != y.end()) {
			if (*first1 < *first2)
				return true;
			if (*first1 > *first2)
				return false;
			++first1;
			++first2;
		}
		if (x.size() > y.size() ||
			(x.size() == y.size() && *(--first1) >= *(--first2)))
			return false;
		return true;
	}

	 template <typename T, typename Compare, typename Alloc>
	bool
	operator<= (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y) {
		return !(y < x);
	}

	 template <typename T, typename Compare, typename Alloc>
	bool
	operator>  (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y) {
		return y < x;
	}

	 template <typename T, typename Compare, typename Alloc>
	bool
	operator>= (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y) {
		return !(x < y);
	}

	  template <typename _T, typename _Compare, typename _Alloc>
	void swap (set<_T,_Compare,_Alloc>& x, set<_T,_Compare,_Alloc>& y) {
		x.swap(y);
	}
}
