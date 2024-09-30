/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali & aclakhda <ysemlali & aclackd    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:06:04 by ysemlali &        #+#    #+#             */
/*   Updated: 2024/09/01 21:25:34 by ysemlali &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getcount(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (ft_isspace(*s))
		{
			count++;
			while (*s && ft_isspace(*s))
				s++;
		}
		if (*s)
		{
			count++;
			while (*s && !ft_isspace(*s))
				s++;
		}
	}
	return (count);
}

static char	*get_next_token(char **s, const char *d)
{
	char	*token;
	char	*dlem;

	dlem = ft_strjoin((char *)d, "\"\'");
	if (**s == '\"' || **s == '\'')
	{
		token = ft_strndup(*s + 1, ft_strchr(*s + 1, **s) - *s - 1);
		*s += ft_strchr(*s + 1, **s) - *s + 1;
	}
	else
	{
		token = ft_strndup(*s, ft_strcspn(*s, (char *)dlem));
		*s += ft_strcspn(*s, (char *)dlem);
	}
	return (free(dlem), token);
}

char	**ft_token(char *s, char *d)
{
	char	**new;
	char	*tmp;
	int		i;

	if (!s || !d)
		return (NULL);
	new = ft_calloc(getcount(s) * 2, sizeof(char *));
	tmp = s;
	i = 0;
	while (*s && ft_strchr(d, *s))
		s++;
	while (*s)
	{
		if (ft_isspace(*s))
		{
			while (*s && ft_strchr(d, *s))
				s++;
			if (!*s)
				break ;
			new[i++] = ft_strreplace(ft_strdup("#"), '#', - '#');
		}
		new[i++] = get_next_token(&s, d);
	}
	return (free(tmp), new[i] = NULL, new);
}
