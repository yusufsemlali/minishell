/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:20:15 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/20 00:28:00 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_str_cpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_str_join(char const *s1, char const *s2)
{
	size_t	i;
	size_t	l1;
	size_t	l2;
	char	*p;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!p)
		return (NULL);
	ft_str_cpy(p, s1);
	i = 0;
	while (s2[i])
	{
		p[l1++] = s2[i++];
	}
	p[l1] = '\0';
	return (p);
}

void	update_env(t_env *nv, char *key, char *value)
{
	t_env	*tmp;

	tmp = nv;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = (char *)malloc(sizeof(char) * (ft_strlen(value) + 1));
			if (!tmp->value)
				return ;
			ft_str_cpy(tmp->value, value);
			return ;
		}
		tmp = tmp->next;
	}
}

char	*get_env_cd(t_env *nv, char *key)
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

void	cd(t_shell *shell)
{
	char	*av[CMD_MAX_LENGTH];
	char	*home;
	int		i;
	char	past_path[1024];
	char	current_path[1024];

	i = 0;
	if (getcwd(past_path, sizeof(past_path)) == NULL)
	{
		perror("getcwd :");
		g_modes->exit_mode = 1;
		return ;
	}
	if (!shell->tree->right || !ft_strcmp(shell->tree->right->op, "~"))
	{
		home = get_env_cd(shell->nv, "HOME");
		if (!home)
		{
			printf("HOME not set\n");
			g_modes->exit_mode = 1;
			return ;
		}
		if (chdir(home))
		{
			perror("cd :");
			g_modes->exit_mode = 1;
			return ;
		}
		g_modes->exit_mode = 0;
		i = 1;
	}
	else
		cmd_maker(shell, av);
	if (chdir(av[1]) && !i)
	{
		perror("cd :");
		g_modes->exit_mode = 1;
		return ;
	}
	if (getcwd(current_path, sizeof(current_path)) == NULL)
	{
		perror("getcwd :");
		g_modes->exit_mode = 1;
		return ;
	}
	update_env(shell->nv, "OLDPWD", past_path);
	update_env(shell->nv, "PWD", current_path);
	g_modes->exit_mode = 0;
}
