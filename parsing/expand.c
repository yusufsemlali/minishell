/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:38:00 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/18 10:38:00 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env(t_env *nv, char *key)
{
	t_env	*tmp;

	tmp = nv;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	get_var(char *s, char *buf, t_env *nv)
{
	char	env[BUFFER_SIZE];

	ft_bzero(env, BUFFER_SIZE);
	if (ft_strncmp(s, "$?", 2) == 0)
		return (ft_strlcat(buf, ft_itoa(g_modes->exit_mode), 1024), 2);
	else if (ft_strncmp(s, "$$", 2) == 0)
		return (ft_strlcat(buf, ft_itoa(getpid()), BUFFER_SIZE), 2);
	else if (ft_strncmp(s, "$#", 2) == 0)
		return (ft_strlcat(buf, "0", BUFFER_SIZE), 2);
	else if (ft_strcmp(s, "$") == 0)
		return (ft_strlcat(buf, "$", BUFFER_SIZE), 1);
	else if (ft_strncmp(s, "$0", 2) == 0)
		return (ft_strlcat(buf, "minishell", BUFFER_SIZE), 2);
	else if (*s == '$' && !ft_isspace(*(s + 1)))
	{
		ft_strlcpy(env, s + 1, ft_strcspn(s + 1, "$ \t\f\v\r/") + 1);
		ft_strlcat(buf, get_env(nv, env), BUFFER_SIZE);
		return (ft_strlen(env) + 1);
	}
	return (ft_strlcat(buf, s, ft_strlen(buf) + 2), 1);
}

char	*var(char *s, t_env *nv)
{
	char	buf[BUFFER_SIZE];

	ft_bzero(buf, BUFFER_SIZE);
	ft_strlcpy(buf, s, ft_strcspn(s, "$") + 1);
	s += ft_strcspn(s, "$");
	while (*s)
		s += get_var(s, buf, nv);
	return (ft_strdup(buf));
}

void	expand(t_shell *shell)
{
	t_oken	*token;
	char	*expand;

	token = shell->token;
	while (token)
	{
		if (token->type == ARGS && (ft_strchr(token->value, -'$')) != NULL)
		{
			expand = var(ft_strreplace(token->value, -'$', '$'), shell->nv);
			if (expand)
			{
				free(token->value);
				token->value = expand;
			}
		}
		token = token->next;
	}
}
