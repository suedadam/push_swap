# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 01:09:10 by asyed             #+#    #+#              #
#    Updated: 2017/12/22 14:21:45 by suedadam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CFLAGS += -Wall -Werror -Wextra

SRC = main.c \
		bulk_ops.c \
		ll_utils.c \
		revrot.c \
		rot.c \
		sort_check.c \
		swap.c \
		utils.c \
		res_assist.c \

LIBFT = libft/

all: $(NAME)

DEBUG:
	@make -C $(LIBFT)
	@gcc $(CFLAGS) $(SRC) $(LIBFT)/libft.a -I $(LIBFT) -DDEBUG -o $(NAME)
	@echo "\033[32mBuilt DEBUG\033[0m"

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