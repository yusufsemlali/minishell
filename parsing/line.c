/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:39:59 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/19 23:48:13 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	metachar(char c, char prev)
{
	return (prev != '\\' && ft_strchr("|;<>", c) != NULL);
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
			// if (s[i] == s[i - 1] && !inquotes(s, i, 0))
			//     new[j++] = s[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = s[i++];
	}
	return (new);
}
