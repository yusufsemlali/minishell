# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/25 21:41:51 by ysemlali          #+#    #+#              #
#    Updated: 2024/08/13 17:34:59 by aclakhda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -Llibft -lft -lreadline
SRCS =	main/minishell.c\
		main/init.c\
		main/signals.c \
		parsing/parse.c\
		parsing/token.c\
		execution/execute.c\
		execution/utils.c\
		execution/executing.c\
		execution/executing_utils.c\
		execution/build_in/echo.c\



OBJS = $(SRCS:.c=.o)
NAME = minishell
LIBFT_NAME = libft/libft.a

all: $(LIBFT_NAME) $(NAME)


$(LIBFT_NAME):
	@make -s -C libft all

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -s -C libft clean

fclean: clean
	@rm -f $(NAME)
	@make -s -C libft fclean

re: fclean all
	@make -s -C libft re

.PHONY: all clean fclean re
