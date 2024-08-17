/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:19:32 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/17 16:59:15 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	metachar(char c, char prev)
{
	if (prev != '\\' && (c == '|' || c == ';' || c == '<' || c == '>'
			|| c == '&' || c == '(' || c == ')' || c == '\n'))
		return (1);
	return (0);
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
		if (*p == '\'' && (p == s || *(p - 1) != '\\') && two % 2 == 0)
			one++;
		if (*p == '\"' && (p == s || *(p - 1) != '\\') && one % 2 == 0)
			two++;
		p++;
	}
	if (x == 1)
		return (one % 2 == 0 && two % 2 != 0);
	return (one % 2 != 0 || two % 2 != 0);
}

char	*new_line(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (i && metachar(s[i], s[i - 1]) && !inquotes(s, i, 0))
			count++;
		i++;
	}
	return (ft_calloc(i + (count * 2) + 1, sizeof(char)));
}

char	*spacing(char *s)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = new_line(s);
	while (s[i] && new)
	{
		if (s[i] == '$' && inquotes(s, i, 1) && i)
			new[j++] = -s[i++];
		else if (i && metachar(s[i], s[i - 1]) && !inquotes(s, i, 0))
		{
			new[j++] = ' ';
			new[j++] = s[i++];
			if (ft_strchr("<>|", s[i]) && !inquotes(s, i, 0))
				new[j++] = s[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = s[i++];
	}
	return (new);
}

void	tokenize(t_shell *shell)
{
	shell->s = spacing(shell->s);
	shell->av = ft_split(shell->s, ' ');
	// for (int i = 0; shell->av[i] != NULL; i++)
	// {
	// 	printf("[%s]\n", shell->av[i]);
	// }
}