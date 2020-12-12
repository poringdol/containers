#pragma once

#include "iterator_random.hpp"
#include <iterator>

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

			size_type		size;
			size_type		capacity;
			pointer			start;
			pointer			finish;
			pointer			end_of_storage;
			allocator_type	alloc;

			void
			_alloc_fill(size_type new_size, value_type value) {
				size = capacity = new_size;
				start = alloc.allocate(size + 2);
				for (size_type i = 1; i < size + 1; i++) {
					alloc.construct(start + i, value);
				}
				finish = start + size + 1;
				end_of_storage = start + size + 2;
			}

			void
			_alloc_range(size_type new_size, value_type value, ) {
				size = capacity = new_size;
				start = alloc.allocate(size + 2);
				for (size_type i = 1; i < size + 1; i++) {
					alloc.construct(start + i, value);
				}
				finish = start + size + 1;
				end_of_storage = start + size + 2;
			}

			void
			_dealloc() {
				for (size_type i = 1; i < size + 1; i++) {
					alloc.destroy(start + i);
				}	
				alloc.deallocate(start, capacity + 2);
			}

			template <class InputIterator>
			size_type
			_range_size(InputIterator first, InputIterator last) {
				size_type s;
				for (s = 0; first != last; ++first, ++s) ;
				return s;
			}

		public:

			explicit
			vector (const allocator_type& alloc = allocator_type())
							: size(0), capacity(0),
							  start(), finish(), end_of_storage() {}

			explicit
			vector (size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type()) {
				_alloc_fill(n, val);
			}
			
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
						const allocator_type& alloc = allocator_type()) {
				typedef typename std::__is_integer<InputIterator>::__type _Integral;
				_alloc(first, last, )
			}
			
			vector (const vector& x) {

			}

			~vector() { _dealloc(); }

			reference
			operator[] (size_type n) { return start[n + 1]; }

			const_reference
			operator[] (size_type n) const { return start[n + 1]; }
	};
}
