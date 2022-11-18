#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# include "utils.hpp"

//https://en.cppreference.com/w/cpp/types/is_integral

namespace ft {

	template<typename T, T v>
	struct integral_constant {
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator T() { return value; }
	};

	typedef integral_constant<bool, false> false_type;
	typedef integral_constant<bool, true> true_type;

	template <typename T> struct is_integral : public false_type {};
	template <typename T> struct is_integral<const T> : public is_integral<T> {};
	template <typename T> struct is_integral<volatile const T> : public is_integral<T> {};
	template <typename T> struct is_integral<volatile T> : public is_integral<T> {};

	template <> struct is_integral<unsigned char> : public true_type {};
	template <> struct is_integral<unsigned short> : public true_type {};
	template <> struct is_integral<unsigned int> : public true_type {};
	template <> struct is_integral<unsigned long> : public true_type {};
	template <> struct is_integral<signed char> : public true_type {};
	template <> struct is_integral<short> : public true_type {};
	template <> struct is_integral<int> : public true_type {};
	template <> struct is_integral<long> : public true_type {};
	template <> struct is_integral<char> : public true_type {};
	template <> struct is_integral<bool> : public true_type {};
	// template <> struct is_integral<char32_t> : public true_type {};
	// template <> struct is_integral<char16_t> : public true_type {};
	template <> struct is_integral<wchar_t> : public true_type {};
	template <> struct is_integral<long long> : public true_type {};
	template <> struct is_integral<unsigned long long> : public true_type {};

} //namespace ft

#endif