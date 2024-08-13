/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:19:32 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/11 16:24:10 by ysemlali         ###   ########.fr       */
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

int	inquotes(const char *s, int i)
{
	int			one;
	int			two;
	const char	*ptr = s;

	one = 0;
	two = 0;
	while (*ptr && ptr - s < i)
	{
		if (*ptr == '\'' && (ptr == s || *(ptr - 1) != '\\') && two % 2 == 0)
			one++;
		if (*ptr == '\"' && (ptr == s || *(ptr - 1) != '\\') && one % 2 == 0)
			two++;
		ptr++;
	}
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
		if (s[i] == '$' && inquotes(s, i))
		{
			new[j++] = 'X';
			i++;
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