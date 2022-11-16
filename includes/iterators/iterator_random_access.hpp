#ifndef ITERATOR_RANDOM_ACCESS_HPP
# define ITERATOR_RANDOM_ACCESS_HPP

# include "iterator.hpp"

//https://eel.is/c++draft/random.access.iterators
//https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf

namespace ft {

	template <typename Iterator>
	class random_access_iterator {

		public:
			typedef	typename iterator_traits<Iterator>::value_type 				value_type;
			typedef 		 std::ptrdiff_t										difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
			typedef typename ft::iterator_traits<Iterator*>::iterator_category	iterator_category;
			typedef 		 pointer											iterator_type;
	
		private:
			Iterator	current_;
	
		public:
			random_access_iterator(): current_() {}
			
			explicit random_access_iterator(pointer lhs): current_(lhs) {}
			
			Iterator base() const {
				return current_;
			}
			
			template <typename U> random_access_iterator(const random_access_iterator<U>& u): current_(u.base()) {}

			virtual ~random_access_iterator() {}

			template <typename U> random_access_iterator& operator=(const random_access_iterator<U>& u) {
				current_ = u.base();
				return *this;
			}
			
			reference operator*() const {
				return *current_;
			}
			
			pointer operator->() const {
				return &(operator*());
			}

			random_access_iterator& operator++() {
				++current_;
				return *this;
			}
			
			random_access_iterator operator++(int) {
				random_access_iterator tmp = *this;
				++current_;
				return tmp;
			}

			random_access_iterator& operator--() {
				--current_;
				return *this;
			}
			
			random_access_iterator operator--(int) {
				random_access_iterator tmp = *this;
				--current_;
				return tmp;
			}

			random_access_iterator operator+ (difference_type n) const {
				return random_access_iterator(current_ + n);
			}

			random_access_iterator& operator+=(difference_type n) {
				current_ += n;
				return *this;
			}

			random_access_iterator operator- (difference_type n) const {
				return random_access_iterator(current_ - n);
			}

			random_access_iterator& operator-=(difference_type n) {
				current_ -= n;
				return *this;
			}

			reference operator[](difference_type n) const {
				return current_[n];
			}
	};

	template <typename Iterator1, typename Iterator2>
	bool operator==(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	bool operator<(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
		return lhs.base() < rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	bool operator!=(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	bool operator>(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
		return lhs.base() > rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	bool operator>=(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	bool operator<=(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
		return lhs.base() <= rhs.base();
	}

}//namespace ft

#endif