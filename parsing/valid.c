/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:05:11 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/18 18:18:41y ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_error(t_shell *shell, int type)
{
	if (shell->err == ERR_SYNTAX)
		return ;
	shell->err = ERR_SYNTAX;
	if (type == PIPE)
		printf("minishell: syntax error near unexpected token `|'\n");
	else if (type == INPUT || type == OUTPUT || type == APPEND)
		printf("minishell: syntax error near unexpected token `newline'\n");
}

void	heredoc_error(t_shell *shell, int type, t_oken *next)
{
	if (shell->err == ERR_SYNTAX)
		return ;
	if (type == HEREDOC && next->type == END)
	{
		shell->err = ERR_SYNTAX;
		printf("minishell: syntax error near unexpected token `newline'\n");
	}
	else if (type == HEREDOC && next->type != END && next->type != ARGS)
	{
		shell->err = ERR_SYNTAX;
		printf("minishell: syntax error near unexpected token `%s'\n",
			next->value);
	}
}

void	redirect_error(t_shell *shell, int type, t_oken *next)
{
	if (shell->err == ERR_SYNTAX)
		return ;
	if ((type == OUTPUT || type == INPUT || type == APPEND)
		&& next->type != ARGS)
	{
		shell->err = ERR_SYNTAX;
		printf("minishell: syntax error near unexpected token `%s'\n",
			next->value);
	}
}

void	valid(t_shell *shell)
{
	t_oken	*token;
  


	token = shell->token;
  if (token->type != CMD && token->type != HEREDOC && token->next->type == END)
			first_error(shell, token->type);
	while (token->next)
	{
		
		if (token->type == HEREDOC)
			heredoc_error(shell, token->type, token->next);
		if ((token->type == OUTPUT || token->type == INPUT
				|| token->type == APPEND) && token->next->type != END)
			redirect_error(shell, token->type, token->next);
		if (token->type == PIPE && token->next->type == PIPE)
		{
			shell->err = ERR_SYNTAX;
			printf("minishell: syntax error near unexpected token `|'\n");
		}
		if (shell->err == ERR_SYNTAX)
			break ;
		token = token->next;
	}
   if (token->type == END)
    printf("%s %d", token->value, token->type);
  exit(0);
}
