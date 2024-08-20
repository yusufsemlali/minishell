# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/25 21:41:51 by ysemlali          #+#    #+#              #
#    Updated: 2024/08/20 07:17:09 by ysemlali         ###   ########.fr        #
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
		parsing/line.c\
		parsing/valid.c\
		execution/execute.c\
		execution/utils.c\
		execution/executing.c\
		execution/executing_utils.c\
		execution/build_in/echo.c\
		execution/utils.c\
		execution/build_in/cd.c\
		execution/build_in/env.c\
		execution/env_utils.c\
		execution/build_in/pwd.c\
		execution/build_in/export_unset.c\
		execution/execute.c\



OBJS = $(SRCS:.c=.o)
NAME = minishell
LIBFT_NAME = libft/libft.a

all: $(LIBFT_NAME) $(NAME) clean


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
