#pragma once

#include <iostream>
#include <iomanip>
#include <limits>
#include <cstddef>
#include "stack.hpp"
#include "multimap_iterator.hpp"


namespace ft {

/********************************** Multimap class ***************************************/

	  template <typename Key,
			  typename T,
			  typename Compare = std::less<Key>,
			  typename Alloc = std::allocator<std::pair<const Key, T> > >
	class multimap {

	public:

		typedef Key						key_type;
		typedef T						mapped_type;
		typedef std::pair<const Key, T>	value_type;
		typedef Compare					key_compare;
		typedef Alloc					allocator_type;
		typedef T&						reference;
		typedef const T&				const_reference;
		typedef T*						pointer;
		typedef const T*				const_pointer;
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;

// ----------------------------------------------------------------------------

// Supporting structure tree_node
		struct _tree_node {

			value_type	_data;
			_tree_node*	_parent;
			_tree_node*	_left;
			_tree_node*	_right;
			bool		_last_node;
			bool		_null;

			_tree_node (value_type data		= value_type(),
						_tree_node* parent	= NULL,
						_tree_node* left	= NULL,
						_tree_node* right	= NULL,
						bool last_node 		= false,
						bool null	 		= false)
							: _data(data), _parent(parent),
							  _left(left), _right(right),
							  _last_node(last_node), _null(null) {}
		};
// ----------------------------------------------------------------------------

// Supporting nested class to compare elements
		class value_compare {

			friend class multimap;
		
		protected:
			Compare _comp;
			value_compare(Compare c) : _comp(c) {}
			friend class multimap<Key, T, Compare, Alloc>;

		public:
			typedef bool	result_type;
			typedef			value_type first_argument_type;
			typedef			value_type second_argument_type;

			bool operator()(const value_type& x, const value_type& y) const {
				return _comp(x.first, y.first);
			}
		};
// ----------------------------------------------------------------------------
	
		typedef _tree_node										node;
		typedef multimap_iterator<Key, T, _tree_node>			iterator;
		typedef multimap_iterator<Key, T, _tree_node>			const_iterator;
		typedef multimap_reverse_iterator<Key, T, _tree_node>	reverse_iterator;
		typedef multimap_reverse_iterator<Key, T, _tree_node>	const_reverse_iterator;

	private:
	
		node*			_root;
		key_compare		_compare;
		allocator_type	_alloc;
		size_t			_node_count;
		value_compare	_comp_val;
		node*			_end;
		node*			_rend;
		node*			_null;

// // Supporting functions -------------------------------------------------------
		
		bool
		_is_key_equal (const value_type& k1, const value_type& k2) const {
			return !_comp_val(k1, k2) &&
				   !_comp_val(k2, k1);
		}

		node*
		_add_node (node* root, const value_type& new_data) {
		
			if (!root) {
				_insert_node(root, new_data);
				_end->_parent = _root;
				_rend->_parent = _root;
				_root->_left = _rend;
				_root->_right = _end;
				return _root;
			}
			root = _root;
			
			while ((root->_left != _null
					&& !root->_left->_last_node
					&& _comp_val(new_data, root->_data))
				|| (root->_right != _null
					&& !root->_right->_last_node
					&& (!_comp_val(new_data, root->_data)
						|| _is_key_equal(new_data, root->_data)))) {

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
				_root = new _tree_node(new_data, _null, _rend, _end);
				res = _root;
			} else if (_comp_val(new_data, root->_data)) {			// new_data < current root data
				if (root->_left != _null) {									// root->_left == rend
					root->_left = new _tree_node(new_data, root, _rend, _null);
					_rend->_parent = root->_left;
					res = root->_left;
				} else {
					root->_left = new _tree_node(new_data, root, _null, _null);
					res = root->_left;
				}
			} else {												// new_data >= current root data
				if (root->_right != _null) {									// root->_right == end
					root->_right = new _tree_node(new_data, root, _null, _end);
					_end->_parent = root->_right;
					res = root->_right;
				} else {
					root->_right = new _tree_node(new_data, root, _null, _null);
					res = root->_right;
				}
			}
			_node_count++;
			return (res);
		}

