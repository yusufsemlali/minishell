/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 00:24:56 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/11 00:28:55 by aclakhda         ###   ########.fr       */
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
		(*shell)->nv->value = ft_strdup(getcwd(NULL, 0));
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
		(*shell)->nv->value = ft_strdup(getenv((*shell)->nv->key));
		if (nv[i + 1])
		{
			(*shell)->nv->next = ft_calloc(1, sizeof(t_env));
			(*shell)->nv = (*shell)->nv->next;
		}
		i++;
	}
	(*shell)->nv->next = NULL;
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
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
}
