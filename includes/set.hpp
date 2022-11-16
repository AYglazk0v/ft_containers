#ifndef SET_HPP
# define SET_HPP

# include "tree/rb_tree.hpp" 
# include "utils/utils.h"

namespace ft
{
	template<typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key> >
	class set {
		public:
			typedef				Key										key_type;
			typedef				Key										value_type;
			typedef				Compare									key_compare;
			typedef				Compare									value_compare;
			typedef				Allocator								allocator_type;
			typedef typename 	Allocator::reference					reference;
			typedef typename 	Allocator::const_reference				const_reference;
			typedef typename 	Allocator::difference_type				difference_type;
			typedef typename 	Allocator::size_type					size_type;		
			typedef typename 	Allocator::pointer						pointer;
			typedef typename 	Allocator::const_pointer				const_pointer;
			typedef RBTree<value_type, key_compare, allocator_type>		tree_type;
			typedef typename	tree_type::iterator						iterator;
			typedef typename	tree_type::const_iterator				const_iterator;
			typedef typename	tree_type::reverse_iterator				reverse_iterator;
			typedef typename	tree_type::const_reverse_iterator		const_reverse_iterator;

		private:
			tree_type tree_;

		public:
// construct/copy/destroy:
			explicit set(const key_compare &comp = key_compare(), 
					const allocator_type &alloc = allocator_type()): 
				tree_(tree_type(comp, alloc)) 
			{}

			template< class InputIterator >
			set(InputIterator first,
					InputIterator last,
					const Compare & comp = Compare(),
					const Allocator &alloc = Allocator()):
				tree_(tree_type(comp, alloc)) {
				insert(first, last);
			}

			set(const set& rhs): tree_(tree_type(rhs.tree_)) {}

			set operator=(const set & rhs) {
				tree_ = rhs.tree_;
				return *this;
			}

			allocator_type get_allocator() const {
				return tree_.get_allocator();
			}

// iterators:
			iterator begin() { return tree_.begin(); }
			const_iterator begin() const { return tree_.begin(); }
			iterator end() { return tree_.end(); }
			const_iterator end() const { return tree_.end(); }
			reverse_iterator rbegin() {	return tree_.rbegin(); }
			const_reverse_iterator rbegin() const { return tree_.rbegin(); }
			reverse_iterator rend() { return (tree_.rend()); }
			const_reverse_iterator rend() const { return tree_.rend(); }

// capacity:
			bool empty() const { return tree_.empty(); }
			size_type size() const { return tree_.size(); }
			size_type max_size() const { return tree_.max_size(); }

// modifiers:
			ft::pair<iterator, bool> insert( const value_type& x) {
				return tree_.insert(x);
			}

			iterator insert( iterator position, const value_type& x) {
				(void)position;
				return tree_.insert(x).first;
			}

			template<class InputIterator>
			void insert(InputIterator first, InputIterator last) {
				while (first!=last)
					tree_.insert(*first++);
			}

			void erase(iterator position) {
				tree_.erase(*position);
			}

			size_type erase(const Key& x) {
				return tree_.delete_node(x);
			}

			void erase(iterator first, iterator last) {
				while (first!=last)
					tree_.delete_node(*first++);
			}

			void swap(set& rhs) {
				tree_.swap(rhs.tree_);
			}

			void clear(){
				tree_.clear();
			}	

// observers:
			value_compare value_comp() const { return (tree_.value_comp()); }
			key_compare key_comp() const { return (value_comp()); }

// set operations:
			iterator find(const key_type& x) { return tree_.find(x); }
			size_type count(const key_type &x) const { return tree_.count(x); }

			iterator lower_bound(const key_type& x) { return tree_.lower_bound(x); }
			iterator upper_bound(const key_type& x) { return tree_.upper_bound(x); }
			pair<iterator, iterator> equal_range(const key_type & x) { return tree_.equal_range(x); }

			template<class t_Key, class t_Compare, class t_Alloc>
			friend bool operator==(const set<t_Key, t_Compare, t_Alloc>& lhs, const set<t_Key, t_Compare, t_Alloc>& rhs) {
				return lhs.tree_ == rhs.tree_;
			}

			template<class t_Key, class t_Compare, class t_Alloc>
			friend bool operator!=(const set<t_Key, t_Compare, t_Alloc>& lhs, const set<t_Key, t_Compare, t_Alloc>& rhs) {
				return !(lhs == rhs);
			}

			template<class t_Key, class t_Compare, class t_Alloc>
			friend bool operator<(const set<t_Key, t_Compare, t_Alloc>& lhs, const set<t_Key, t_Compare, t_Alloc>& rhs) {
				return lhs.tree_ < rhs.tree_;
			}

			template<class t_Key, class t_Compare, class t_Alloc>
			friend bool operator>(const set<t_Key, t_Compare, t_Alloc>& lhs, const set<t_Key, t_Compare, t_Alloc>& rhs) {
				return rhs < lhs;
			}

			template<class t_Key, class t_Compare, class t_Alloc>
			friend bool operator<=(const set<t_Key, t_Compare, t_Alloc>& lhs, const set<t_Key, t_Compare, t_Alloc>& rhs) {
				return !(lhs > rhs);
			}

			template<class t_Key, class t_Compare, class t_Alloc>
			friend bool operator>=(const set<t_Key, t_Compare, t_Alloc>& lhs, const set<t_Key, t_Compare, t_Alloc>& rhs) {
				return !(lhs < rhs);
			}

	}; //namespace set

// specialized algorithms:
	template<class Key,class Compare, class Alloc>
	void swap(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
		lhs.swap(rhs);
	}

}; //namespace ft

#endif