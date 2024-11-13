/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:52:31 by ysemlali          #+#    #+#             */
/*   Updated: 2024/11/12 20:52:31 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	squish(t_shell *shell)
{
	t_oken	*token;
	t_oken	*prev;
	t_oken	*to_delete;

	token = shell->token;
	prev = NULL;
	while (token)
	{
		if (token->type == EMPTY)
		{
			to_delete = token;
			if (prev)
				prev->next = token->next;
			else
				shell->token = token->next;
			token = token->next;
			ft_lstdelone(to_delete);
		}
		else
		{
			prev = token;
			token = token->next;
		}
	}
}
