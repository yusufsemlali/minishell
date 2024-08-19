/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 00:24:56 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/17 20:12:02 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_old_pwd(t_shell **shell, char **nv)
{
	int	i;

	i = 0;
	while (nv[i] && ft_strncmp(nv[i], "OLDPWD=", 7) != 0)
		i++;
	if (!nv[i] && (*shell)->nv->next == NULL)
	{
		(*shell)->nv->next = ft_calloc(1, sizeof(t_env));
		(*shell)->nv = (*shell)->nv->next;
		(*shell)->nv->key = ft_strdup("OLDPWD");
		(*shell)->nv->value = getcwd(NULL, 0);
		(*shell)->nv->next = NULL;
	}
}

void	init_env(t_shell **shell, char **nv)
{
	int		i;
	t_env	*tmp;

	i = 0;
	(*shell)->nv = ft_calloc(1, sizeof(t_env));
	tmp = (*shell)->nv;
	while (nv[i])
	{
		(*shell)->nv->key = ft_strndup(nv[i], ft_strchr(nv[i], '=') - nv[i]);
		(*shell)->nv->value = getenv((*shell)->nv->key);
		if (nv[i + 1])
		{
			(*shell)->nv->next = ft_calloc(1, sizeof(t_env));
			(*shell)->nv = (*shell)->nv->next;
		}
		i++;
	}
	(*shell)->nv->next = NULL;
	add_old_pwd(shell, nv);
	(*shell)->nv = tmp;
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