		node*
		_find (const key_type& k) const {

			iterator it = begin();
			value_type temp(k, T());
			while (it != end()) {
				if (_is_key_equal(*it, temp))
					return it.base();
				++it;
			}
			return it.base();
		}

		void
		_erase (iterator position) {

			node* ptr = position.base();

			if (ptr->_left->_last_node && ptr->_right->_last_node)
				_set_empty_map();

			else if (ptr->_left->_last_node || ptr->_right->_last_node)
			{
				if (ptr->_left->_last_node)
				{
					if (ptr->_right == _null)
					{
						ptr->_parent->_left = _rend;
						_rend->_parent = ptr->_parent;
					}
					else
					{
						ptr->_parent->_left = ptr->_right;
						ptr->_right->_parent = ptr->_parent;

						node* tmp = ptr->_right;
						while (tmp->_left != _null)
							tmp = tmp->_left;
						tmp->_left = _rend;
						_rend->_parent = tmp;
					}
				}
				if (ptr->_right->_last_node)
				{
					if (ptr->_left == _null)
					{
						ptr->_parent->_right = _end;
						_end->_parent = ptr->_parent;
					}
					else
					{
						ptr->_parent->_right = ptr->_left;
						ptr->_left->_parent = ptr->_parent;

						node* tmp = ptr->_left;
						while (tmp->_right != _null)
							tmp = tmp->_right;
						tmp->_right = _end;
						_end->_parent = tmp;
					}
				}
			}
			else if (ptr->_left == _null &&
				ptr->_right == _null)
			{
				if (ptr == ptr->_parent->_left)
					ptr->_parent->_left = _null;
				else
					ptr->_parent->_right = _null;
			}
			else if (ptr->_left == _null ||
					ptr->_right == _null)
			{
				node* tmp = (ptr->_left != _null) ? ptr->_left : ptr->_right;

				(ptr == ptr->_parent->_left) ? ptr->_parent->_left = tmp : ptr->_parent->_right = tmp;
				tmp->_parent = ptr->_parent;
			}
			else
			{
				node* tmp = ptr->_left;
				if (tmp->_right == _null)
				{
					tmp->_parent = ptr->_parent;
					tmp->_right = ptr->_right;
					ptr->_right->_parent = tmp;

					(ptr == ptr->_parent->_left) ? ptr->_parent->_left = tmp : ptr->_parent->_right = tmp;
				}
				else
				{
					while (tmp->_right != _null)
						tmp = tmp->_right;

					(ptr == ptr->_parent->_left) ? ptr->_parent->_left = tmp : ptr->_parent->_right = tmp;

					if (tmp == ptr->_left) {

						tmp->_parent = ptr->_parent;
						tmp->_right = ptr->_right;
						ptr->_right->_parent = tmp;
					}

					else {
						tmp->_parent->_right = tmp->_left;
						tmp->_left->_parent = tmp->_parent;

						ptr->_left->_parent = ptr->_right->_parent = tmp;

						tmp->_parent = ptr->_parent;
						tmp->_left = ptr->_left;
						tmp->_right = ptr->_right;
					}
				}
			}
			_node_count--;
			delete ptr;
		}

		void
		_clear () { erase(begin(), end()); }

		void
		_print (node* p, int indent = 0) {
			if(p != _null) {
				if (indent)
					std::cout << std::setw(indent) << ' ';
				std::cout << "[" << p->_data.first << " " << p->_data.second << "]" << "\n ";
				if(p->_left && p->_left != _rend)
					_print(p->_left, indent + 5);
				if(p->_right && p->_right != _end)
					_print(p->_right, indent + 5);
			}
		}

		void
		_set_empty_map() {
			_end->_parent = _rend;
			_rend->_parent = _end;
			_root = NULL;
		}


	public:

		void
		_print_tree () { std::cout << "\n"; _print(_root); std::cout << "\n"; }

// Multimap constructors -----------------------------------------------------------

