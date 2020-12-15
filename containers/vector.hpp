#pragma once

#include <iterator>
#include "iterator_random.hpp"
#include "cpp_type_traits.hpp"

#ifndef NOEXCEPT
	#if __cplusplus >= 201103L
		#define NOEXCEPT throw()
	#else
		#define NOEXCEPT noexcept
	#endif
#endif

namespace ft {
/********************************** Vector class ***************************************/

	template<typename T, typename Alloc = std::allocator<T> >
	class vector {

	private:

		typedef ft::random_iterator<T>			random_iterator;
		typedef ft::random_reverse_iterator<T>	random_reverse_iterator;


	public:

		typedef Alloc					allocator_type;
		typedef size_t					size_type;
		typedef T						value_type;
		typedef T*						pointer;
		typedef const T*				const_pointer;
		typedef T&						reference;
		typedef const T&				const_reference;
		typedef random_iterator			iterator;
		typedef random_iterator			const_iterator;
		typedef random_reverse_iterator	reverse_iterator;
		typedef random_reverse_iterator	const_reverse_iterator;

	private:

		allocator_type	_alloc;
		pointer			_start;
		pointer			_finish;
		pointer			_end_of_storage;

// Supporting functions -------------------------------------------------------

		size_type
		_check_max_len (size_type n) const {
			if (n >= max_size())
				throw std::out_of_range("cannot create ft::vector larger than max_size()");
			return n;
		}

		size_type
		_check_range (size_type n) const {
			if (n >= size())
				throw std::out_of_range("Index is out of range");
			return n;
		}

		void
		_allocate (size_type new_size, const value_type& value, ft::__true_type) {
			(void)value;
			if (new_size) {
				_finish = _start = _alloc.allocate(new_size + 2);
				_end_of_storage = _start + new_size + 2;
			}
		}

		template<typename InputIterator>
		void
		_allocate (InputIterator first, InputIterator last, ft::__false_type) {
			size_type new_size = _range_size(first, last);
			if (new_size) {
				_finish = _start = _alloc.allocate(new_size + 2);
				_end_of_storage = _start + new_size + 2;
			}
		}

		void
		_construct (size_type new_size, const value_type& value, ft::__true_type) {
			for (size_type i = 1; i < new_size + 1; ++i) {
				_alloc.construct(_start + i, value);
			}
			_finish = new_size ?_start + new_size + 1 : _finish;
		}

		template<typename InputIterator>
		void
		_construct (InputIterator first, InputIterator last, ft::__false_type) {
			size_type new_size = _range_size(first, last);
			for (size_type i = 1; i < new_size + 1; ++i, ++first) {
				_alloc.construct(_start + i, *first);
			}
			_finish = new_size ?_start + new_size + 1 : _finish;
		}

		template<typename InputIterator>
		void
		_destroy (InputIterator first, InputIterator last) {
			if (_finish != _start) {
				for (size_type i = 1; first != last; ++i, ++first) {
					_alloc.destroy(_start + i);
				}
				_finish = _start;
			}
		}

		template<typename InputIterator>
		void
		_destroy_simple (InputIterator first, InputIterator last) {
			if (_finish != _start) {
				for (size_type i = 1; first != last; ++i, ++first) {
					_alloc.destroy(_start + i);
				}
			}
		}

		void
		_dealloc (pointer start, pointer finish, pointer end_of_store) {
			_alloc.deallocate(start, end_of_store - start);
			start = finish = end_of_store = NULL;
		}

		template<typename InputIterator>
		size_type
		_range_size (InputIterator first, InputIterator last) const {
			size_type s;
			for (s = 0; first != last; ++first, ++s) ; 
			return s; 
		}

		template<typename InputIterator>
		void
		_assign (InputIterator first, InputIterator last, ft::__false_type) {
			size_type new_size = _range_size(first, last);
			if (new_size <= capacity()) {
				_destroy(first, last);
				_construct(first, last, ft::__false_type());
			} else {
				_destroy(first, last);
				_dealloc(_start, _finish, _end_of_storage);
				_allocate(first, last, ft::__false_type());
				_construct(first, last, ft::__false_type());
			}
		}

