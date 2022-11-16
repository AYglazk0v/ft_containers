#ifndef RB_NODE_HPP
# define RB_NODE_HPP

namespace ft {

	typedef enum { black, red, nil} NodeColor;

	template<typename Value>
	struct RB_Node {
		public:
			typedef RB_Node*	pointer;
			typedef RB_Node&	reference;

			pointer		parent_;
			pointer		left_;
			pointer		right_;
			NodeColor	type_;
			Value*		value_;

			RB_Node(pointer parent, pointer left, pointer right, NodeColor type = black, Value *value = NULL) :
					parent_(parent), left_(left), right_(right), type_(type), value_(value) { }
			
			RB_Node(const RB_Node &rhs) {
				*this = rhs;
			}

			RB_Node operator=(const RB_Node& rhs) {
				if (this == &rhs) {
					return *this;
				}
				parent_ = rhs.parent_;
				left_ = rhs.left_;
				right_ = rhs.right_;
				type_ = rhs.type_;
				value_ = rhs.value_;
				return *this;
			}
			
			~RB_Node() {}
	};

} //namespace ft

#endif
