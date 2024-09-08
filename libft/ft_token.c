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
static char	*extract_quoted(char **s, char quote)
{
	char	*start;
	char	*result;

	start = ++(*s);
	while (**s && (**s != quote || *(*s - 1) == '\\'))
		(*s)++;
	result = ft_strndup(start, *s - start);
	if (**s == quote)
		(*s)++; // Move past the closing quote
	return (result);
}

static char	*get_next_token(char **s, const char *d)
{
	char	*token;

	if (**s == '\"' || **s == '\'')
		token = extract_quoted(s, **s);
	else
	{
		token = ft_strndup(*s, ft_strcspn(*s, d));
		*s += ft_strcspn(*s, d);
	}
	return (token);
}

char	**ft_token(char *s, char *d)
{
	char	**new;
	char	*tmp;
	int		i;

	if (!s || !d)
		return (NULL);
	new = ft_calloc(ft_strlen(s) + 2, sizeof(char *));
	tmp = s;
	if (!new)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && ft_strchr(d, *s))
			s++;
		if (!*s)
			break ;
		new[i] = get_next_token(&s, d);
		if (handle_free(new, i++) != 0)
			return (NULL);
	}
	return (free(tmp), s = NULL, new);
}
