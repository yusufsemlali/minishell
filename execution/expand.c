/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:09:14 by ysemlali          #+#    #+#             */
/*   Updated: 2024/11/05 21:35:37 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_size(char *s, t_env *nv)
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

int	get_vars(char *s, char *buf, t_env *nv)
{
	char	env[1024];
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
	char	*buf;

	buf = ft_calloc(get_size(s, nv) + 1, 1);
	while (*s)
		s += get_vars(s, buf, nv);
	return (buf);
}
