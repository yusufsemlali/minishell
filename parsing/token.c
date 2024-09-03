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
	else if (ft_strcmp(s, "&") == 0)
		return (AND);
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
		v = shell->av[i++];
		ft_lstadd_back(&shell->token, ft_lstnew(v, token_type(v)));
	}
	shell->av = NULL;
	return (shell->token);
}

void	tokenize(t_shell *shell)
{
	shell->s = spacing(shell->s);
	if (shell->s == NULL)
		return ;
	shell->av = ft_token(shell->s, " \t\r\f\v");
	for (int i = 0; shell->av[i]; i++)
		printf("av[%d]: %s\n", i, shell->av[i]);
	// shell->token = token_lst(shell);
	// shell->av = NULL;
}
