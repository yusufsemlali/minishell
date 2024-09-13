/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali & aclakhda <ysemlali & aclackd    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:39:59 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/26 17:49:30 by ysemlali &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	metachar(char c, char prev)
{
  (void)prev;
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
  if (x == 2)
    return (one % 2 != 0 && two % 2 == 0);
	if (x == 1)
		return (one % 2 == 0 && two % 2 != 0);
	return (one % 2 != 0 || two % 2 != 0);
}
/*
int	new_line(char *s)
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
	// return (ft_calloc(i + (count * 2) + 1, sizeof(char)));
	return(i + (count * 2) + 1);
}
*/

/*
char *spacing(char *s)
{
  char new[ BUFFER_SIZE ];
  if (!s)
    return (ft_strdup(new));

  if (*s ==  

  spacing(s);
}
*/


char	*spacing(char *s)
{
	char	new[ BUFFER_SIZE ];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] )
	{
		if (s[i] == '$' && !inquotes(s, i, 2) && i)
			new[j++] = -s[i++];
		else if ( metachar(s[i], s[i - 1]) && !inquotes(s, i, 0))
		{
			new[j++] = ' ';
			new[j++] = s[i++];
			if (ft_strchr("<>", s[i]) && s[i] == s[i-1] && !inquotes(s, i, 0))
				new[j++] = s[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = s[i++];
	}
  new[j] = '\0';
	return(ft_strdup(new));
}

