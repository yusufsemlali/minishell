/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:19:32 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/19 10:49:50 by aclakhda         ###   ########.fr       */
/*   Updated: 2024/08/19 22:26:01 by ysemlali         ###   ########.fr       */
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

char	*join_args(char **av, int i)
{
	char	*next;
	char	*joined;

	if (av[i + 1] == NULL || token_type(av[i + 1]) != ARGS)
		return (av[i]);
	else
	{
		next = join_args(av, i + 1);
		joined = ft_strjoin(av[i], next);
		if (next != av[i + 1])
			free(next);
		return (joined);
	}
}

void	token_value_type(char **av, int *i, int *type, char **value)
{
	*type = token_type(av[*i]);
	if (token_type(av[*i]) == ARGS)
		(*value) = join_args(av, *i);
}

t_oken	*token_lst(char **av)
{
	t_oken	*token;
	t_oken	*head;
	int		i;

	i = 0;
	head = NULL;
	while (av[i])
	{
		token = malloc(sizeof(t_oken));
		token_value_type(av, &i, &token->type, &token->value);
		if (token->value == NULL)
			return (NULL);
		token->next = NULL;
		if (head == NULL)
			head = token;
		// else
		// 	token_add_back(&head, token);
		i++;
	}
	return (head);
}

void	tokenize(t_shell *shell)
{
	shell->s = spacing(shell->s);
	// shell->s = validate(shell->s);
	shell->av = ft_split(shell->s, ' ');
}
