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

int	t_type(char *s)
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
	else
		return (ARGS);
}

int	get_next_token(char **str, char *token)
{
	int		i;
	int		x;
	char	*s;

	i = 0;
	x = 0;
	s = *str;
	while (s[i])
	{
		while ((s[i] == '\"' || s[i] == '\'') && !inquotes(s, i, 0))
			x = s[i++];
		if (s[i] == '\0' || (ft_isspace(s[i]) && !inquotes(s, i, 0)))
			break ;
		if (s[i] != '\0' && x != s[i])
			ft_strlcat(token, s + i, ft_strlen(token) + 2);
		i++;
	}
	*str += i;
	if (x != 0)
		return (ARGS);
	return (t_type(token));
}

int	skip_whitespace(char **s)
{
	while (**s && ft_strchr(" \t\r\v\f", **s))
		(*s)++;
	if (!*s)
		return (-1);
	return (0);
}

void	lexer(t_shell *shell)
{
	char	token[BUFFER_SML];
	char	*s;
	int		i;
	int		type;

	i = 0;
	s = shell->s;
	i = 0;
	type = 0;
	ft_bzero(token, BUFFER_SML);
	skip_whitespace(&s);
	while (*s)
	{
		if (skip_whitespace(&s))
			break ;
		type = get_next_token(&s, token);
		if (i == 0 && type == ARGS)
			shell->token = ft_lstnew(ft_strdup(token), CMD, i++);
		else
			ft_lstadd_back(&shell->token, ft_lstnew(ft_strdup(token), type,
					i++));
		ft_bzero(token, BUFFER_SML);
	}
	ft_lstadd_back(&shell->token, ft_lstnew(ft_strdup("END"), END, i));
}
