/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:19:32 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/14 18:07:50 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	seperator(char c, char prev)
{
	if (prev != '\\' && (c == '|' || c == ';' || c == '<' || c == '>'))
		return (1);
	return (0);
}

char	*new_line(char *s)
{
	int		i;
	int		count;
	char	*new;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (seperator(s[i], s[i + 1]) && i > 0)
			count++;
		i++;
	}
	new = malloc(i + (count * 2) + 1);
	return (new);
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

char	*spacing(char *s)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = new_line(s);
	while (new &&s[i])
	{
		if (s[i] == '$' && inquotes(s, i, 1))
			new[j++] = -s[i++];
		else if (seperator(s[i], s[i - 1]) && i > 0 && !inquotes(s, i, 0))
		{
			new[j++] = ' ';
			new[j++] = s[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = s[i++];
	}
	new[j] = '\0';
	return (new);
}

void	tokenize(t_shell *shell)
{
	shell->line = spacing(shell->line);
	printf("\n%s\n", shell->line);
	shell->av = ft_split(shell->line, ' ');
}