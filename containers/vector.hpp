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
/********************************** Vector container ***************************************/

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

			void
			_allocate(size_type new_size, const value_type& value, ft::__true_type) {
				(void)value;
				if (new_size) {
					_finish = _start = _alloc.allocate(new_size + 2);
					_end_of_storage = _start + new_size + 2;
				}
			}

		  template <class InputIterator>
			void
			_allocate(InputIterator first, InputIterator last, ft::__false_type) {
				size_type new_size = _range_size(first, last);
				if (new_size) {
					_finish = _start = _alloc.allocate(new_size + 2);
					_end_of_storage = _start + new_size + 2;
				}
			}

			void
			_construct(size_type new_size, value_type value, ft::__true_type) {
				for (size_type i = 1; i < new_size + 1; ++i) {
					_alloc.construct(_start + i, value);
				}
				_finish = new_size ?_start + new_size + 1 : _finish;
			}

		  template <class InputIterator>
			void
			_construct(InputIterator first, InputIterator last, ft::__false_type) {
				size_type new_size = _range_size(first, last);
				for (size_type i = 1; i < new_size + 1; ++i, ++first) {
					_alloc.construct(_start + i, *first);
				}
				_finish = new_size ?_start + new_size + 1 : _finish;
			}

			// void
			// _destroy(size_type new_size, value_type value, ft::__true_type) {
			// 	for (size_type i = 1; i < new_size + 1; ++i) {
			// 		_alloc.destroy(_start + i);
			// 	}
			// 	_finish = _start;
			// }

		  template <class InputIterator>
			void
			_destroy(InputIterator first, InputIterator last) {
				size_type new_size = _range_size(first, last);
				for (size_type i = 1; i < new_size + 1; ++i, ++first) {
					_alloc.destroy(_start + i);
				}
				_finish = _start;
			}

			void
			_dealloc() {
				_alloc.deallocate(_start, _end_of_storage - _start);
				_start = _finish = _end_of_storage = NULL;
			}

		  template <class InputIterator>
			size_type
			_range_size(InputIterator first, InputIterator last) {
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
					_dealloc();
					_allocate(first, last, ft::__false_type());
					_construct(first, last, ft::__false_type());
				}
			}

		  template<typename T1>
			void
			_assign (size_type n, T1 val, ft::__true_type) {
				(void)val; (void)n;
				// this->clear();
				// while (n--) {
				// 	this->push_back(val);
				// }
			}
// ==============================================================================

		public:

// Vector constructors ----------------------------------------------------------

			explicit
			vector (const allocator_type& alloc = allocator_type())
					: _alloc(alloc), _start(), _finish(), _end_of_storage() {}

			explicit
			vector (size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type()):  _alloc(alloc) {
				_allocate(n, val, __true_type());
				_construct(n, val, ft::__true_type());
			}
			
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
						const allocator_type& alloc = allocator_type()): _alloc(alloc) {
				typedef typename ft::__is_integer<InputIterator>::__type _Integral;
				_allocate(first, last, _Integral());
				_construct(first, last, _Integral());
			}
			
			vector (const vector& x)
					: _start(), _finish(), _end_of_storage() { *this = x; }

// Vector destructors ---------------------------------------------------------------

			~vector() {
				_destroy(begin(), end());
				_dealloc();
			}

// Vector operators -----------------------------------------------------------------

			const vector&
			operator= (const vector& x) {
				_alloc = x._alloc;
				_allocate(x.begin(), x.end(), ft::__false_type());
				_construct(x.begin(), x.end(), ft::__false_type());
				return *this;
			}

			reference
			operator[] (size_type n) { return _start[n + 1]; }

			const_reference
			operator[] (size_type n) const { return _start[n + 1]; }

// Vector methods --------------------------------------------------------------------

		  template <class InputIterator>
			void
			assign (InputIterator first, InputIterator last) {
				typedef typename ft::__is_integer<InputIterator>::__type _Integral;
				_assign(first, last, _Integral());
			}

			void
			assign (size_type n, const value_type& val) {
				_assign(n, val, ft::__true_type());
			}

			iterator
			begin() NOEXCEPT			{ return iterator(_start != _finish ? _start + 1 : _start); }

			const_iterator
			begin() const NOEXCEPT		{ return const_iterator(_start != _finish ? _start + 1 : _start); }

			iterator
			end() NOEXCEPT				{ return iterator(_finish); }

			const_iterator
			end() const NOEXCEPT		{ return const_iterator(_finish); }

			iterator
			rbegin() NOEXCEPT			{ return iterator(_start != _finish ? _finish - 1 : _finish); }

			const_iterator
			rbegin() const NOEXCEPT		{ return const_iterator(_start != _finish ? _finish - 1 : _finish); }

			iterator
			rend() NOEXCEPT				{ return iterator(_start); }

			const_iterator
			rend() const NOEXCEPT		{ return const_iterator(_start); }

			reference
			back() NOEXCEPT				{ return *(rbegin()); }

			const_reference
			back() const NOEXCEPT		{ return *(rbegin()); }

			reference
			front() NOEXCEPT			{ return *(begin()); }

			const_reference
			front() const NOEXCEPT		{ return *(begin()); }

			bool
			empty() const NOEXCEPT		{ return begin() == end(); }

			size_type
			size() const NOEXCEPT		{ return empty() ? 0 : _finish - (_start + 1); }
			
			size_type
			max_size() const NOEXCEPT	{ return __gnu_cxx::__numeric_traits<ptrdiff_t>::__max / sizeof(T); }

			size_type
			capacity() const NOEXCEPT	{ return empty() ? 0 : _end_of_storage - (_start + 2); }
	};
// ==============================================================================
}
