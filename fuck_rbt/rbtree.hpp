#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <memory>
# include <stdexcept>
# include <algorithm>

typedef enum {red, black, nil} Color;

template <typename NodePtr>
inline bool tree_is_left_child(NodePtr node) noexcept {
	return node == node->parent_->left_;
}

/*
//Функция для определения является ли поддерево с корнем node правильным rbtree поддеревом.
//Если node -- правильное поддерево, то возращается черная высота (null считается за 1).
//Если node -- неправильное поддерево, то возвращается 0.
//ЗАМЕЧАНИЕ: ЕСЛИ ТЕКУЩАЯ NODE КРАСНАЯ, ТО НИ ОДИН ИЗ ДЕТЕЙ НЕ МОЖЕТ БЫТЬ КРАСНЫМ!
*/
template<typename NodePtr>
unsigned tree_sub_invariant(NodePtr node) {
	if (node == nullptr_t) {
		return 1;
	}
	if (node->left_ != nullptr_t && node->left_->parent_ != node) {
		return 0;
	}
	if (node->right_ != nullptr_t && node->right_->parent_ != node) {
		return 0;
	}
	if (node->left_ == node->right_ && node->left_ != nullptr_t) {
		return 0;
	}
	if (node->color_ == red) {
		if (node->left_ && node->left_->color_ == red) {
			return 0;
		}
		if (node->right_ && node->right_->color_ == red) {
			return 0;
		}
	}
	unsigned retval_hight_black = tree_sub_invariant(node->left_);
	if (retval_hight_black == 0) {
		return 0;
	}
	if (retval_hight_black != tree_sub_invariant(node->right_)) {
		return 0;
	}
	return retval_hight_black + node->color_ == black;
}

/*
//Функция для определения является ли дерево с корнем root правильным rbtree
//Возвращает true, если дерево правильное иначе false;
//ЗАМЕЧАНИЕ: ROOT == NULLPTR_T -- ПРАВИЛЬНОЕ ДЕРЕВО!
*/
template<typename NodePtr>
bool tree_invariant(NodePtr root) {
	if (root == nullptr_t) {
		return true;
	}
	if (root->parent_ == nullptr_t) {
		return false;
	}
	if (!tree_is_left_child(root)) {
		return false;
	}
	if (root->color_ != black) {
		return false;
	}
	return tree_sub_invariant(root) != 0;
}

/*
//Функция возвращает самый левый указатель под node.
//ЗАМЕЧАНИЕ: NODE != NULLPTR_T
*/
template<typename NodePtr>
inline NodePtr tree_min(NodePtr node) noexcept {
	while (node->left_ != nullptr_t) {
		node = node->left_;
	}
	return node;
}

/*
//Функция возвращает самый правый указатель под node
//ЗАМЕЧАНИЕ: NODE != NULLPTR_T
*/
template<typename NodePtr>
inline NodePtr tree_max(NodePtr node) noexcept {
	while (node->right_ != nullptr_t) {
		node = node->right_;
	}
	return node;
}

/*
//Функция возвращает указатель на следующий по порядку узел после node
//ЗАМЕЧАНИЕ: NODE != NULLPTR_T
*/
template<typename NodePtr>
NodePtr tree_next(NodePtr node) noexcept {
	if (node->right_ != nullptr_t) {
		return tree_min(node->right_);
	}
	while (!tree_is_left_child(node)) {
		node = node->parent_;
	}
	return node->parent_;
}

/*
//Функция возвращает указатель на предыдущий по порядку узел до node
//ЗАМЕЧАНИЕ: NODE != NULLPTR_T
*/
template <typename NodePtr>
NodePtr tree_prev(NodePtr node) noexcept {
	if (node->left_ != nullptr_t) {
		return tree_max(node->left_);
	}
	while (tree_is_left_child(node)) {
		node = node->parent_;
	}
	return node->parent_;
}

/*
//Функция возвращает указатель на node у которого нет потомков
//ЗАМЕЧАНИЕ: NODE != NULLPTR_T
*/
template<typename NodePtr>
NodePtr tree_leaf(NodePtr node) noexcept {
	while (node->left_ != nullptr_t && node->right_ != nullptr_t) {
		if (node->left_ != nullptr_t) {
			node = node->left_;
		} else {
			node = node->right_;
		}
	}
	return node;
}

