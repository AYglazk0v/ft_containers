#ifndef MAP_HPP
# define MAP_HPP

# include "tree/rb_tree.hpp"
# include "utils/utils.h"
# include <functional>

namespace ft {
	
	template<typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
		public:
// types:
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef ft::pair<const Key, T>								value_type;
			typedef Compare												key_compare;
			typedef	Allocator											allocator_type;

			class value_compare : public std::binary_function<value_type,value_type,bool> {
				 private:
					friend class map;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					bool operator()(const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
						}
			};

			typedef typename	Allocator::reference					reference;
			typedef typename	Allocator::const_reference				const_reference;
			typedef typename	Allocator::difference_type				difference_type;
			typedef typename	Allocator::size_type					size_type;
			typedef typename	Allocator::pointer						pointer;
			typedef typename	Allocator::const_pointer				const_pointer;
			typedef RBTree<value_type, value_compare, allocator_type>	tree_type;
			typedef typename tree_type::iterator						iterator;
			typedef typename tree_type::const_iterator					const_iterator;
			typedef typename tree_type::reverse_iterator				reverse_iterator;
			typedef typename tree_type::const_reverse_iterator			const_reverse_iterator;

		private:
			tree_type		tree_;
		
// construct/copy/destroy:
		public:
			explicit map(const key_compare& cmp = key_compare(), const allocator_type& alloc = allocator_type()) :
					tree_(tree_type(cmp, alloc)),
			{}

			template<typename InputIterator>
			map(InputIterator first, InputIterator last,
					const key_compare& cmp = key_compare(),
					const allocator_type& alloc = allocator_type()) :
						tree_(tree_type(cmp, alloc)) {
				insert(first, last);
			}

			map(const &map rhs) : tree_(tree_type(rhs.cmp_, rhs.alloc_)) {
				*this = rhs;
			}

			map& operator=(const map& rhs) {
				if (this == &rhs) {
					return (*this)
				}
				tree_ = rhs.tree_;
				return *this;
			}

			~map() {}

// iterators:
			iterator begin() noexcept { return tree_.begin(); }
			const_iterator begin() const noexcept { return tree_.begin(); }
			interator end() { return tree_.end(); }
			const_iterator end() const noexcept { return tree_.end(); }
			reverse_iterator rbegin() {return tree_.rbegin(); }
			const_reverse_iterator rbegin() const noexcept { return tree_.rbegin(); }
			reverse_iterator rend() { return tree_.rend(); }
			const_reverse_iterator rend() const { return tree_.rend(); }


// capacity:
			bool empty() const { return tree_.empty(); }
			size_type size() const { return tree_.size(); }
			size_type max_size() const { return tree_.max_size(); }

// element access:
			mapped_type& operator[](const key_type& rhs) {
				return (*((this->insert(ft::make_pair(rhs, mapped_type()))).first)).second; //UB?
			}

// modifiers:
			pair<iterator, bool> insert(const value_type& x) {
				return tree_.insert(x);
			}

			iterator insert(iterator position, const value_type& x) {
				(void)position;
				return tree_.insert(x).first;
			}

			template<class InputIterator>
			void insert(InputIterator first, InputIterator last) {
				while (first!=last)
					tree_.insert(*first++);
			}

			void erase(iterator position) {
				tree_.delete_node(*position);
			}

			size_type erase(const Key& x) {
				return tree_.delete_node(ft::make_pair(x, mapped_type()));
			}

			void erase(iterator first, iterator last) {
				while (first!=last)
					tree_.delete_node(*first++);
			}

			void swap(map & other) {
				tree_.swap(other.tree_);
			}

			void clear() {
				tree_.clear();
			}

// observers:
			key_compare key_comp() const { return value_comp(); }
			value_compare value_comp() const { return tree_.value_comp(); }

//map operations:
			iterator	find(const Key& x) { return tree_.find(ft::make_pair(x, mapped_type())); }
			const_iterator find(const key_type& x) const { return tree_.find(ft::make_pair(x, mapped_type())); }
			size_type count(const Key& x) const { return tree_.count(ft::make_pair(x, mapped_type())); }
			iterator lower_bound(const key_type& x) { return tree_.lower_bound(ft::make_pair(x, mapped_type())); }	
			const_iterator lower_bound(const key_type& x) const { return tree_.lower_bound(ft::make_pair(x, mapped_type())); }	
			iterator upper_bound(const key_type& x) { return tree_.upper_bound(ft::make_pair(x, mapped_type())); }	
			const_iterator upper_bound(const key_type& x) const { return tree_.upper_bound(ft::make_pair(x, mapped_type())); }
			pair<iterator, iterator> equal_range(const key_type & x) { return tree_.equal_range(ft::make_pair(x, mapped_type())); }	
			pair<const_iterator, const_iterator> equal_range(const key_type & x) const { return tree_.equal_range(ft::make_pair(x, mapped_type())); }	


			template<class t_Key, class t_T, class t_Compare, class t_Alloc>
			friend bool operator==(const map<t_Key, t_T, t_Compare, t_Alloc>& lhs,
					const map<_Key, t_T, t_Compare, t_Alloc>& rhs) {
				return lhs.tree_ == rhs.tree_;
			}

			template<class t_Key, class t_T, class t_Compare, class t_Alloc>
			friend bool operator!=(const map<t_Key, t_T, t_Compare, t_Alloc>& lhs,
					const map<_Key, t_T, t_Compare, t_Alloc>& rhs) {
				return !(lhs == rhs);
			}

			template<class t_Key, class t_T, class t_Compare, class t_Alloc>
			friend bool operator<(const map<t_Key, t_T, t_Compare, t_Alloc>& lhs,
					const map<t_Key, t_T, t_Compare, t_Alloc>& rhs) {
				return lhs.tree_ < rhs.tree_;
			}
			
			template<class t_Key, class t_T, class t_Compare, class t_Alloc>
			friend bool operator>(const map<t_Key, t_T, t_Compare, t_Alloc>& lhs,
					const map<t_Key, t_T, t_Compare, t_Alloc>& rhs) {
				return rhs < lhs;
			}

			template<class t_Key, class t_T, class t_Compare, class t_Alloc>
			friend bool operator<=(const map<t_Key, t_T, t_Compare, t_Alloc>& lhs,
					const map<t_Key, t_T, t_Compare, t_Alloc>& rhs) {
				return !(lhs > rhs);
			}

			template<class t_Key, class t_T, class t_Compare, class t_Alloc>
			friend bool operator>=(const map<t_Key, t_T, t_Compare, t_Alloc>& lhs,
					const map<t_Key, t_T, t_Compare, t_Alloc>& rhs) {
				return !(lhs < rhs);
			}

	}; //map

// specialized algorithms:
	template<class t_Key, class t_T, class t_Compare, class t_Alloc>
	void swap(const map<t_Key, t_T, t_Compare, t_Alloc>& lhs, const map<t_Key, t_T, t_Compare, t_Alloc>& rhs) {
		lhs.swap(rhs);
	}

} // namespace ft

#endif