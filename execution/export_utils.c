/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:30:46 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/27 20:08:58 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_export_entry(char *entry, t_shell *shell)
{
	char	*key;
	char	*value;
	int		j;

	j = 0;
	while (entry[j])
	{
		if (is_space(entry[j]))
		{
			handle_export_error();
			return ;
		}
		if (entry[j] == '=')
		{
			key = ft_substr(entry, 0, j);
			value = ft_substr(entry, j + 1, ft_strlen(entry) - (j + 1));
			create_env(key, value, shell);
			free(key);
			free(value);
			g_modes->exit_mode = 0;
			return ;
		}
		j++;
	}
}

void	handle_export_error(void)
{
	ft_putstr_fd("export : not a valid identifier\n", STDERR);
	g_modes->exit_mode = 1;
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

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || \
		c == '\n' || c == '\v' || c == \
			'\f' || c == '\r');
}

void	update_existing_env(t_env *env, const char *value)
{
	free(env->value);
	env->value = strdup(value);
}
