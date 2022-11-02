#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft {

	template<typename Iterator>
	class iterator_traits {
		public:
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	template<typename T>
	class iterator_traits<T*> {
		public:
			typedef	std::ptrdiff_t							difference_type;
			typedef	T 										value_type;
			typedef	T*										pointer;
			typedef	T&										reference;
			typedef	std::random_access_iterator_tag			iterator_category;
	};

	template<typename T>
	class iterator_traits<const T*> {
		public:
			typedef	std::ptrdiff_t							difference_type;
			typedef	T 										value_type;
			typedef const T*								pointer;
			typedef	const T&								reference;
			typedef	std::random_access_iterator_tag			iterator_category;
	};

	template<typename InputIterator>
	typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
		std::ptrdiff_t	 result = 0;
		while (first != last) {
			++first;
			++result;
		}
		return result;
	}

} //namespace ft

#endif