#ifndef STACK_HPP
#define  STACK_HPP

#include "vector.hpp"

namespace ft {

	template<typename T, typename Container = ft::vector<T> >
	class stack {
		
		public:
			typedef typename Container::value_type	value_type;
			typedef typename Container::size_type	size_type;
			typedef	Container						container_type;
			
		protected:
			Container c;
		
		public:
			explicit stack(const container_type& cont = container_type()) : c(cont) {};
			
			bool empty() const 				{ return c.empty();}
			size_type size() const 			{ return c.size(); }
			value_type& top()				{ return c.back(); }
			const value_type& const			{ return c.back(); }
			void push (const value_type& x) { c.push_back(x); }
			void pop()						{ c.pop_back(); }


			friend bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
			friend bool operator< (const stack<T, Container>& lhs, const stack<T, Container>& rhs);
			friend bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
			friend bool operator> (const stack<T, Container>& lhs, const stack<T, Container>& rhs);
			friend bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
			friend bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);

	}; //stack 

	template<typename T, typename Container = ft::vector<T>>
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.c == rhs.c;
	}

	template<typename T, typename Container = ft::vector<T>>
	bool operator< (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.c < rhs.c;
	}

	template<typename T, typename Container = ft::vector<T>>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.c != rhs.c;			
	}

	template<typename T, typename Container = ft::vector<T>>
	bool operator> (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.c > rhs.c;
	}

	template<typename T, typename Container = ft::vector<T>>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.c >= rhs.c;
	}

	template<typename T, typename Container = ft::vector<T>>
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.c <= rhs.c;
	}

}//namespace ft

#endif