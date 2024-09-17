/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:03:09 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/17 15:14:49 by aclakhda         ###   ########.fr       */
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
	t_env	*tmp;
	t_env	*new;

	tmp = shell->nv;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = malloc((ft_strlen(value) + 1));
			if (!tmp->value)
				return ;
			ft_str_cpy(tmp->value, value);
			return ;
		}
		tmp = tmp->next;
	}
	new = (t_env *)malloc(sizeof(t_env));
	new->key = key;
	new->value = value;
	new->next = NULL;
	tmp = shell->nv;
	if (!tmp)
	{
		shell->nv = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
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
				break ;
			}
			j++;
		}
		i++;
	}
}

void	found_key(t_shell *shell, char *key)
{
	t_env	*tmp;
	t_env	*prev = NULL;

	tmp = shell->nv;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (prev)
				prev->next = tmp->next;
			else
				shell->nv = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
    }
}

void	unset(t_shell *shell)
{
	char	*arr[1024];
	int		i;

	i = 0;
	if (create_arr(arr, shell))
		return ;
	while (arr[i])
	{
		found_key(shell, arr[i]);
		i++;
	}
}