		template<typename T1>
		void
		_assign (size_type new_size, const T1& val, ft::__true_type) {
			if (new_size <= this->capacity()) {
				_destroy(this->begin(), this->end());
				_construct(new_size, val, ft::__true_type());
			} else {
				_destroy(this->begin(), this->end());
				_dealloc(_start, _finish, _end_of_storage);
				_allocate(_check_max_len(new_size), val, ft::__true_type());
				_construct(new_size, val, ft::__true_type());
			}
		}

		iterator
		_copy_range (iterator dst, iterator first, iterator last) {
			for ( ; first != last; ++first, ++dst) {
				_alloc.construct(dst.base(), *first);
			}
			return dst.base();
		}

		template<typename T1>
		iterator
		_copy_fill (iterator dst, size_type n, const T1& val) {
			for (size_type _size = 0 ; _size < n; ++dst, ++_size) {
				_alloc.construct(dst.base(), val);
			}
			return dst.base();
		}

		iterator
		_copy_to_end (iterator position, size_t size) {
			iterator first = --end();
			iterator last = first + size;
			iterator res = end() + size;
			for (; first >= position; --first, --last) {
				_alloc.construct(last.base(), *first);
				_alloc.destroy(first.base());
			}
			return res;
		}

		template<typename InputIterator>
		void
		_insert (iterator position, InputIterator first, InputIterator last, ft::__false_type) {
			
			size_type _size = _range_size(first, last) + this->size();
			iterator _end;
			pointer _start_old = _start;
			pointer _finish_old = _finish;
			pointer	_end_of_s_old = _end_of_storage;

			if (_size > this->capacity()) {
				size_type _alloc_size = !size() ? _size : (size() * 2 > _size ? size() * 2 : _size);
				_allocate(_check_max_len(_alloc_size), T(), ft::__true_type());

				if (_start_old == _finish_old) {
					_end = _copy_range(_start + 1, iterator(first.base()), iterator(last.base())); 
				} else {
					_end = _copy_range(_start + 1, iterator(_start_old + 1), position);
					_end = _copy_range(_end, iterator(first.base()), iterator(last.base()));
					_end = _copy_range(_end, position, iterator(_finish_old));
					_destroy(iterator(_start_old + 1), iterator(_finish_old));
				}
				_dealloc(_start_old, _finish_old, _end_of_s_old);
			} else {
				if (_start_old == _finish_old) {
					_end = _copy_range(_start + 1, iterator(first.base()), iterator(last.base()));
				} else {
					_end = _copy_to_end(position, _range_size(first, last));
					_copy_range(position, iterator(first.base()), iterator(last.base()));
				}
			}
			_finish = _end.base();
		}

		template<typename T1>
		iterator
		_insert (iterator position, size_type n, const T1& val, ft::__true_type) {
			size_type _size = n + this->size();
			iterator _end;
			iterator _res;
			pointer _start_old = _start;
			pointer _finish_old = _finish;
			pointer	_end_of_s_old = _end_of_storage;

			if (_size > this->capacity()) {
				size_type _alloc_size = !size() ? _size : _max(size() * 2, _size);
				_allocate(_check_max_len(_alloc_size), T1(), ft::__true_type());

				if (_start_old == _finish_old) {
					_end = _copy_fill(_start + 1, n, val);
					_res = iterator(_start + 1);
				} else {
					_end = _copy_range(_start + 1, iterator(_start_old + 1), position);
					_end = _copy_fill(_end, n, val);
					_res = _end;
					_end = _copy_range(_end, position, iterator(_finish_old));
					_destroy(iterator(_start_old + 1), iterator(_finish_old));
					_dealloc(_start_old, _finish_old, _end_of_s_old);
				}
			} else {
				_res = position;
				if (_start_old == _finish_old) {
					_end = _copy_fill(_start + 1, n, val);
				} else {
					_end = _copy_to_end(position, n);
					_copy_fill(position, n, val);
				}
			}
			_finish = _end.base();
			return _res;
		}

		size_type
		_max (size_type val1, size_type val2) const { return val1 > val2 ? val1 : val2; }

		template<typename T1>
		void
		_swap (T1& val1, T1& val2) {
			T1 temp = val1;
			val1 = val2;
			val2 = temp;
		}

	public:

// Vector constructors ----------------------------------------------------------

		explicit
		vector (const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _start(), _finish(), _end_of_storage() {}

		explicit
		vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()):  _alloc(alloc) {
			_allocate(_check_max_len(n), val, __true_type());
			_construct(n, val, ft::__true_type());
		}
		
