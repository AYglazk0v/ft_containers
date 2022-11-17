NAME	=	ft_container	

OBJ_DIR	=	.obj

SRCS	=	main.cpp

# CFLAGS	=	-std=c++98 -Wall -Werror -Wextra -g -I ./includes/ -fsanitize=address
CFLAGS	=	-std=c++98 -Wall -Werror -Wextra -g -I ./includes/

OBJ		= 	$(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))

CC		=	c++

RM		=	rm -rf

HEADER	= 	./includes/map.hpp \
			./includes/set.hpp \
			./includes/stack.hpp \
			./includes/vector.hpp \
			./includes/vector.hpp \
			./includes/utils/utils.h \
			./includes/utils/pair.hpp \
			./includes/utils/nullptr.hpp \
			./includes/utils/lexicographical_cmp.hpp \
			./includes/utils/is_iter.hpp \
			./includes/utils/is_integral.hpp \
			./includes/utils/equal.hpp \
			./includes/utils/enableif.hpp \
			./includes/tree/rb_tree.hpp \
			./includes/tree/rb_node.hpp \
			./includes/iterators/iterator_random_access.hpp \
			./includes/iterators/iterator_reverse.hpp \
			./includes/iterators/iterator.hpp \
			./includes/iterators/iterator.hpp \
			./includes/iterators/RBTree_iterator.hpp

$(OBJ_DIR)/%.o:%.cpp ${HEADER}
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY	:	all clean fclean re

all		:	$(NAME) 

$(NAME)	:	$(OBJ)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean	:
	@$(RM) $(OBJ_DIR)

fclean	:	clean
	@$(RM) $(NAME)
	@$(RM) .vscode

re		: fclean all
