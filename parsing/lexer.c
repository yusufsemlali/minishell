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

int	t_type(char *s, t_oken *prev)
{
	if (ft_strcmp(s, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(s, "<") == 0)
		return (INPUT);
	else if (ft_strcmp(s, ">") == 0)
		return (OUTPUT);
	else if (ft_strcmp(s, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(s, "<<") == 0)
		return (HEREDOC);
	else if (prev == NULL || (prev && prev->type == PIPE))
		return (CMD);
	return (ARGS);
}

char	*get_next_token(char **str)
{
	char	buf[BUFFER_SML];
	int		i;
	char	*s;

	i = 0;
	s = *str;
	ft_bzero(buf, BUFFER_SML);
	while (s[i])
	{
		if (ft_isspace(s[i]) && !inquotes(s, i, 0))
			break ;
		ft_strlcat(buf, s + i, ft_strlen(buf) + 2);
		i++;
	}
	*str += i;
	return (ft_strdup(buf));
}

int	skip_whitespace(char **s)
{
	while (**s && ft_strchr(" \t\r\v\f", **s))
		(*s)++;
	if (**s == '\0')
		return (-1);
	return (0);
}

void	lexer(t_shell *shell)
{
	char	*s;
	int		i;

	i = 0;
	s = shell->s;
	skip_whitespace(&s);
	while (*s)
	{
		if (skip_whitespace(&s) != 0)
			break ;
		ft_lstadd_back(&shell->token, ft_lnew(get_next_token(&s), 0, i,
				ft_lstlast(shell->token)));
		i++;
	}
}
