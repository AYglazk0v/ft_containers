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
            node_pointer tree_minimum(node_pointer node) const noexcept {
                while (node != nil_ && node->left_ != nil_) {
                    node = node->left_;
                }
                return node;
            }

			node_pointer tree_maximum(node_pointer node) const noexcept {
				while (node != nil && node->right_ != nil_) {
					node = node->right_;
				}
				return node;
			}

			void clear() {
				destroy(root_);
				root_= nil_->parent_ = nil_;
				size_ = 0;
			}

			void destroy(node_pointer node) {
				if (node != nil_) {
					destroy(node->right_);
					destroy(node->left_);
					alloc_val_.destroy(node->value_);
					alloc_val_.deallocate(node->value_, 1);
					alloc_node_.deallocate(node, 1);
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
				destroy(root_);
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
				destroy(root_);
				alloc_node_.deallocate(nil_, 1);
			}

			bool empty() const { return size_ == 0; }
			size_type size() const { return size_; }
			size_type max_size() const { return alloc_val_.max_size(); }

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

			iterator end() noexcept { return iterator(tree_maximum(root_)); }
			const_iterator end() const noexcept { return const_iterator(tree_maximum(root_)); }
			iterator begin() noexcept { return iterator(tree_minimum(root_)); }
			const_iterator begin() const noexcept { return const_iterator(tree_minimum(root_)); }
			reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
			const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
			reverse_iterator rend() noexcept { return reverse_iterator(begin()) ;}
			const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()) ;}

			void swap(RBTree &rhs) {
				node_pointer tmp_nil = nil_;
				node_pointer tmp_root = root_;
				Compare tmp_cmp = comp_;
				size_t tmp_sz = size_;
				
				nil_ = rhs.nil_;
				root_ = rhs.root_;
				comp_ = rhs.comp_;
				size_ = rhs.size_;
				
				rhs.nil_ = tmp_nil;
				rhs.root_ = tmp_root;
				rhs.comp_ = tmp_cmp;
				rhs.size_ - tmp_sz;
			}

			ft::pair<node_pointer, bool> insert(const value_type& val) {
				node_pointer curr = root_;
				node_pointer parent = nil_;
				node_pointer insert_elem;

				while (curr != nil_) {
					parent = curr;
					if (comp_(val, *(parent->value_))) {
						curr = curr->left_;
					} else if (comp_(*(parent->value_),val)) {
						curr = curr->right_;
					} else {
						return ft::pair<node_pointer, bool>(curr, false);
					}
				}
				pointer new_val = alloc_val_.allocate(1);
				alloc_val_.construct(new_val, val);
				insert_elem = alloc_node_.allocate(1);
				alloc_node_.construct(insert_elem, Node(parent, nil_, nil_, red, new_val));

				if (parent != nil_) {
					if (comp_(val, *(parent->value_))) {
						parent->left_ = insert_elem;
					} else {
						parent->right_ = insert_elem;
					}
				} else {
					root_ = insert_elem;
					nil_->parent_ = insert_elem;
				}

				nil_->parent_ = tree_maximum(root_);
				insert_fixup(insert_elem);
				++size_;
				return ft::pair<node_pointer, bool>(insert_elem, true);
			
			}
	};
} // namespace ft

#endif
