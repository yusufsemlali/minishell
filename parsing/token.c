/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:11:01 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/22 12:11:01 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	t_type(char *s)
{
	if (ft_strcmp(s, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(s, "<") == 0)
		return (INPUT);
	else if (ft_strcmp(s, ">") == 0)
		return (OUTPUT);
	else if (ft_strcmp(s, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(s, "<<") == 0)
		return (HEREDOC);
	else
		return (ARGS);
}

void	token_lst(t_shell *shell)
{
	int		i;
  int   t;
	char	*v;

	i = 0;
	while (shell->av[i])
	{
		v = shell->av[i];
    t = t_type(v);
		if (t == ARGS && i == 0)
			shell->token = ft_lstnew(ft_strdup(v), CMD, i);
		else if (i > 0 && t == ARGS && t_type(shell->av[i - 1]) == PIPE)
			ft_lstadd_back(&shell->token, ft_lstnew(ft_strdup(v), CMD,i));
		else
			ft_lstadd_back(&shell->token, ft_lstnew(ft_strdup(v), t, i));
		i++;
	}
	ft_lstadd_back(&shell->token, ft_lstnew(ft_strdup("END"), END,i));
}
