/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:53:24 by aclakhda          #+#    #+#             */
/*   Updated: 2024/11/04 16:54:09 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	extract_and_create_env(char *entry, int j, t_shell *shell)
{
	char	*key;
	char	*value;
	int		edit;

	key = NULL;
	value = NULL;
	edit = 0;
	if (entry[j - 1] == '+')
	{
		edit = 1;
		key = ft_substr(entry, 0, j - 1);
	}
	else
		key = ft_substr(entry, 0, j);
	value = ft_substr(entry, j + 1, ft_strlen(entry) - (j + 1));
	create_env(key, value, shell, edit);
}

void	process_export_entry(char *entry, t_shell *shell, int *check)
{
	int	j;

	j = 0;
	if (validate(entry))
	{
		*check = 1;
		return ;
	}
	while (entry[j])
	{
		if (entry[j] == '=')
		{
			*check = 1;
			extract_and_create_env(entry, j, shell);
			if (!g_modes.d_change)
				g_modes.exit_mode = 0;
			return ;
		}
		j++;
	}
}

void	handle_export_error(void)
{
	ft_putstr_fd("export : not a valid identifier\n", STDERR);
	g_modes.exit_mode = 1;
}

void	print_env(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->nv;
	while (tmp)
	{
		printf("declare -x %s", tmp->key);
		if (tmp->value)
		{
			printf("=\"%s\"", tmp->value);
		}
		printf("\n");
		tmp = tmp->next;
	}
}

void	update_existing_env(t_env *env, char *value, int i, char *key)
{
	char	*tmp;

	tmp = env->value;
	if (i)
	{
		tmp = ft_strjoin(env->value, (char *)value);
		free(env->value);
		env->value = tmp;
		free(value);
		free(key);
		return ;
	}
	if (env->value)
		free(env->value);
	env->value = strdup(value);
	free(key);
	free(value);
}
