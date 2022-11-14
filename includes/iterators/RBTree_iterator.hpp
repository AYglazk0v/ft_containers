#ifndef RBTREE_ITERATOR_HPP
# define RBTREE_ITERATOR_HPP

# include "../tree/rb_node.hpp"
# include "iterator.hpp"

namespace ft {
	template<typename T> struct remove_const {typedef T type; };
	template<typename T> struct remove_const<const T> : remove_const<T>{};

	template<typename T>
	class RBTree_iterator {		
		public:
			typedef T															value_type;
			typedef T*															pointer;
			typedef T&															reference;
			typedef std::bidirectional_iterator_tag								iterator_category;
			typedef std::ptrdiff_t												difference_type;
			
			typedef typename ft::remove_const<value_type>::type					clear_value_type;
			typedef RB_Node<clear_value_type>									Node;
			typedef Node*														node_ptr;

		private:
			node_ptr node_;

		public:
			RBTree_iterator() {}

			RBTree_iterator(node_ptr node): node_(static_cast<node_ptr>(node)) {}

			RBTree_iterator(const RBTree_iterator<clear_value_type>& rhs) {
				*this = rhs;
			}

			RBTree_iterator& operator=(const RBTree_iterator<clear_value_type>& rhs) {
				node_ = rhs.node_();
				return *this;
			}

			node_ptr node() const {
				return node_;
			}

			reference operator*() const {
				return *(node_->value_);
			}

			pointer operator->() const {
				return &(operator*());
			}

			RBTree_iterator& operator++() {
				next();
				return (*this);
			}

			RBTree_iterator operator++(int) {
				RBTree_iterator tmp(*this);
				next();
				return (tmp);
			}

			RBTree_iterator& operator--() {
				previous();
				return (*this);
			}

			RBTree_iterator operator--(int) {
				RBTree_iterator tmp(*this);
				previous();
				return (tmp);
			}

			template<typename Iterator1, typename Iterator2>
			friend bool operator==(const RBTree_iterator<Iterator1>& lhs, const RBTree_iterator<Iterator2>& rhs);

			template<typename Iterator1, typename Iterator2>
			friend bool operator!=(const RBTree_iterator<Iterator1>& lhs, const RBTree_iterator<Iterator2>& rhs);

		private:
			node_ptr maximum(node_ptr node) const {
				while (node->right_->type != nil) {
					node = node->right_;
				}
				return node;
			}

			node_ptr minimum(node_ptr node) const {
				while (node->left_->type_ != nil) {
					node = node->left_;
				}
				return node;
			}

			void next() {
				if (node_->type_ == nil) {
					return ;
				}
				if (node_->right_->type_ != nil) {
					node_ = minimum(node_->right_);
					return ;
				}
				node_ptr tmp = node_->parent_;
				while (tmp->type_ != nil && node_ == tmp->right_) {
					node_ = tmp;
					tmp = tmp->parent_;
				}
				node_ = tmp;
			}

			void previous() {
				if (node_->type_ == nil) {
					node_ = node_->parent_;
					return ;
				}
				if (node_->type_ != nil && node_->left_->type_ != nil) {
					node_ = maximum(node_->left_);
					return ;
				}
				node_ptr tmp = node_->parent_;
				while (tmp->type_ != nil && node_ == tmp->left_) {
					node_ = tmp;
					tmp = tmp->parent_;
				}
				if (tmp->type_ != nil) {
					node_ = tmp;
				}
			}
	};

	template<typename Iterator1, typename Iterator2>
	bool operator==(const RBTree_iterator<Iterator1>& lhs, const RBTree_iterator<Iterator2>& rhs) {
		return (lhs.node() == rhs.node());
	}

	template<typename Iterator1, typename Iterator2>
	bool operator!=(const RBTree_iterator<Iterator1>& lhs, const RBTree_iterator<Iterator2>& rhs) {
		return (lhs.node() != rhs.node());
	}



	template<typename T>
	class RBTree_const_iterator {		
		public:
			typedef T															value_type;
			typedef const T*													pointer;
			typedef const T&													reference;
			typedef std::bidirectional_iterator_tag								iterator_category;
			typedef std::ptrdiff_t												difference_type;
			
			typedef typename ft::remove_const<value_type>::type					clear_value_type;
			typedef RB_Node<clear_value_type>									Node;
			typedef const Node*													node_ptr;

		private:
			node_ptr node_;

		public:
			RBTree_const_iterator() {}

			RBTree_const_iterator(node_ptr node): node_(static_cast<node_ptr>(node)) {}

			RBTree_const_iterator(const RBTree_iterator<clear_value_type>& rhs) {
				*this = rhs;
			}

			RBTree_const_iterator& operator=(const RBTree_iterator<clear_value_type>& rhs) {
				node_ = rhs.node_();
				return *this;
			}

			node_ptr node() const {
				return node_;
			}

			reference operator*() const {
				return *(node_->value_);
			}

			pointer operator->() const {
				return &(operator*());
			}

			RBTree_const_iterator& operator++() {
				next();
				return (*this);
			}

			RBTree_const_iterator operator++(int) {
				RBTree_const_iterator tmp(*this);
				next();
				return (tmp);
			}

			RBTree_iterator& operator--() {
				previous();
				return (*this);
			}

			RBTree_iterator operator--(int) {
				RBTree_const_iterator tmp(*this);
				previous();
				return (tmp);
			}

			template<typename Iterator1, typename Iterator2>
			friend bool operator==(const RBTree_const_iterator<Iterator1>& lhs, const RBTree_const_iterator<Iterator2>& rhs);

			template<typename Iterator1, typename Iterator2>
			friend bool operator!=(const RBTree_const_iterator<Iterator1>& lhs, const RBTree_const_iterator<Iterator2>& rhs);

		private:
			node_ptr maximum(node_ptr node) const {
				while (node->right_->type != nil) {
					node = node->right_;
				}
				return node;
			}

			node_ptr minimum(node_ptr node) const {
				while (node->left_->type_ != nil) {
					node = node->left_;
				}
				return node;
			}

			void next() {
				if (node_->type_ == nil) {
					return ;
				}
				if (node_->right_->type_ != nil) {
					node_ = minimum(node_->right_);
					return ;
				}
				node_ptr tmp = node_->parent_;
				while (tmp->type_ != nil && node_ == tmp->right_) {
					node_ = tmp;
					tmp = tmp->parent_;
				}
				node_ = tmp;
			}

			void previous() {
				if (node_->type_ == nil) {
					node_ = node_->parent_;
					return ;
				}
				if (node_->type_ != nil && node_->left_->type_ != nil) {
					node_ = maximum(node_->left_);
					return ;
				}
				node_ptr tmp = node_->parent_;
				while (tmp->type_ != nil && node_ == tmp->left_) {
					node_ = tmp;
					tmp = tmp->parent_;
				}
				if (tmp->type_ != nil) {
					node_ = tmp;
				}
			}
	};

	template<typename Iterator1, typename Iterator2>
	bool operator==(const RBTree_const_iterator<Iterator1>& lhs, const RBTree_const_iterator<Iterator2>& rhs) {
		return (lhs.node() == rhs.node());
	}

	template<typename Iterator1, typename Iterator2>
	bool operator!=(const RBTree_const_iterator<Iterator1>& lhs, const RBTree_const_iterator<Iterator2>& rhs) {
		return (lhs.node() != rhs.node());
	}
	
} // namespace ft

#endif