#pragma once

#include <memory>

#ifndef NOEXCEPT
	#if __cplusplus <= 199711L
		#define NOEXCEPT throw()
	#else
		#define NOEXCEPT noexcept
	#endif
#endif

namespace ft {
/********************************** Vector container ***************************************/

template<typename T, typename Alloc = std::allocator<T>>
	class list {

	public:

		typedef Alloc								allocator_type;
		typedef size_t								size_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef const T*							const_pointer;
		typedef T&									reference;
		typedef const T&							const_reference;
		typedef ft::biderect_iterator<T, list_node>	biderect_iterator;
		typedef biderect_iterator					iterator;
		typedef biderect_iterator					const_iterator;
		typedef ft::reverse_iterator<T, list_node>	reverse_iterator;
		typedef ft::reverse_iterator<T, list_node>	const_reverse_iterator;
		typedef ft::iterator<T, list_node>			iterator_category;
};
