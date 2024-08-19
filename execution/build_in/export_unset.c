/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:03:09 by aclakhda          #+#    #+#             */
/*   Updated: 2024/08/16 20:47:59 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_arr(char **arr, t_shell *shell)
{
	t_tree	*tmp;
	int		i;

	if (shell->tree->right == NULL)
		return (1);
	i = 0;
	tmp = shell->tree->right;
	while(tmp)
	{
		arr[i] = tmp->op;
		tmp = tmp->right;
		i++;
	}
	arr[i] = NULL;
	return (0);
}

void	create_env(char *key, char *value, t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->nv[i].key)
	{
		if (!ft_strcmp(shell->nv[i].key, key))
		{
			if (shell->nv[i].value)
				free(shell->nv[i].value);
			shell->nv[i].value = ft_strdup(value);
			return ;
		}
		i++;
	}
	shell->nv[i].key = ft_strdup(key);
	shell->nv[i].value = ft_strdup(value);
	shell->nv[i + 1].key = NULL;
	shell->nv[i + 1].value = NULL;
}

void	export(t_shell *shell)
{
	char	*arr[1024];
	int		i;
	int		j;
	char	*key;
	char	*value;

	i = 0;
	j = 0;
	if (create_arr(arr, shell))
		return ;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == '=')
			{
				key = ft_substr(arr[i], 0, j);
				value = ft_substr(arr[i], j + 1, ft_strlen(arr[i]) - (j + 1));
				create_env(key, value, shell);
				free(key);
				free(value);
				break ;
			}
			j++;
		}
		i++;
	}
}

int	found_key(t_shell *shell, char *arr)
{
	int	i;

	i = 0;
	while (shell->nv[i].key)
	{
		if (ft_strcmp(arr, shell->nv[i].key) == 0)
		{
			free(shell->nv[i].key);
			if (shell->nv[i].value)
				free(shell->nv[i].value);
		}
	}
	return 0;
}

void	unset(t_shell *shell)
{
	char	*arr[1024];
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (create_arr(arr, shell))
		return ;
	while (arr[i])
	{
		if (found_key(shell, arr[i]))
			printf("nope\n");
		// 	// delete(shell, arr[i]);
		i++;
	}
}
