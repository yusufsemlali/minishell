/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:18:41 by aclakhda          #+#    #+#             */
/*   Updated: 2024/11/04 18:38:23 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_errrror(char *file_name)
{
	ft_putstr_fd("minishell: failed to open file \"", 2);
	if (file_name)
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

void	check_directory(t_var *var, t_shell *shell)
{
	struct stat	path_stat;

	if (stat(var->cmd_path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			print_err(var->av[0], 0);
			g_modes.exit_mode = 126;
			handle_exec_error(var, shell, 0);
		}
	}
}

void	print_err(char *str, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (i == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a file\n", 2);
	}
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || \
			c == '\n' || c == '\v' || c == '\f' || c == '\r');
}
