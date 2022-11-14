#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include <iostream>
# include <memory>
# include "../iterators/RBTree_iterator.hpp"
# include "../iterators/iterator_reverse.hpp"
# include "../utils/utils.h"

namespace ft {
	template<typename Value, typename Compare = std::less<Value>, typename Allocator = std::allocator<Value> >
	class RBTree {
		public:
			typedef Value													value_type;
			typedef Compare 												value_compare;
			typedef	Allocator												allocator_type;
			typedef typename allocator_type::reference 						reference;
			typedef typename allocator_type::const_reference			 	const_reference;
			typedef typename allocator_type::pointer 						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::size_type						size_type;

			typedef RB_Node<Value>											Node;
			typedef Node*													node_pointer;
			
			//↓↓↓ необходимо для корректного выделения памяти
			typedef typename allocator_type::template rebind<Node>::other 	allocator_node; 

			typedef ft::RBTree_iterator<Value>								iterator;
			typedef ft::RBTree_iterator<const Value>						const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

		private:
			allocator_node  alloc_node_;
			allocator_type  alloc_val_;
			node_pointer	nil_;
			node_pointer 	root_;
			value_compare 	comp_;
			size_t 			size_;

		public:
		 	RBTree() : 
					alloc_node_(allocator_node()),
					alloc_val_(allocator_type(),
					nil_(alloc_node_.allocate(1)),
					root_(nil_),
					comp_(value_compare()),
					size_(0)) {
				alloc_node_.construct(nil_, Node(nil_, nil_, nil_, nil));
			}

			RBTree(const Compare &cmp, const allocator_type& alloc = allocator_type()):
					alloc_node_(allocator_node()),
					alloc_val_(alloc),
					nil_(alloc_node_.allocate(1)),
					root_(nil_),
					comp_(cmp),
					size_(0) {
				alloc_node_.construct(nil_, Node(nil_, nil_, nil_, nil));
			}

			RBTree(const RBTree& rhs) : nil_(alloc_node_.allocate(1)), root_(nil_), comp_(rhs.comp_) {
				alloc_node_.construct(nil_, Node(nil_,nil_,nil_, nil));
				*this = rhs;
			}

	};
} // namespace ft

#endif
