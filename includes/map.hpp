/*
// Map -- отсортированный ассоциативный контейнер, содержащий пары ключ-значение с уникальными ключами.
// Ключи сортируются с помощью функции сравнения Comapare. Операции поиска, удаления и вставки имеют логарифмическую сложность.
// Контейнер реализуется на основе красно-черного дерева.
// Использованные материалы:
//		https://en.cppreference.com/w/cpp/container/map
//		https://android.googlesource.com/platform/ndk/+/5de42e6621b3d0131472c3f8838b7f0ccf3e8963/sources/cxx-stl/llvm-libc++/libcxx/include/__tree
//		https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf
//		https://eel.is/c++draft/map
//		https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/stl_tree.h
*/

#ifndef MAP_HPP
# define MAP_HPP

# include "tree/rb_tree.hpp"
# include <memory>
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
						return comp(x.first_, y.first_);
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
			allocator_type	alloc_;
			tree_type		tree_;
			key_compare		cmp_;
		
// construct/copy/destroy:
		public:
			explicit map(const key_compare& cmp = key_compare(), const allocator_type& alloc = allocator_type()) :
					alloc_(alloc),
					tree_(tree_type(cmp, alloc)),
					cmp_(cmp)
			{}

			template<typename InputIterator>
			map(InputIterator first, InputIterator last,
					const key_compare& cmp = key_compare(),
					const allocator_type& alloc = allocator_type()) :
								alloc_(alloc),
								tree_(tree_type(cmp, alloc)),
								cmp_(cmp) {
				insert(first, last);
			}

			map(const map& rhs) : tree_(tree_type(rhs.cmp_, rhs.alloc_)) {
				*this = rhs;
			}

			map& operator=(const map& rhs) {
				if (this == &rhs) {
					return (*this);
				}
				alloc_ = rhs.alloc_;
				tree_ = rhs.tree_;
				cmp_ = rhs.cmp_;
				return *this;
			}

			~map() {}

// iterators:
			iterator begin() { return tree_.begin(); }
			const_iterator begin() const { return tree_.begin(); }
			iterator end() { return tree_.end(); }
			const_iterator end() const { return tree_.end(); }
			reverse_iterator rbegin() {return tree_.rbegin(); }
			const_reverse_iterator rbegin() const { return tree_.rbegin(); }
			reverse_iterator rend() { return tree_.rend(); }
			const_reverse_iterator rend() const { return tree_.rend(); }

// capacity:
			bool empty() const { return tree_.empty(); }
			size_type size() const { return tree_.size(); }
			size_type max_size() const { return tree_.max_size(); }

// element access:
			mapped_type& operator[](const key_type& rhs) {
				return (*((this->insert(ft::make_pair(rhs, mapped_type()))).first_)).second_; //UB?
			}

// modifiers:
			pair<iterator, bool> insert(const value_type& x) {
				return tree_.insert_node(x);
			}

			iterator insert(iterator position, const value_type& x) {
				(void)position;
				return tree_.insert_node(x).first_;
			}

			template<typename InputIterator>
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


			template<typename t_Key, typename t_T, typename t_Compare, typename t_Alloc>
			friend bool operator==(const map<t_Key, t_T, t_Compare, t_Alloc>& lhs, const map<t_Key, t_T, t_Compare, t_Alloc>& rhs) {
				return lhs.tree_ == rhs.tree_;
			}

			template<typename t_Key, typename t_T, typename t_Compare, typename t_Alloc>
			friend bool operator!=(const map<t_Key, t_T, t_Compare, t_Alloc>& lhs,
					const map<t_Key, t_T, t_Compare, t_Alloc>& rhs) {
				return !(lhs == rhs);
			}

			template<typename t_Key, typename t_T, typename t_Compare, typename t_Alloc>
			friend bool operator<(const map<t_Key, t_T, t_Compare, t_Alloc>& lhs,
					const map<t_Key, t_T, t_Compare, t_Alloc>& rhs) {
				return lhs.tree_ < rhs.tree_;
			}
			
			template<typename t_Key, typename t_T, typename t_Compare, typename t_Alloc>
			friend bool operator>(const map<t_Key, t_T, t_Compare, t_Alloc>& lhs,
					const map<t_Key, t_T, t_Compare, t_Alloc>& rhs) {
				return rhs < lhs;
			}

			template<typename t_Key, typename t_T, typename t_Compare, typename t_Alloc>
			friend bool operator<=(const map<t_Key, t_T, t_Compare, t_Alloc>& lhs,
					const map<t_Key, t_T, t_Compare, t_Alloc>& rhs) {
				return !(lhs > rhs);
			}

			template<typename t_Key, typename t_T, typename t_Compare, typename t_Alloc>
			friend bool operator>=(const map<t_Key, t_T, t_Compare, t_Alloc>& lhs,
					const map<t_Key, t_T, t_Compare, t_Alloc>& rhs) {
				return !(lhs < rhs);
			}

	}; //map

// specialized algorithms:
	template<typename t_Key, typename t_T, typename t_Compare, typename t_Alloc>
	void swap(const map<t_Key, t_T, t_Compare, t_Alloc>& lhs, const map<t_Key, t_T, t_Compare, t_Alloc>& rhs) {
		lhs.swap(rhs);
	}

} // namespace ft

#endif