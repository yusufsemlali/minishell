/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:27:46 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/23 17:25:14 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**creat_env(t_env *nv)
{
	char	**env;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = nv;
	env = malloc(sizeof(char *) * (env_size(nv) + 1));
	if (!env)
		return (NULL);
	while (tmp)
	{
		env[i] = ft_strjoin(tmp->key, "=");
		if (!env[i] || (tmp->value && \
			!(env[i] = ft_strjoin(env[i], tmp->value))))
		{
			lazy_free(env, i);
			return (NULL);
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
		free(env[--i]);
	free(env);
}