		explicit
		multimap (const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type())
				  : _root(),
					_compare(comp),
					_alloc(alloc),
					_node_count(),
					_comp_val(comp),
					_end(),
					_rend() {

			_null = new node(value_type(), NULL, NULL, NULL, false, true);
			_end  = new node(value_type(), _null, _null, _null, true);
			_rend = new node(value_type(), _null, _null, _null, true);
			_set_empty_map();
		}

		  template <typename InputIterator>
		multimap (InputIterator first,
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
					
				_null = new node(value_type(), NULL, NULL, NULL, false, true);
				_end  = new node(value_type(), _null, _null, _null, true);
				_rend = new node(value_type(), _null, _null, _null, true);
				_set_empty_map();

				insert(first, last);
			}

		multimap (const multimap& x)
			  : _root(),
				_compare(x._compare),
				_alloc(x._alloc),
				_node_count(),
				_comp_val(x._comp_val),
				_end(),
				_rend() {

			_null = new node(value_type(), NULL, NULL, NULL, false, true);
			_end  = new node(value_type(), _null, _null, _null, true);
			_rend = new node(value_type(), _null, _null, _null, true);
			_set_empty_map();

			insert(x.begin(), x.end());
		}

// Multimap destructor --------------------------------------------------------------

		~multimap () {
			_clear();
			delete _end;
			delete _rend;
			delete _null;
		}

// // Multimap operators -------------------------------------------------------------------

		multimap&
		operator= (const multimap& x) {
			insert(x.begin(), x.end());
			return *this;
		}

// // Multimap methods ---------------------------------------------------------------------

// 	//  Iterators -------------------------------

		iterator
		begin () throw()				{ return iterator(_rend->_parent); }

		const_iterator
		begin () const throw()			{ return iterator(_rend->_parent); }

		iterator
		end () throw()					{ return iterator(_end); }

		const_iterator
		end () const throw()			{ return const_iterator(_end); }

		reverse_iterator
		rbegin () throw()				{ 
			return reverse_iterator(_end->_parent); }

		const_reverse_iterator
		rbegin () const throw() 		{ return reverse_iterator(_end->_parent); }

		reverse_iterator
		rend () throw()					{ return reverse_iterator(_rend); }

		const_reverse_iterator
		rend () const throw()			{ return const_reverse_iterator(_rend); }

// 	//  Capacity --------------------------------

		bool
		empty () const throw()			{ return _node_count == 0u; }

		size_type
		size () const throw()			{ return _node_count; }

		size_type
		max_size () const throw()		{ return std::numeric_limits<long>::max() / sizeof(_tree_node); }

// 	// Modifiers --------------------------------

