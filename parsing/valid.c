/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:38:43 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/21 22:01:38 by aclakhda         ###   ########.fr       */
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
		g_modes->exit_mode = 2;
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
	}
	else if (type == HEREDOC && next->type != END && next->type != ARGS)
	{
		shell->err = ERR_SYNTAX;
		g_modes->exit_mode = 2;
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(next->value, 2);
		ft_putstr_fd("'\n", 2);
	}
}

void	redirect_error(t_shell *shell, int type, t_oken *next)
{
	if (shell->err == ERR_SYNTAX)
		return ;
	if (type == INPUT && next->type == OUTPUT)
		return ;
	if ((type == OUTPUT || type == INPUT || type == APPEND)
		&& next->type != ARGS)
	{
		shell->err = ERR_SYNTAX;
		g_modes->exit_mode = 2;
		if (next->type == END)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token", 2);
			ft_putendl_fd("`newline'", 2);
		}
		else
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(next->value, 2);
			ft_putstr_fd("'\n", 2);
		}
	}
}

void	pipe_error(t_shell *shell, t_oken *next)
{
	if (shell->err == ERR_SYNTAX)
		return ;
	if (next->type == END || next->type == PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		shell->err = ERR_SYNTAX;
		g_modes->exit_mode = 2;
	}
}

void	valid(t_shell *shell)
{
	t_oken	*token;

	token = shell->token;
	while (token->next)
	{
		if (token->type == PIPE)
			pipe_error(shell, token->next);
		if (token->type == HEREDOC)
			heredoc_error(shell, token->type, token->next);
		if ((token->type == OUTPUT || token->type == INPUT
				|| token->type == APPEND) && token->next->type != ARGS)
			redirect_error(shell, token->type, token->next);
		if (ft_strcmp(token->value, "export") == 0 && token->next->type == ARGS)
			export_error(shell, token->next);
		if (shell->err == ERR_SYNTAX)
			break ;
		token = token->next;
	}
	ft_dellast(&shell->token, del);
}
