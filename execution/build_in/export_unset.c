/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:03:09 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/25 23:10:49 by aclakhda         ###   ########.fr       */
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

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || \
		c == '\n' || c == '\v' || c == \
			'\f' || c == '\r');
}

void	print_env(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->nv;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putstr_fd(tmp->key, STDOUT);
		if (tmp->value)
		{
			ft_putstr_fd("=\"", STDOUT);
			ft_putstr_fd(tmp->value, STDOUT);
			ft_putstr_fd("\"", STDOUT);
		}
		ft_putstr_fd("\n", STDOUT);
		tmp = tmp->next;
	}
}

int	process_export_entry(char *entry, t_shell *shell)
{
	int		j;
	char	*key;
	char	*value;

	j = 0;
	while (entry[j])
	{
		if (is_space(entry[j]))
		{
			ft_putstr_fd("export : not a valid identifier\n", STDERR);
			g_modes->exit_mode = 1;
			return (-1);
		}
		if (entry[j] == '=')
		{
			key = ft_substr(entry, 0, j);
			value = ft_substr(entry, j + 1, ft_strlen(entry) - (j + 1));
			create_env(key, value, shell);
			g_modes->exit_mode = 0;
			break ;
		}
		j++;
	}
	return (0);
}

void	export(t_shell *shell)
{
	char	*arr[1024];
	int		i;

	i = 0;
	if (g_modes->has_pipe)
		return ;
	if (create_arr(arr, shell))
	{
		print_env(shell);
		return ;
	}
	while (arr[i])
	{
		if (process_export_entry(arr[i], shell) == -1)
			return ;
		i++;
	}
}

void	found_key(t_shell *shell, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	prev = NULL;
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
	g_modes->exit_mode = 0;
	if (create_arr(arr, shell))
		return ;
	while (arr[i])
	{
		found_key(shell, arr[i]);
		i++;
	}
}
