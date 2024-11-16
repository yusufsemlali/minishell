/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 22:42:13 by ysemlali          #+#    #+#             */
/*   Updated: 2024/11/15 22:42:13 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_token(t_shell *shell, t_oken *token)
{
	if (token->prev)
		token->prev->next = token->next;
	else
		shell->token = token->next;
	if (token->next)
		token->next->prev = token->prev;
	ft_lstdelone(token);
}

void	delete_pipe_and_empty(t_shell *shell, t_oken **token)
{
	t_oken	*to_delete;
	t_oken	*prev_token;

	to_delete = *token;
	if (to_delete->prev && to_delete->prev->type == PIPE)
	{
		prev_token = to_delete->prev;
		delete_token(shell, prev_token);
	}
	prev_token = to_delete->next;
	delete_token(shell, to_delete);
	*token = prev_token;
}

void	squish(t_shell *shell)
{
	t_oken	*token;

	token = shell->token;
	shell->i = 0;
	while (token)
	{
		if (token->type == EMPTY)
			delete_pipe_and_empty(shell, &token);
		else
		{
			token->index = shell->i++;
			token = token->next;
		}
	}
}
