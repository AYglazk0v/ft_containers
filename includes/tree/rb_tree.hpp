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

		private:
			void claer_node(node_pointer node) {
				if (node != nil) {

				}
			}

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

			RBTree& operator=(const RBTree& rhs) {
				if (this == &rhs) {
					return *this;
				}
				clear_node(root_);
				alloc_node_.destroy(nil_);
				alloc_node_.deallocate(nil_, 1);
				alloc_node_ = rhs.alloc_node_;
				alloc_val_ = rhs.alloc_val_;
				comp_ = rhs.comp_;
				nil_ = alloc_node_.allocate(1);
				alloc_node_.construct(nil_, *(rhs.nil_));
				root_ = nil_;
				if (rhs.size_ > 0) {
					root_ = copy_node(rhs.root_);
					root_->parent_ = nil_;
					copy_all(root_, rhs.root_);
				}
				size_ = rhs.size_;
				return *this;
			}

			~RBTree(){
				clear_node(root_);
				alloc_node_.deallocate(nil_, 1);
			}

			node_pointer copy_node(node_pointer other) {
				node_pointer new_node = alloc_node_.allocate(1);
				alloc_node_.construct(new_node, Node(other->parent_, other->left_, other->right_, other->type_));
				if (other->value_) {
					new_node->value_ = alloc_val_.allocate(1);
					alloc_val_.construct(new_node->value_, *(other->value_));
				}
				return new_node;
			}

			void copy_all(node_pointer node, node_pointer other) {
				if (other->left_->type_ == nil) {
					node->left_ = nil_;
				} else {
					node->left_ = copy_node(other->left_);
					node->left_->parent_ = node;
					copy_all(node->left_, other->left_);
				}
				if (other->right_->type_ == nil) {
					node->right_ = nil_;
				} else {
					node->right_ = copy_node(other->right_);
					node->right_->parent_ = node;
					copy_all(node->right_, other->right_);
				}
			}

	};
} // namespace ft

#endif
