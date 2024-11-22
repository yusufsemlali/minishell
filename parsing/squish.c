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
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] > 0)
		{
			s[j] = s[i];
			j++;
		}
		i++;
	}
	s[j] = '\0';
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
		token = next_token;
	}
}
