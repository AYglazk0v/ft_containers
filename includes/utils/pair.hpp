#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {
	template <typename key, typename value>
	struct pair {
		typedef key		firsttype;
		typedef value	secondtype;
	
		firsttype	first;
		secondtype second;
	
		pair(): first(), second() {}

		pair(const key& f, const value& s) : first(f), second(s) {}

		template<typename U, typename V>
		pair (const pair<U, V>& p) : first(p.first), second(p.second) {}
	
		pair& operator=(const pair& p) {
			if (this == &p) {
				return *this;
			}
			first = p.first;
			second = p.second;
			return *this;
		}
	
		friend bool operator==(const pair<key, value>& lhs, const pair<key, value>& rhs) {
			return lhs.first == rhs.first && lhs.second == rhs.second;
		}
	
		friend bool operator!=(const pair<key, value>& lhs, const pair<key, value>& rhs) {
			return !(lhs == rhs);
		}
		
		friend bool operator<(const pair<key, value>& lhs, const pair<key, value>& rhs) {
			return lhs.first < rhs.first || (lhs.first <= rhs.first && lhs.second < rhs.second);
		}
	
		friend bool operator<=(const pair<key, value>& lhs, const pair<key, value>& rhs) {
			return !(rhs < lhs);
		}
	
		friend bool operator>(const pair<key, value>& lhs, const pair<key, value>& rhs) {
			return rhs < lhs;
		}
	
		friend bool operator>=(const pair<key, value>& lhs, const pair<key, value>& rhs) {
			return !(lhs < rhs);
		}
	};

	template<typename T1, typename T2> pair<T1, T2> make_pair(const T1& key, const T2& value) { return pair<T1, T2>(key, value); }

}//namespace ft
#endif