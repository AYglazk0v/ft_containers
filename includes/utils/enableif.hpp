#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

# include "utils.h"

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