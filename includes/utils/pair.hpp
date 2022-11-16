#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {
	template <typename key, typename value>
	struct pair {
		typedef key		first_type;
		typedef value	second_type;
	
		first_type	first_;
		second_type second_;
	
		pair(): first_(), second_() {}

		pair(const key& f, const value& s) : first_(f), second_(s) {}

		template<typename U, typename V>
		pair (const pair<U, V>& p) : first_(p.first_), second_(p.second_) {}
	
		pair& operator=(const pair& p) {
			if (this == &p) {
				return *this;
			}
			first_ = p.first_;
			second_ = p.second_;
			return *this;
		}
	
		friend bool operator==(const pair<key, value>& lhs, pair<key, value>& rhs) {
			return lhs.first_ == rhs.first_ && lhs.second_ == rhs.second_;
		}
	
		friend bool operator!=(const pair<key, value>& lhs, pair<key, value>& rhs) {
			return !(lhs == rhs);
		}
		
		friend bool operator<(const pair<key, value>& lhs, pair<key, value>& rhs) {
			return lhs.first_ < rhs.first_ || (lhs.first_ <= rhs.first_ && lhs.second_ < rhs.second_);
		}
	
		friend bool operator<=(const pair<key, value>& lhs, pair<key, value>& rhs) {
			return !(rhs < lhs);
		}
	
		friend bool operator>(const pair<key, value>& lhs, pair<key, value>& rhs) {
			return rhs < lhs;
		}
	
		friend bool operator>=(const pair<key, value>& lhs, pair<key, value>& rhs) {
			return !(lhs < rhs);
		}
	};

	template<typename T1, typename T2> pair<T1, T2> make_pair(const T1& key, const T2& value) { return pair<T1, T2>(key, value); }

}//namespace ft
#endif