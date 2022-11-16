#ifndef ITERATOR_REVERSE_HPP
# define ITERATOR_REVERSE_HPP

# include "iterator.hpp"

//https://eel.is/c++draft/random.access.iterators
//https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf

namespace ft {
	
	template <typename Iterator>
	class reverse_iterator {
		
		public:
			typedef	Iterator 													iterator_type;
			typedef	typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	
		private:
			Iterator	current_;
			
		public:
			reverse_iterator(): current_() {}

			explicit reverse_iterator(Iterator rhs): current_(rhs) {}
			
			virtual ~reverse_iterator() {}
			
			Iterator base() const { 
				return current_;
			}

			template <typename U> reverse_iterator(const reverse_iterator<U>& u): current_(u.base()) {}

			template <typename U> reverse_iterator& operator=(const reverse_iterator<U>& u) {
				current_ = u.base();
				return *this;
			}
			
			reference operator*() const {
				Iterator tmp = current_;
				return *--tmp;
			}
			
			pointer operator->() const {
				return &(operator*());
			}

			reverse_iterator& operator++() {
				--current_;
				return *this;
			}

			reverse_iterator operator++(int) {
				reverse_iterator tmp = *this;
				--current_;
				return tmp;
			}

			reverse_iterator& operator--() {
				++current_;
				return *this;			
			}

			reverse_iterator operator--(int) {
				reverse_iterator tmp = *this;
				++current_;
				return tmp;
			}

			reverse_iterator operator+ (difference_type n) const {
				return reverse_iterator(current_ - n);
			}

			reverse_iterator& operator+=(difference_type n) {
				current_ -= n;
				return *this;
			}

			reverse_iterator operator- (difference_type n) const {
				return reverse_iterator(current_ + n);
			}

			reverse_iterator& operator-=(difference_type n) {
				current_ += n;
				return *this;
			}

			reference operator[](difference_type n) const {
				return current_[-n - 1];
			}
	};

	template <typename Iterator1, typename Iterator2>
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() < rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() > rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() <= rhs.base();
	}

}//namespace ft

#endif