		template<typename InputIterator>
		vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type()): _alloc(alloc) {
			typedef typename ft::__is_integer<InputIterator>::__type _Integral;
			_allocate(first, last, _Integral());
			_construct(first, last, _Integral());
		}
		
		vector (const vector& x)
				: _start(), _finish(), _end_of_storage() { *this = x; }

		const vector&
		operator= (const vector& x) {
			_alloc = x._alloc;
			_allocate(x.begin(), x.end(), ft::__false_type());
			_construct(x.begin(), x.end(), ft::__false_type());
			return *this;
		}

// Vector destructor ---------------------------------------------------------------

		~vector () {
			_destroy(begin(), end());
			_dealloc(_start, _finish, _end_of_storage);
		}

// Vector methods -------------------------------------------------------------------

	// Iterators --------------------------------

		iterator
		begin () NOEXCEPT			{ return iterator(_start != _finish ? _start + 1 : _start); }

		const_iterator
		begin () const NOEXCEPT		{ return const_iterator(_start != _finish ? _start + 1 : _start); }

		iterator
		end () NOEXCEPT				{ return iterator(_finish); }

		const_iterator
		end () const NOEXCEPT		{ return const_iterator(_finish); }

		reverse_iterator
		rbegin () NOEXCEPT			{ return reverse_iterator(_start != _finish ? _finish - 1 : _finish); }

		const_reverse_iterator
		rbegin () const NOEXCEPT	{ return const_reverse_iterator(_start != _finish ? _finish - 1 : _finish); }

		reverse_iterator
		rend () NOEXCEPT			{ return reverse_iterator(_start); }

		const_reverse_iterator
		rend () const NOEXCEPT		{ return const_reverse_iterator(_start); }


	//  Capacity --------------------------------

		size_type
		size () const NOEXCEPT		{ return empty() ? 0 : _finish - (_start + 1); }
		
		size_type
		max_size () const NOEXCEPT	{ return __gnu_cxx::__numeric_traits<ptrdiff_t>::__max / sizeof(T); }

		void
		resize (size_type n, value_type val = value_type()) {
			if (n == size()) return;

			size_type _size;
			if (n < size()) {
				_size = size() - n;
				_destroy_simple(begin() + _size, iterator(_finish));
				_finish -= _size;
			} else {
				_size = n - size();
				if (n <= capacity()) {
					this->insert(this->end(), _size, val);
				} else {
					pointer _start_old = _start;
					pointer _finish_old = _finish;
					pointer	_end_of_s_old = _end_of_storage;

					size_type _alloc_size = !size() ? n : _max(size() * 2, n);
					_allocate(_alloc_size, val, ft::__true_type());
					iterator _end = _start + 1;
					if (_start_old != _finish_old)
						_end = _copy_range(_start + 1, iterator(_start_old + 1), iterator(_finish_old));
					_end = _copy_fill(_end, _size, val);
					if (_start_old != _finish_old)
						_destroy(iterator(_start_old + 1), iterator(_finish_old));
					_dealloc(_start_old, _finish_old, _end_of_s_old);
					_finish = _end.base();
				}
			}
		}

		size_type
		capacity () const NOEXCEPT	{ return _end_of_storage == _start ? 0 : _end_of_storage - (_start + 2); }

		bool
		empty () const NOEXCEPT		{ return begin() == end(); }

		void
		reserve (size_type new_size) {
			if (new_size > max_size()) {
				throw std::length_error("ft::vector::reserve::Requested size is larger than max_size()");
			}
			if (new_size <= capacity()) return;

			pointer	_start_old = _start;
			pointer _finish_old = _finish;
			pointer	_end_of_s_old = _end_of_storage;
			iterator _begin_old = iterator(_start == _finish ? _start : _start + 1);
			iterator _end_old = iterator(_finish);
			iterator _new_finish;

			_allocate(new_size, T(), ft::__true_type());
			_new_finish = _copy_range(_start + 1, _begin_old, _end_old);
			_destroy(_begin_old, _end_old);
			_dealloc(_start_old, _finish_old, _end_of_s_old);
			_finish = _new_finish.base();
		}

	//  Element access ------------------------------

		reference
		operator[] (size_type n)		{ return _start[n + 1]; }

