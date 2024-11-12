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

#include "../includes/minishell.h"

char *get_next_token(char **str)
{
	char	buf[BUFFER_SML];
    int     i;
    char    *s;

    i = 0;
    s = *str;
  ft_bzero(token,BUFFER_SML );

    while (s[i])
    {
        if (ft_isspace(s[i]) && !inquotes(s, i, 0))
            break;
        ft_strlcat(token, s + i, ft_strlen(token) + 2);
        i++;
    }

    *str += i;
    return ft_strdup(token);
}

int	skip_whitespace(char **s)
{
	while (**s && ft_strchr(" \t\r\v\f", **s))
		(*s)++;
	if (**s == '\0')
		return (-1);
	return (0);
}

static size_t	ft_wordlen(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}


static size_t	ft_word_count(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			i += ft_wordlen(&s[i], c);
		}
		else
			i++;
	}
	return (count);
}

void	lexer(t_shell *shell)
{
	char	*s;
	int		i;

	i = 0;
	s = shell->s;
	shell->av = ft_calloc((ft_word_count(s, ' ') + 1), sizeof(char *));
  if(shell->av == NULL)
    return;
	skip_whitespace(&s);
	while (*s)
	{
		if (skip_whitespace(&s) != 0)
			break ;
		shell->av[i++] = get_next_token(&s);
	}
}
