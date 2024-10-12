/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:38:00 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/21 16:25:01 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_var(char *s, char *buf, t_env *nv)
{
	char	env[BUFFER_SML];
	char	*tmp;

	ft_bzero(env, BUFFER_SML);
	if (ft_strncmp(s, "$?", 2) == 0)
		return (ft_strlcat(buf, (tmp = ft_itoa(g_modes->exit_mode)),
				BUFFER_SML), free(tmp), 2);
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
	if (*s == '$' && !ft_isspace(*(s + 1)) && *(s + 1) != '/')
	{
		ft_strlcpy(env, s + 1, ft_strcspn(s + 1, "$ =\'\"\t\f\v\r/") + 1);
		ft_strlcat(buf, get_env(nv, env), BUFFER_SML);
		return (ft_strlen(env) + 1);
	}
	return (ft_strlcat(buf, s, ft_strlen(buf) + 2), 1);
}

char	*var(char *s, t_env *nv)
{
	char	buf[BUFFER_BIG];

	ft_bzero(buf, BUFFER_BIG);
	while (*s)
		s += get_var(s, buf, nv);
	return (ft_strdup(buf));
}

void	expand(t_shell *shell)
{
	char	*expand;

	expand = var(shell->s, shell->nv);
	if (*expand != 0)
	{
		free(shell->s);
		shell->s = ft_strreplace(expand, -'$', '$');
	}
}
