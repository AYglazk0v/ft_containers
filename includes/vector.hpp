#ifndef VECROT_HPP
# define VECTOR_HPP

# include <bits/allocator.h>

namespace ft {
	template <typename T, typename Allocator = std::allocator<T>>
	class Vector {
	private:
		// typedef Vector_base_<T, Allocator>			Base;
		typedef typename _Base::_Tp_alloc_type		_Tp_alloc_type;
		// typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type>	_Alloc_traits;
		
	public:
		typedef T							value_type;
		// typedef typename _Base::pointer			pointer;
		// typedef typename _Alloc_traits::const_pointer	const_pointer;
		// typedef typename _Alloc_traits::reference		reference;
		// typedef typename _Alloc_traits::const_reference	const_reference;
		// typedef __gnu_cxx::__normal_iterator<pointer, vector> iterator;
		// typedef __gnu_cxx::__normal_iterator<const_pointer, vector> const_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef ft::reverse_iterator<iterator>		reverse_iterator;
		typedef size_t						size_type;
		typedef ptrdiff_t					difference_type;
		typedef Allocator					allocator_type;

	};
}

#endif