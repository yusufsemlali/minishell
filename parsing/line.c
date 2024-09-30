/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:37:42 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/25 17:13:41 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	metachar(char c)
{
	return (ft_strchr("|<>", c) != NULL);
}

int	inquotes(char *s, int i, int x)
{
	int		one;
	int		two;
	char	*p;

	p = s;
	one = 0;
	two = 0;
	while (*p && p - s < i)
	{
		if (*p == '\'' && two % 2 == 0)
			one++;
		if (*p == '\"' && one % 2 == 0)
			two++;
		p++;
	}
	if (x == 1)
		return (one % 2 == 0 && two % 2 != 0);
	if (x == 2)
		return (one % 2 != 0 && two % 2 == 0);
	return (one % 2 != 0 || two % 2 != 0);
}

void	spacing(t_shell *shell)
{
	char	new[BUFFER_SIZE];
  char *s = shell->s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	bzero(new, BUFFER_SIZE);
	while (s[i] && i < BUFFER_SIZE)
	{
		if (s[i] == '$' && inquotes(s, i, 2))
			new[j++] = -s[i++];
		else if (metachar(s[i]) && !inquotes(s, i, 0))
		{
			new[j++] = ' ';
			new[j++] = s[i++];
			if (ft_strchr("<>", s[i]) && s[i] == s[i - 1] && !inquotes(s, i, 0))
				new[j++] = s[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = s[i++];
	}
  free(shell->s);
	shell->s = ft_strdup(new);
}