		iterator
		insert (const value_type& val) {

			return _add_node(_root, val);
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

			value_type temp(k, T());
			ft::stack<node*> store;

			for (iterator first = begin(); first != end(); first++) {
				if (_is_key_equal(*first, temp)) {
					store.push(first.base());
				}
			}
			size_type count = store.size();

			while (!store.empty()) {
				_erase(store.top());
				store.pop();
			}
			return count;
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
		swap (multimap& x) {

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

// 	// Observers --------------------------------

		key_compare
		key_comp() const				{ return _compare; }
	
		value_compare
		value_comp() const				{ return _comp_val; }

// 	// Operations -------------------------------

		iterator
		find (const key_type& k)		{ return iterator(_find(k)); }

		const_iterator
		find (const key_type& k) const	{ return const_iterator(_find(k)); }

		size_type
		count (const key_type& k) const	{ 
			size_type n = 0u;
			value_type temp(k, T());

			for (iterator it = begin(); it != end(); it++) {
				if (_is_key_equal(*it, temp))
					n++;
			}
			return n;
		}

		iterator
		lower_bound (const key_type& k) { 
			
			iterator it = begin();
			value_type temp(k, T());
			
			while (it != end()) {
				if (_is_key_equal(*it, temp) || _comp_val(temp, it.base()->_data))
					return it;
				++it;
			}
			return it;
		}

		const_iterator
		lower_bound (const key_type& k) const {

			const_iterator it = begin();
			value_type temp(k, T());
			
			while (it != end()) {
				if (_is_key_equal(*it, temp) || _comp_val(temp, it.base()->data))
					return it;
				++it;
			}
			return it;
		}

		iterator
		upper_bound (const key_type& k) {

			iterator it = begin();
			value_type temp(k, T());
			
			while (it != end()) {
				if (_comp_val(temp, *it))
					return it;
				++it;
			}
			return it;
		}

		const_iterator
		upper_bound (const key_type& k) const {
			
			const_iterator it = begin();
			value_type temp(k, T());
			
			while (it != end()) {
				if (_comp_val(temp, *it))
					return it;
				++it;
			}
			return it;
		}

		std::pair<iterator, iterator>
		equal_range (const key_type& k) {

			return std::make_pair(lower_bound(k), upper_bound(k));
		}

		std::pair<const_iterator, const_iterator>
		equal_range (const key_type& k) const {

			return std::make_pair(lower_bound(k), upper_bound(k));
		}

// Friend functions -----------------------------------------------------------
		  template <typename _Key, typename _T, typename _Compare, typename _Alloc>
		friend bool
		operator== (const multimap<_Key,_T,_Compare,_Alloc>&, const multimap<_Key,_T,_Compare,_Alloc>&);

		  template <typename _Key, typename _T, typename _Compare, typename _Alloc>
		friend  bool
		operator<  (const multimap<_Key,_T,_Compare,_Alloc>&, const multimap<_Key,_T,_Compare,_Alloc>&);

		  template <typename _Key, typename _T, typename _Compare, typename _Alloc>
  		void swap (multimap<_Key,_T,_Compare,_Alloc>& x, multimap<_Key,_T,_Compare,_Alloc>& y);

		  template<typename U>
		friend void
		print_tree(U& tree);
	};

/************************************ end of Multimap class ***********************************/

// Friend functions definitions -----------------------------------------------

	 template <typename Key, typename T, typename Compare, typename Alloc>
	bool
	operator== (multimap<Key,T,Compare,Alloc>& x, multimap<Key,T,Compare,Alloc>& y) {
		
		if (x.size() != y.size()) return false;
		
		typename ft::multimap<Key, T>::iterator first1 = x.begin();
		typename ft::multimap<Key, T>::iterator first2 = y.begin();
		
		while (first1 != x.end()) {
			if (*first1 != *first2)
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	 template <typename Key, typename T, typename Compare, typename Alloc>
	bool
	operator!= (multimap<Key,T,Compare,Alloc>& x, multimap<Key,T,Compare,Alloc>& y) {
		return !(x == y);
	}

	 template <typename Key, typename T, typename Compare, typename Alloc>
	bool
	operator<  (multimap<Key,T,Compare,Alloc>& x, multimap<Key,T,Compare,Alloc>& y) {

		typename ft::multimap<Key, T>::iterator first1 = x.begin();
		typename ft::multimap<Key, T>::iterator first2 = y.begin();
		
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

	 template <typename Key, typename T, typename Compare, typename Alloc>
	bool
	operator<= (multimap<Key,T,Compare,Alloc>& x, multimap<Key,T,Compare,Alloc>& y) {
		return !(y < x);
	}

	 template <typename Key, typename T, typename Compare, typename Alloc>
	bool
	operator>  (multimap<Key,T,Compare,Alloc>& x, multimap<Key,T,Compare,Alloc>& y) {
		return y < x;
	}

	 template <typename Key, typename T, typename Compare, typename Alloc>
	bool
	operator>= (multimap<Key,T,Compare,Alloc>& x, multimap<Key,T,Compare,Alloc>& y) {
		return !(x < y);
	}

	  template <typename _Key, typename _T, typename _Compare, typename _Alloc>
	void swap (multimap<_Key,_T,_Compare,_Alloc>& x, multimap<_Key,_T,_Compare,_Alloc>& y) {
		x.swap(y);
	}
}
