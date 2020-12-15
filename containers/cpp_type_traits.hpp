#ifndef FT_CPP_TYPE_TRAITS_H
#define FT_CPP_TYPE_TRAITS_H 1

namespace ft {

  struct true_type_my { };
  struct false_type_my { };

  template<bool>
    struct truth_type_my
    { typedef false_type_my type_my; };

  template<>
    struct truth_type_my<true>
    { typedef true_type_my type_my; };

  // N.B. The conversions to bool are needed due to the issue
  // explained in c++/19404.
  template<class S, class T>
    struct traitor_my
    {
      enum { value_my = bool(S::value_my) || bool(T::value_my) };
      typedef typename truth_type_my<value_my>::type_my type_my;
    };

  // Compare for equality of types.
  template<typename, typename>
    struct are_same_my
    {
      enum { value_my = 0 };
      typedef false_type_my type_my;
    };

  template<typename T>
    struct are_same_my<T, T>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  // Holds if the template-argument is a void type.
  template<typename T>
    struct is_void_my
    {
      enum { value_my = 0 };
      typedef false_type_my type_my;
    };

  template<>
    struct is_void_my<void>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  //
  // Integer types
  //
  template<typename T>
    struct is_integer_my
    {
      enum { value_my = 0 };
      typedef false_type_my type_my;
    };

  // Thirteen specializations (yes there are eleven standard integer
  // types; <em>long long</em> and <em>unsigned long long</em> are
  // supported as extensions).  Up to four target-specific __int<N>
  // types are supported as well.
  template<>
    struct is_integer_my<bool>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  template<>
    struct is_integer_my<char>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  template<>
    struct is_integer_my<signed char>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  template<>
    struct is_integer_my<unsigned char>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

# ifdef _GLIBCXX_USE_WCHAR_T
  template<>
    struct is_integer_my<wchar_t>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };
# endif

#ifdef _GLIBCXX_USE_CHAR8_T
  template<>
    struct is_integer_my<char8_t>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };
#endif

#if __cplusplus >= 201103L
  template<>
    struct is_integer_my<char16_t>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  template<>
    struct is_integer_my<char32_t>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };
#endif

  template<>
    struct is_integer_my<short>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  template<>
    struct is_integer_my<unsigned short>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  template<>
    struct is_integer_my<int>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  template<>
    struct is_integer_my<unsigned int>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  template<>
    struct is_integer_my<long>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  template<>
    struct is_integer_my<unsigned long>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  template<>
    struct is_integer_my<long long>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  template<>
    struct is_integer_my<unsigned long long>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

#define __INT_N(TYPE) 					\
  template<>							\
    struct is_integer_my<TYPE>			\
    {									\
      enum { value_my = 1 };			\
      typedef true_type_my type_my;		\
    };									\
  template<>							\
    struct is_integer_my<unsigned TYPE>	\
    {									\
      enum { value_my = 1 };			\
      typedef true_type_my type_my;		\
    };

#ifdef __GLIBCXX_TYPE_INT_N_0
__INT_N(__GLIBCXX_TYPE_INT_N_0)
#endif
#ifdef __GLIBCXX_TYPE_INT_N_1
__INT_N(__GLIBCXX_TYPE_INT_N_1)
#endif
#ifdef __GLIBCXX_TYPE_INT_N_2
__INT_N(__GLIBCXX_TYPE_INT_N_2)
#endif
#ifdef __GLIBCXX_TYPE_INT_N_3
__INT_N(__GLIBCXX_TYPE_INT_N_3)
#endif

#undef __INT_N

  //
  // Floating point types
  //
  template<typename T>
    struct is_floating_my
    {
      enum { value_my = 0 };
      typedef false_type_my type_my;
    };

  // three specializations (float, double and 'long double')
  template<>
    struct is_floating_my<float>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  template<>
    struct is_floating_my<double>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  template<>
    struct is_floating_my<long double>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  //
  // Pointer types
  //
  template<typename T>
    struct is_pointer_my
    {
      enum { value_my = 0 };
      typedef false_type_my type_my;
    };

  template<typename T>
    struct is_pointer_my<T*>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  //
  // An arithmetic type is an integer type or a floating point type
  //
  template<typename T>
    struct is_arithmetic_my
    : public traitor_my<is_integer_my<T>, is_floating_my<T> >
    { };

  //
  // A scalar type is an arithmetic type or a pointer type
  // 
  template<typename T>
    struct is_scalar_my
    : public traitor_my<is_arithmetic_my<T>, is_pointer_my<T> >
    { };

  //
  // For use in std::copy and std::find overloads for streambuf iterators.
  //
  template<typename T>
    struct is_char_my
    {
      enum { value_my = 0 };
      typedef false_type_my type_my;
    };

  template<>
    struct is_char_my<char>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

#ifdef _GLIBCXX_USE_WCHAR_T
  template<>
    struct is_char_my<wchar_t>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };
#endif

  template<typename T>
    struct is_byte_my
    {
      enum { value_my = 0 };
      typedef false_type_my type_my;
    };

  template<>
    struct is_byte_my<char>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  template<>
    struct is_byte_my<signed char>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

  template<>
    struct is_byte_my<unsigned char>
    {
      enum { value_my = 1 };
      typedef true_type_my type_my;
    };

} // namespace

#endif //_CPP_TYPE_TRAITS_H
