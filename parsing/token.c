/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:19:32 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/19 23:52:29by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	token_type(char *s)
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

t_oken	*token_lst(t_shell *shell)
{
	int		i;
	char	*v;

	i = 0;
	while (shell->av[i])
	{
		v = shell->av[i];
		t_oken *new_token = ft_lstnew(ft_strdup(v), token_type(v));
		new_token->read = 0;
		if (i == 0 && token_type(v) == ARGS)
			ft_lstadd_back(&shell->token, new_token);
		else if (i > 0 && token_type(v) == ARGS && token_type(shell->av[i - 1]) == PIPE)
			ft_lstadd_back(&shell->token, new_token);
		else
			ft_lstadd_back(&shell->token, new_token);
		i++;
	}
	ft_lstadd_back(&shell->token, ft_lstnew(ft_strdup("END"), END));
	ft_lstadd_back(&shell->token, NULL);
	return (shell->token);
}

void	tokenize(t_shell *shell)
{
	shell->av = ft_token(spacing(shell->s), " \t\r\f\v");
	shell->token = token_lst(shell);
	valid(shell);
}
