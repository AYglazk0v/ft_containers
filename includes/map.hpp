#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "tree/rb_tree.hpp"
# include "utils/utils.h"

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

			map(const &map rhs) : tree_(tree_type(rhs.cmp_, rhs.alloc_)) {
				*this = rhs;
			}

			map& operator=(const map& rhs) {
				if (this == &rhs) {
					return (*this)
				}
				alloc_ = rhs.alloc_;
				tree_ = rhs.alloc_;
				cmp_ = rhs.cmp_;
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

// 23.3.1.2 element access:
			// mapped_type& operator[](const key_type& rhs) {
				// iterator tmp = this->tree_.find(rhs);	
			}
	}; //map

} // namespace ft


#endif