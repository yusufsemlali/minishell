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

static int	is_delim(char c, const char *d)
{
	return (ft_strchr(d, c) != NULL);
}

static char	*extract_quoted(char **s, char quote)
{
	char	*start;
	char	*result;

	start = ++(*s);
	while (**s && (**s != quote || *(*s - 1) == '\\'))
		(*s)++;
	result = ft_strndup(start, *s - start);
	if (**s == quote)
		(*s)++;
	return (result);
}

static int	handle_free(char **new, int i)
{
	if (!new[i])
	{
		while (i-- > -1)
			free(new[i]);
		free(new);
		return (-1);
	}
	return (0);
}

char	**ft_token(char *s, char *d)
{
	char	**new;
	int		i;

	if (!s || !d)
		return (NULL);
	new = ft_calloc(ft_strlen(s) + 2, sizeof(char *));
	i = 0;
	while (*s)
	{
		while (*s && is_delim(*s, d))
			s++;
		if (!*s)
			break ;
		if (*s == '\"' || *s == '\'')
			new[i] = extract_quoted(&s, *s);
		else
		{
			new[i] = ft_strndup(s, ft_strcspn(s, d));
			s += ft_strcspn(s, d);
		}
		if (handle_free(new, i++) != 0)
			return (NULL);
	}
	return (new);
}
