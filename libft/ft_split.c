/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 06:58:31 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/20 07:05:19 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	freeall(char **result, size_t count)
// {
// 	size_t	i;

// 	if (result[count] == NULL)
// 	{
// 		i = 0;
// 		while (i < count)
// 			free(result[i++]);
// 		free(result);
// 		return (0);
// 	}
// 	return (1);
// }

// static size_t	ft_wordlen(const char *s, char c)
// {
// 	size_t	len;

// 	len = 0;
// 	while (s[len] && s[len] != c)
// 		len++;
// 	return (len);
// }

// static size_t	ft_count_words(const char *s, char c)
// {
// 	size_t	count;
// 	size_t	i;

// 	count = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c)
// 		{
// 			count++;
// 			i += ft_wordlen(&s[i], c);
// 		}
// 		else
// 			i++;
// 	}
// 	return (count);
// }

// char	**ft_split(const char *s, char c)
// {
// 	char	**result;
// 	size_t	i;
// 	size_t	j;

// 	if (!s)
// 		return (NULL);
// 	result = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c)
// 		{
// 			result[j] = ft_substr(s, i, ft_wordlen(&s[i], c));
// 			if (freeall(result, j) != 1)
// 				return (NULL);
// 			j++;
// 			i += ft_wordlen(&s[i], c);
// 		}
// 		else
// 			i++;
// 	}
// 	return (result[j] = NULL, result);
// }

static int	is_delim(char c, const char *d)
{
	return (ft_strchr(d, c) != NULL);
}

static char	*extract_quoted(char **s, char quote)
{
	char	*start;

	start = ++(*s);
	while (**s && (**s != quote || *(*s - 1) == '\\'))
		(*s)++;
	if (**s == quote)
		(*s)++;
	return (ft_strndup(start, *s - start - 1));
}

static int	handle_free(char **new, int i)
{
	if (!new[i])
	{
		while (i-- > 0)
			free(new[i]);
		free(new);
		return (0);
	}
	return (1);
}

char	**ft_split(char *s, char *d)
{
	char	**new;
	int		i;

	if (!s || !d)
		return (NULL);
	new = ft_calloc(ft_strlen(s) / 2 + 2, sizeof(char *));
	i = 0;
	while (new && *s)
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
		if (!handle_free(new, i++))
			return (NULL);
	}
	return (new);
}