		const_reference
		operator[] (size_type n) const	{ return _start[n + 1]; }

		reference
		at (size_type n)				{ return (*this)[_check_range(n)]; }

		const_reference
		at (size_type n) const			{ return (*this)[_check_max_len(n)]; }

		reference
		front () NOEXCEPT				{ return *(begin()); }

		const_reference
		front () const NOEXCEPT			{ return *(begin()); }

		reference
		back () NOEXCEPT				{ return *(rbegin()); }

		const_reference
		back () const NOEXCEPT			{ return *(rbegin()); }

	//  Modifiers ------------------------------------

		template<typename InputIterator>
		void
		assign (InputIterator first, InputIterator last) {
			typedef typename ft::__is_integer<InputIterator>::__type _Integral;
			_assign(first, last, _Integral());
		}

		void
		assign (size_type n, const value_type& val) { _assign(n, val, ft::__true_type()); }

		void
		push_back (const value_type& val) NOEXCEPT	{ insert(end(), 1, val); }

		void
		pop_back () NOEXCEPT						{ _alloc.destroy(--_finish); }

		iterator
		insert (iterator position, const value_type& val) {
			return _insert(position, static_cast<size_type>(1), val, ft::__true_type());
		}

		void
		insert (iterator position, size_type n, const value_type& val) {
			_insert(position, n, val, ft::__true_type());
		}

		template<typename InputIterator>
		void
		insert (iterator position, InputIterator first, InputIterator last) {
			typedef typename ft::__is_integer<InputIterator>::__type _Integral;
			_insert(position, first, last, _Integral());
		}

		iterator
		erase (iterator position) NOEXCEPT {
			iterator res = position;
			for ( ;position != end(); ++position) {
				_alloc.destroy(position.base());
				_alloc.construct(position.base(), *(position + 1));
			}
			if (!empty())
				--_finish;
			return res;
		}
		
		iterator
		erase (iterator first, iterator last) NOEXCEPT {

			iterator res = first;
			size_type size = _range_size(first, last);

			for (; first != last; ++first) {
				_alloc.destroy(first.base());
			}
			for (first = res; first != last && last != end(); ++first, ++last) {
				_alloc.destroy(first.base());
				_alloc.construct(first.base(), *(last));
			}
			_finish -= size;
			return res;
		}

		void
		swap (vector& x) NOEXCEPT {
			_swap(_start, x._start);
			_swap(_finish, x._finish);
			_swap(_end_of_storage, x._end_of_storage);
		}
		void
		clear () NOEXCEPT			{ _destroy(begin(), end()); }

	// Non-member overloads ------------------------------------------------------------

		template<typename _T, typename _Alloc>
		friend bool
		operator== (const vector<_T, _Alloc>&, const vector<_T, _Alloc>&);

		template<typename _T, typename _Alloc>
		friend bool
		operator<  (const vector<_T, _Alloc>&, const vector<_T, _Alloc>&);

		template<typename _T, typename _Alloc>
		friend void
		swap (list<_T, _Alloc>&, list<_T, _Alloc>&);

	};

/************************************ end of list class **************************************/

// Friend functions definitions -------------------------------------------------


	template<typename T, typename Alloc>
	inline bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		
		if (lhs.size() != rhs.size()) return false;
		
		typename ft::vector<T>::iterator first1 = lhs.begin();
		typename ft::vector<T>::iterator first2 = rhs.begin();
		while (first1 != lhs.end()) {
			if (*first1 != *first2)
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template<typename T, typename Alloc>
	inline bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template<typename T, typename Alloc>
	inline bool operator<  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {

		typename ft::vector<T>::iterator first1 = lhs.begin();
		typename ft::vector<T>::iterator first2 = rhs.begin();
		
		while (first1 != lhs.end() && first2 != rhs.end()) {
			if (*first1 < *first2)
				return true;
			if (*first1 > *first2)
				return false;
			++first1;
			++first2;
		}
		if (lhs.size() > rhs.size() ||
			(lhs.size() == rhs.size() && *(--first1) >= *(--first2)))
				return false;
		return true;
	}

	template<typename T, typename Alloc>
	inline bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template<typename T, typename Alloc>
	inline bool operator> (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		return rhs < lhs;
	}

	template<typename T, typename Alloc>
	inline bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template<typename T, typename Alloc>
	void
	swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}

}
