#ifndef IS_ITER_HPP
# define IS_ITER_HPP

# include "utils.h"

namespace ft {

	template <typename T> struct is_iter : public false_type {};
	template <typename T> struct is_iter<const T> : public is_iter<T> {};
	template <typename T> struct is_iter<volatile const T> : public is_iter<T> {};
	template <typename T> struct is_iter<volatile T> : public is_iter<T> {};


	template <typename T> struct is_iter<typename ft::random_access_iterator<T*> > : public true_type {};
	template <typename T> struct is_iter<typename ft::reverse_iterator<T*> > : public true_type {};
	template <typename T> struct is_iter<__gnu_cxx::__normal_iterator<T*, std::vector<T> > > : public true_type {};

} // namespace ft

#endif