# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/25 21:41:51 by ysemlali          #+#    #+#              #
#    Updated: 2024/10/16 16:20:06 by aclakhda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBS = -Llibft -lft -lreadline
SRCS =	main/minishell.c  main/init.c main/free.c main/error.c  main/signals.c\
		    parsing/parse.c\
		    parsing/line.c\
				parsing/lexer.c\
				parsing/expand.c\
		    parsing/valid.c\
				parsing/token.c\
				parsing/export.c\
		    execution/utils.c\
				parsing/squish.c\
				execution/utils_2.c\
		    execution/executing.c\
		    execution/executing_utils.c\
		    execution/build_in/echo.c\
		    execution/build_in/cd.c\
		    execution/build_in/env.c\
				execution/build_in/exit.c\
		    execution/env_utils.c\
		    execution/build_in/pwd.c\
		    execution/build_in/export_unset.c\
		    execution/execute.c\
		    execution/rederextion.c\
		    execution/pipe.c\
				execution/tree_utils.c\
				execution/herdoc_utils.c\
				execution/export_utils.c\
				execution/cd_utils.c\
				execution/exit_pipe.c\
				execution/ft_rederction.c\
				execution/utils_3.c\
				execution/tree_u2.c\
				execution/im_gonna_kms.c\
				execution/bocchi_3.c\
				execution/help.c\

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
	@rm -rf $(OBJS)
	@make -s -C libft clean

fclean: clean
	@rm -f $(NAME)
	@make -s -C libft fclean

re: fclean all
	@make -s -C libft re

.PHONY: all clean fclean re
