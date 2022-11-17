#ifndef LEXICOGRAPHICAL_CMP_HPP
# define LEXICOGRAPHICAL_CMP_HPP

# include "utils.hpp"

//https://eel.is/c++draft/alg.lex.comparison
//https://timsong-cpp.github.io/cppwp/n3337/draft.pdf

namespace ft {
	
	template<typename InputIterator1, typename InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2) {
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2,
								BinaryPredicate pred) {
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (pred(*first1, *first2)) return true;
			if (pred(*first2, *first1)) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

} //namespace ft

#endif