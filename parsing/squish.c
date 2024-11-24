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

void	normalize(char *s)
{
	char	*c;

	c = s;
	if (!s)
		return ;
	while (*s)
	{
		if (*s > 0)
			*c++ = *s;
		s++;
	}
	*c = '\0';
}

void	change_cmd_value(t_oken *token)
{
	if (token->value)
		free(token->value);
	token->value = ft_strdup("''");
}

void	squish(t_shell *shell)
{
	t_oken	*token;
	t_oken	*next_token;

	token = shell->token;
	shell->i = 0;
	while (token)
	{
		next_token = token->next;
		if (token->type == EMPTY)
			delete_token(shell, token);
		else
		{
			normalize(token->value);
			token->index = shell->i++;
		}
		if (token->type == CMD && *token->value == '\0')
			change_cmd_value(token);
		token = next_token;
	}
}
