#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luccasim <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/05 12:00:41 by luccasim          #+#    #+#              #
#    Updated: 2016/12/05 12:00:43 by luccasim         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= 	$(NAME1) $(NAME2)
NAME1 		=	serveur
NAME2		=	client
DEP_1		=	serveur_srcs/serveur
DEP_2		=	client_srcs/client

all: $(NAME)

$(NAME1): $(DEP_1)
	@cp $(DEP_1) .

$(NAME2): $(DEP_2)
	@cp $(DEP_2) .

$(DEP_1):
	@make -C serveur_srcs/

$(DEP_2):
	@make -C client_srcs/

clean:
	@make -C serveur_srcs/ clean
	@make -C client_srcs/ clean

fclean: clean
	@make -C serveur_srcs/ fclean
	@make -C client_srcs/ fclean
	@/bin/rm -rf $(NAME1)
	@/bin/rm -rf $(NAME2)

re: fclean all

.PHONY: re all clean fclean