/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:18:41 by aclakhda          #+#    #+#             */
/*   Updated: 2024/11/13 20:39:20 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_errrror(char *file_name)
{
	ft_putstr_fd("minishell: failed to open file \"", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd("\" >~<\n", 2);
}

int	type_check(t_tree *tree)
{
	if (tree->type == OUTPUT || tree->type == INPUT || \
		tree->type == APPEND || tree->type == HEREDOC)
		return (1);
	return (0);
}

int	check_directory(t_var *var, t_shell *shell)
{
	struct stat	path_stat;

	if (stat(var->av[0], &path_stat) == -1)
	{
		if (var->cmd_path || check_is_dir_path(var->av[0]))
			return (0);
		print_err(var->av[0], 1);
		g_modes.exit_mode = 127;
		handle_exec_error(var, shell, 0);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		if (check_is_dir_path(var->av[0]))
			return (1);
		print_err(var->av[0], 0);
		for_norminet(var, shell);
	}
	if (access(var->av[0], X_OK) == -1)
	{
		if (ft_strncmp("./", var->av[0], 2) && ft_strncmp("/", var->av[0], 1))
			return (0);
		print_err(var->av[0], 2);
		for_norminet(var, shell);
	}
	return (0);
}

void	print_err(char *str, int i)
{
	char	buf[BUFFER_SML];

	ft_strlcat(buf, "minishell: ", BUFFER_SML);
	if (i == 1)
	{
		ft_strlcat(buf, str, BUFFER_SML);
		ft_strlcat(buf, ": No such file or directory\n", BUFFER_SML);
	}
	else if (i == 0)
	{
		ft_strlcat(buf, str, BUFFER_SML);
		ft_strlcat(buf, ": Is a directory\n", BUFFER_SML);
	}
	else if(i == 2)
	{
		ft_strlcat(buf, str, BUFFER_SML);
		ft_strlcat(buf, "ambigguous redirect\n", BUFFER_SML);
	}
	else
	{
		ft_strlcat(buf, str, BUFFER_SML);
		ft_strlcat(buf, ": Permission denied\n", BUFFER_SML);
	}
	ft_putstr_fd(buf, STDERR);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || \
			c == '\n' || c == '\v' || c == '\f' || c == '\r');
}
