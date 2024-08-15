/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:20:15 by aclakhda          #+#    #+#             */
/*   Updated: 2024/08/14 18:11:41 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static void	ft_str_cpy(char *dest, const char *src)
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

void	update_env(char **nv, char *key, char *value)
{
	int		i;
	char	*tmp;
	char	*tmp2;


	tmp = ft_str_join(key, "=");
	tmp2 = ft_str_join(tmp, value);
	free(tmp);
	i = 0;
	while (nv[i])
	{
		if (ft_strncmp(nv[i], key, ft_strlen(key)) == 0 && nv[i][ft_strlen(key)] == '=')
		{
			free(nv[i]);
			nv[i] = tmp2;
			return ;
		}
		i++;
	}
	nv[i] = tmp2;
	nv[i + 1] = NULL;
}

void	cd(t_shell *shell)
{
	char	*av[CMD_MAX_LENGTH];
	char	past_path[1024];
	char	current_path[1024];

	if (getcwd(past_path, sizeof(past_path)) == NULL)
	{
		perror("getcwd :");
		return ;
	}
	cmd_maker(shell, av);
	if (chdir(av[1]))
	{
		perror("cd :");
		return ;
	}
	if (getcwd(past_path, sizeof(current_path)) == NULL)
	{
		perror("getcwd :");
		return ;
	}
	//update_env(shell->nv, "OLDPWD", past_path);
	//update_env(shell->nv, "PWD", current_path);
}
