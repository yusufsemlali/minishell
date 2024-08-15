/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:56:29 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/14 20:00:58 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	old_pwd(char **nv)
{
	int	i;

	i = 0;
	while (nv[i])
	{
		if (ft_strncmp(nv[i], "OLDPWD=", 7) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	init_env(t_shell **shell, char **nv)
{
	int	i;

	i = 0;
	while (nv[i])
		i++;
	(*shell)->nv = ft_calloc(i + old_pwd(nv) + 1, sizeof(t_env));
	i = 0;
	while (nv[i])
	{
		(*shell)->nv[i].key = ft_strndup(nv[i], ft_strchr(nv[i], '=') - nv[i]);
		(*shell)->nv[i].value = getenv((*shell)->nv[i].key);
		i++;
	}
	if (old_pwd(nv))
	{
		(*shell)->nv[i].key = ft_strdup("OLDPWD");
		(*shell)->nv[i++].value = getcwd(NULL, 0);
	}
}

void	init(t_shell **shell, int ac, char **av, char **nv)
{
	(void)ac;
	(void)av;
	*shell = ft_calloc(1, sizeof(t_shell));
	(*shell)->status = 0;
	g_modes = ft_calloc(1, sizeof(t_mode));
	init_env(shell, nv);
}
