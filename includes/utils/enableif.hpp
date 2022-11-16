#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

# include "utils.h"

//https://stackoverflow.com/questions/2795023/c-template-typedef
//https://youtu.be/avnte_HqBKQ?list=PL3BR09unfgciJ1_K_E914nohpiOiHnpsK&t=1641

namespace ft {
	
	template <bool B, typename T = void>
	struct enable_if { typedef T type; };

	template <typename T>
	struct enable_if<false, T> { };

	template <bool B, typename T = void>
	struct enable_if_t {
		typedef enable_if<B, T> type;
	};

} // namespace ft

#endif