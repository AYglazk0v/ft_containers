NAME	=	ft_container	

OBJ_DIR	=	.obj

SRCS	=	main.cpp

CFLAGS	=	-std=c++98 -Wall -Werror -Wextra -g

# CFLAGS	=	-std=c++98 -Wall -Werror -Wpedantic -Wextra -g
# CFLAGS	=	-std=c++17 -Wall -Werror -Wpedantic -Wextra -g

OBJ		= 	$(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))

CC		=	c++

RM		=	rm -rf

#HEADER	=

$(OBJ_DIR)/%.o:%.cpp $(HEADER)
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
