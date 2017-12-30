# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 01:09:10 by asyed             #+#    #+#              #
#    Updated: 2017/12/22 14:23:52 by suedadam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = checker

CFLAGS += -Wall -Werror -Wextra

SRC = main.c \
		revrot.c \
		rot.c \
		swap.c \

LIBFT = libft/

all: $(NAME)

$(NAME):
	@make -C $(LIBFT)
	@gcc $(CFLAGS) $(SRC) $(LIBFT)/libft.a -I $(LIBFT) -o $(NAME)
	@echo "\033[32mBuilt\033[0m"

clean:
	@/bin/rm -f $(NAME)
	@make clean -C $(LIBFT)
	@echo "\033[32mCleaned\033[0m"

fclean:
	@/bin/rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@echo "\033[32mRemoved Executable\033[0m"

re: clean all