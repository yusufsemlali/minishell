/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:03:09 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/27 20:17:12 by aclakhda         ###   ########.fr       */
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
	while (tmp)
	{
		arr[i] = tmp->op;
		tmp = tmp->right;
		i++;
	}
	arr[i] = NULL;
	return (0);
}

t_env	*create_new_env(const char *key, const char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = strdup(key);
	new->value = strdup(value);
	if (!new->key || !new->value)
	{
		free(new->key);
		free(new->value);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
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
			update_existing_env(tmp, value);
			return ;
		}
		tmp = tmp->next;
	}
	new = create_new_env(key, value);
	if (!new)
		return ;
	tmp = shell->nv;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	export(t_shell *shell)
{
	char	*arr[1024];
	int		i;

	if (g_modes->has_pipe)
		return ;
	if (create_arr(arr, shell))
	{
		print_env(shell);
		return ;
	}
	i = 0;
	while (arr[i])
	{
		process_export_entry(arr[i], shell);
		i++;
	}
	g_modes->exit_mode = 0;
}

void	unset(t_shell *shell)
{
	char	*arr[1024];
	int		i;

	i = 0;
	g_modes->exit_mode = 0;
	if (create_arr(arr, shell))
		return ;
	while (arr[i])
	{
		found_key(shell, arr[i]);
		i++;
	}
}