/*
//Функция выполняет попрот дерева так, чтобы node->right стал корнем 
//поддерева с node -- его левым потомком при сохранении порядка.
//ЗАМЕЧАНИЕ: NODE->RIGHT !_ NULLPTR_T
*/
template<typename NodePtr>
void tree_left_rotate(NodePtr node) noexcept {
	NodePtr tmp = node->right_;
	node->right_ = tmp->left_;
	if (node->right_ != nullptr_t) {
		node->right_->parent_ = node;
	}
	tmp->parent_ = node->parent_;
	if (tree_is_left_child(node)) {
		node->parent_->left_ = tmp;
	} else {
		node->parent_->right_ = tmp;
	}
	tmp->left_ = node;
	node->parent_ = tmp;
}

/*
//Функция выполняет попрот дерева так, чтобы node->left стал корнем 
//поддерева с node -- его правым потомком при сохранении порядка.
//ЗАМЕЧАНИЕ: NODE->LEFT !_ NULLPTR_T
*/
template<typename NodePtr>
void tree_right_rotate(NodePtr node) noexcept {
	NodePtr tmp = node->left_;
	node->left_ = tmp->right_;
	if (node->left_ != nullptr_t) {
		node->left_->parent_ = node; 
	}
	tmp->parent_ = node->parent_;
	if (tree_is_left_child(node)) {
		node->parent_->left_ = tmp;
	} else {
		node->parent_->right_ = tmp;
	}
	tmp->right_ = node;
	node->parent_ = tmp;
}

/*
//Функция перебалансирует root после присоединения node к листу.
//
//ТРЕБОВАНИЯ: ROOT !=N ULLPTR_T && NODE != NULLPTR_T, NODE НЕ ИМЕЕТ ДОЧЕРНИХ ЭЛЕМЕНТОВ
//NODE == ROOT ИЛИ == ПРЯМОЙ ИЛИ КОСВЕННЫЙ ДОЧЕРНИЙ ЭЛЕМЕНТ ROOT
//ЕСЛИ БЫ NODE НУЖНО БЫЛО ОТСОЕДИНИТЬ ОТ ROOT (УСТАНОВИВ ROOT В NULLPTR_T, ЕСЛИ ROOT == NODE),
//TREE_INVARIANT(ROOT) == TRUE
//
//ПОСТУСЛОВИЕ: tree_invariant(end_node->left) == true.
//end_node->left_ может отличаться от значения, переданного как root.
*/
template <typename NodePtr>
void tree_balacnce_after_insert(NodePtr root, NodePtr node) noexcept {
	if (node == root) {
		node->color_ = black;
	}
	while ( node != root && !node->parent_->color_ == black) {
		if (tree_is_left_child(node->parent_)) {
			NodePtr tmp = node->parent_->parent_->right_;
			if (tmp != nullptr_t && !tmp->color_ == black) {
				node = node->parent_;
				node->color_ = black;
				node = node->parent_;
				if (node == root) {
					node->color_ = black;
				}
				tmp->color_ = black;
			} else {
				if (!tree_is_left_child(node)) {
					node = node->parent_;
					tree_left_rotate(node);
				}
				node = node->parent_;
				node->color_ = black;
				node = node->parent_;
				node->color_ = red;
				tree_right_rotate(node);
				break;
			}
		} else {
			NodePtr tmp = node->parent_->parent_->left_;
			if (node != nullptr_t && !node->color_ == black) {
				node = node->parent_;
				node->color_ = black;
				node = node->parent_;
				if (node == root) {
					node->color_ = black;
				}
				tmp->color_ = black;
			} else {
				if (tree_is_left_child(node)) {
					node = node->parent_;
					tree_right_rotate(node);
				}
				node = node->parent_;
				node->color_ = black;
				node = node->parent_;
				node->color_ = red;
				tree_left_rotate(node);
				break;
			}
		}
	}
}

/*
// Удаление элемента node из дерева с корнем root, балансировка по мере необходимости.
*/
template<typename NodePtr>
void tree_remove(NodePtr root, NodePtr node) noexcept {
	NodePtr y = (node->left_ == nullptr_t || node->right_ == nullptr_t) ? node : tree_next(node);
	NodePtr x = y->left_ != nullptr_t ? y->left_ : y->right_;
	NodePtr w = nullptr_t;























































#endif
