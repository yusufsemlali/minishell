/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:07:02 by ysemlali          #+#    #+#             */
/*   Updated: 2024/11/06 16:07:02 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_variable_size(char *s, t_env *nv)
{
	int		len;
	char	env[BUFFER_SML];

	len = 0;
	while (*s)
	{
		if (ft_strncmp(s, "$?", 2) == 0)
			len += get_num_len(g_modes.exit_mode);
		if (ft_strncmp(s, "$$", 2) == 0)
			len += 2;
		if (ft_strncmp(s, "$#", 2) == 0 || ft_strncmp(s, "\"$\"", 3) == 0)
			len++;
		if (ft_strncmp(s, "$0", 2) == 0)
			len += ft_strlen("minishell");
		if (*s == '$' && (ft_isspace(*(s + 1)) || *(s + 1) == '\0'))
			len++;
		if (*s == '$' && !ft_isspace(*(s + 1)) && *(s + 1) != '/')
		{
			ft_strlcpy(env, s + 1, ft_strcspn(s + 1, "$ =\'\"\t\f\v\r/") + 1);
			len += (ft_strlen(get_env(nv, env)));
		}
		len++;
		s++;
	}
	return (len);
}

int	basic_env(char *s, char *buf)
{
	char	*tmp;

	if (ft_strncmp(s, "$?", 2) == 0)
		return (ft_strlcat(buf, (tmp = ft_itoa(g_modes.exit_mode)), BUFFER_SML),
			free(tmp), 2);
	if (ft_strncmp(s, "$$", 2) == 0)
		return (ft_strlcat(buf, "$$", BUFFER_SML), 2);
	if (ft_strncmp(s, "$#", 2) == 0)
		return (ft_strlcat(buf, "0", BUFFER_SML), 2);
	if (ft_strncmp(s, "\"$\"", 3) == 0)
		return (ft_strlcat(buf, "$", BUFFER_SML), 3);
	if (ft_strncmp(s, "$0", 2) == 0)
		return (ft_strlcat(buf, "minishell", BUFFER_SML), 2);
	if (*s == '$' && (ft_isspace(*(s + 1)) || *(s + 1) == '\0'))
		return (ft_strlcat(buf, "$", BUFFER_SML), 1);
	return (0);
}

int	get_variables(char *s, char *buf, t_env *nv, int prev)
{
	char	env[1024];
	int		i;

	i = basic_env(s, buf);
	if (i != 0)
		return (i);
	if (*s == '$' && !ft_isspace(*(s + 1)) && *(s + 1) != '/')
	{
		ft_strlcpy(env, s + 1, ft_strcspn(s + 1, "$ =\'\"\t\f\v\r/") + 1);
		if (get_env(nv, env) == NULL && (prev == HEREDOC || prev == INPUT
				|| prev == OUTPUT || prev == APPEND))
		{
			ft_strlcat(buf, "$", BUFFER_SML);
			ft_strlcat(buf, env, BUFFER_SML);
		}
		ft_strlcat(buf, get_env(nv, env), BUFFER_SML);
		return (ft_strlen(env) + 1);
	}
	return (ft_strlcat(buf, s, ft_strlen(buf) + 2), 1);
}

char	*expanding(char *s, t_oken *prev, t_env *nv)
{
	char	*buf;

	buf = ft_calloc(get_variable_size(s, nv) + 2, 1);
	if (buf)
	{
		while (*s)
		{
			if (prev)
				s += get_variables(s, buf, nv, prev->type);
			else
				s += get_variables(s, buf, nv, -1);
		}
	}
	return (buf);
}

void	expand(t_shell *shell)
{
	t_oken	*token;
	char	*new;

	token = shell->token;
	while (token)
	{
		token->type = t_type(token->value, token->prev);
		new = expanding(token->value, token->prev, shell->nv);
		new = quotes(new);
		if (new)
		{
			free(token->value);
			token->value = new;
		}
		token->value = ft_strreplace(token->value, - '$', '$');
		token = token->next;
	}
}
