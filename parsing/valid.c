/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:38:43 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/21 18:10:25 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (next->type == END)
			printf("minishell: syntax error near unexpected token `newline'\n");
		else
			printf("minishell: syntax error near unexpected token `%s'\n",
				next->value);
	}
}

void	pipe_error(t_shell *shell, t_oken *next)
{
	if (shell->err == ERR_SYNTAX)
		return ;
	if ((next->type != CMD && next->type != HEREDOC) || next->type == END)
	{
		printf("next->type: %d\n", next->type);
		shell->err = ERR_SYNTAX;
		if (next->type == END)
			printf("minishell: syntax error near unexpected token `|'\n");
		else
			printf("minishell: syntax error near unexpected token `%s'\n",
				next->value);
	}
}

// void	valid(t_shell *shell)
// {
// 	t_oken	*token;

// 	token = shell->token;
// 	while (token->next)
// 	{
// 		if (token->type == PIPE)
// 			pipe_error(shell, token->next);
// 		if (token->type == HEREDOC)
// 			heredoc_error(shell, token->type, token->next);
// 		if ((token->type == OUTPUT || token->type == INPUT
// 				|| token->type == APPEND) && token->next->type != ARGS)
// 			redirect_error(shell, token->type, token->next);
// 		if (shell->err == ERR_SYNTAX)
// 			break ;
// 		token = token->next;
// 	}
// 	ft_dellast(&shell->token, del);
// }
