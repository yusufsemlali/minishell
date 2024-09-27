/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:37:19 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/18 10:37:19 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value(char *key)
{
	char	*value;

	if (ft_strcmp(key, "PWD") == 0)
		value = ft_strdup(getcwd(NULL, 0));
	else if (ft_strcmp(key, "SHLVL") == 0)
		value = ft_strdup("1");
	else if (ft_strcmp(key, "_") == 0)
		value = ft_strdup("/usr/bin/env");
	else
		value = ft_strdup("");
	return (value);
}

void	init_basic_env(t_shell **shell, char **nv)
{
	t_env	*tmp;
	int		i;

	tmp = (*shell)->nv;
	i = 0;
	(*shell)->nv = ft_calloc(1, sizeof(t_env));
	while (nv[i])
	{
		(*shell)->nv->key = ft_strdup(nv[i]);
		(*shell)->nv->value = get_value(nv[i]);
		if (nv[i + 1] != NULL)
		{
			(*shell)->nv->next = ft_calloc(1, sizeof(t_env));
			(*shell)->nv = (*shell)->nv->next;
		}
		i++;
	}
	(*shell)->nv->next = NULL;
	(*shell)->nv = tmp;
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
		if (ft_strcmp((*shell)->nv->key, "SHLVL") == 0)
			(*shell)->nv->value = ft_itoa(ft_atoi(ft_strchr(nv[i], '=') + 1)
					+ 1);
		else
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
	char	*basic[5];

	basic[0] = "PWD";
	basic[1] = "LS_COLORS";
	basic[2] = "SHLVL";
	basic[3] = "_";
	basic[4] = NULL;
	(void)ac;
	(void)av;
	*shell = ft_calloc(1, sizeof(t_shell));
	(*shell)->status = 0;
	g_modes = ft_calloc(1, sizeof(t_mode));
	if (nv == NULL)
		init_basic_env(shell, basic);
	else
		init_env(shell, nv);
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
}
