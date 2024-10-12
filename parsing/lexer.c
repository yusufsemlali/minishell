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


static char	*get_next_token(char **s, const char *dlem)
{
	char	*token;

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
	return (token);
}

void	lexer(t_shell *shell)
{
	char	**new;
	char	*s;
	int		i;

	new = ft_calloc(getcount(shell->s) * 2, sizeof(char *));
	i = 0;
	s = shell->s;
	while (*s && ft_strchr(" \t\r\v\f", *s))
		s++;
	while (*s)
	{
		if (ft_isspace(*s))
		{
			while (*s && ft_strchr(" \t\r\v\f", *s))
				s++;
			if (!*s)
				break ;
			new[i++] = ft_strreplace(ft_strdup("#"), '#', - '#');
		}
		new[i++] = get_next_token(&s, " \t\r\v\f\"\'");
	}
	new[i] = NULL;
	shell->av = new;
}
