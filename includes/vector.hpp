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


};
