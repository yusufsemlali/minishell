/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	free_keys(char *key, char *value)
{
	free(key);
	free(value);
}

=
void	extract_and_create_env(char *entry, int j, t_shell *shell)
{
	char	*key;
	char	*value;

	key = ft_substr(entry, 0, j);
	value = ft_substr(entry, j + 1, ft_strlen(entry) - (j + 1));
	if (entry[j - 1] == '+')
		create_env(key, value, shell, 1);
	else
		create_env(key, value, shell, 0);
	free_keys(key, value);
}

void	process_export_entry(char *entry, t_shell *shell, int *check)
{
	int	j;

	j = 0;
	if (validate(entry, shell))
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

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || \
		c == '\n' || c == '\v' || c == \
			'\f' || c == '\r');
}

void	update_existing_env(t_env *env, const char *value, int i)
{
	if (i)
	{
		env->value = ft_strjoin(env->value, (char *)value);
		free((char *)value);
		return ;
	}
	free(env->value);
	env->value = strdup(value);
}
