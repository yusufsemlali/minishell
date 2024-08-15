/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:27:46 by aclakhda          #+#    #+#             */
/*   Updated: 2024/08/15 12:31:56 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**creat_env(t_env *nv)
{
	char	**env;
	t_var	var;

	var.size = env_size(nv);
	var.i = 0;
	env = (char **)malloc(sizeof(char *) * (var.size + 1));
	if (!env)
		return (NULL);
	while (var.i < var.size)
	{
		var.key_len = ft_strlen(nv[var.i].key);
		var.value_len = ft_strlen(nv[var.i].value);
        env[var.i] = (char *)malloc(var.key_len + var.value_len + 2);
        if (!env[var.i])
        {
			lazy_free(env, var.i);
			return NULL;
		}
		ft_strcpy(env[var.i], nv[var.i].key);
		ft_strcat(env[var.i], "=");
		ft_strcat(env[var.i], nv[var.i].value);
		var.i++;
	}
	env[var.i] = NULL;
	return (env);
}

int	env_size(t_env *nv)
{
	int	i;

	i = 0;
	while (nv[i].key)
		i++;
	return (i);
}

void	lazy_free(char **env, int i)
{
	while (i > 0)
		free(env[--i]);
	free(env);
}
