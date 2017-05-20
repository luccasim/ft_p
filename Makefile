EXEC_1 	= client_srcs
EXEC_2 	= serveur_srcs
LIB		= libft

all:
	@make -C $(LIB) > /dev/null 2>&1
	@make -C $(EXEC_1) > /dev/null 2>&1
	@make -C $(EXEC_2) > /dev/null 2>&1
	ln -s $(EXEC_1)/client . > /dev/null 2>&1
	ln -s $(EXEC_2)/serveur . > /dev/null 2>&1

clean:
	@make -C $(LIB) clean > /dev/null 2>&1
	@make -C $(EXEC_1) clean > /dev/null 2>&1
	@make -C $(EXEC_2) clean > /dev/null 2>&1

fclean: clean
	/bin/rm client
	/bin/rm serveur

re: fclean all