CC		=	llvm-gcc
CFLAGS	=	-Wall -Werror -Wextra
INC		=	-I includes -I ../libft/includes
SRC		=	$(shell find srcs -type f -name '*.c')
OBJ		=	$(patsubst %.c, $(DOBJ)/%.o, $(SRC))
DOBJ	=	objs
LIB		=	-L ../libft/ -lft
NAME	=	serveur

all: $(NAME)

$(NAME): $(DOBJ) $(OBJ)
	@make -C ../libft/ > /dev/null 2>&1
	$(CC) $(INC) -o $(NAME) $(OBJ) $(LIB)

$(DOBJ):
	@mkdir -p objs/srcs/ > /dev/null 2>&1

$(DOBJ)/%.o:%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	/bin/rm -rf $(DOBJ)

fclean: clean
	/bin/rm $(NAME)

re: fclean all

.PHONY: clean fclean re all