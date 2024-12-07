/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:53:08 by aclakhda          #+#    #+#             */
/*   Updated: 2024/11/04 18:39:15 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_paths(t_shell *shell, char *past_path)
{
	char	current_path[1024];

	if (getcwd(current_path, sizeof(current_path)) == NULL)
	{
		perror("getcwd :");
		exit_mode = 1;
		return ;
	}
	update_env(shell->nv, "OLDPWD", past_path);
	update_env(shell->nv, "PWD", current_path);
}

void	handle_home_directory(t_shell *shell)
{
	char	*home;

	home = get_env_cd(shell->nv, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd : HOME not set\n", 2);
		exit_mode = 1;
		return ;
	}
	change_directory(shell, home, NULL);
}

void	change_directory(t_shell *shell, char *path, char **av)
{
	(void)shell;
	if (chdir(path))
	{
		exit_mode = 1;
		if (av)
			s_free(av);
		perror("cd :");
	}
	else
	{
		if (av)
			s_free(av);
		exit_mode = 0;
	}
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
