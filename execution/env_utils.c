/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:27:46 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/25 21:16:06 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**creat_env(t_env *nv)
{
	t_env	*tmp = nv;
	int		i = 0;
	char	**env;

	env = malloc(sizeof(char *) * (env_size(nv) + 1));
	if (!env)
		return (NULL);
	while (tmp)
	{
		env[i] = ft_strjoin(tmp->key, "=");
		if (!env[i])
			return (lazy_free(env, i), NULL);
		if (tmp->value)
		{
			char *temp = env[i];
			env[i] = ft_strjoin(env[i], tmp->value);
			free(temp);
			if (!env[i])
				return (lazy_free(env, i), NULL);
		}
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

int	env_size(t_env *nv)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = nv;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	lazy_free(char **env, int i)
{
	while (i > 0)
	{
		if (env[i - 1])
			free(env[--i]);
	}
	free(env);
}
