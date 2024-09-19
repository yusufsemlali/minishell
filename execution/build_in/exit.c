/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:55:33 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/18 23:31:48 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

size_t	overfl(int exit_mode)
{
	if (exit_mode < 0)
		return (256 + (exit_mode % 256));
	return (exit_mode % 256);
}

void	free_all_shell(t_shell *shell, int i)
{
	if (i)
	{
		g_modes->exit_mode = overfl(g_modes->exit_mode);
		return ;
	}
	free_herdoc(shell->herdoc);
	ft_free_tree(shell->tree);
	close(shell->fd);
	unlink("tmp");
	free_all(shell);
	exit(g_modes->exit_mode);
}

void	exit_pipe(t_shell *shell)
{
	int i = 0;

	if (shell->tree->right)
	{
		if (is_numeric(shell->tree->right->op))
			g_modes->exit_mode = ft_atoi(shell->tree->right->op);
		else
		{
			i++;
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(shell->tree->right->op, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			g_modes->exit_mode = 2;
		}
		if (shell->tree->right->right && !i)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			g_modes->exit_mode = 1;
			return;
		}
	}
	else
		g_modes->exit_mode = 0;
	free_all_shell(shell, 1);
}

void	handle_exit_error(t_shell *shell, char *msg, int exit_code)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (exit_code == 2)
		ft_putstr_fd(": numeric argument required", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_modes->exit_mode = exit_code;
	if (exit_code == 1)
		return ;
	free_all_shell(shell, 0);
}

void	ft_exit(t_shell *shell)
{
	if (g_modes->has_pipe)
		return exit_pipe(shell);
	g_modes->exit_mode = 0;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (shell->tree->right)
	{
		if (is_numeric(shell->tree->right->op) && !shell->tree->right->right)
			g_modes->exit_mode = ft_atoi(shell->tree->right->op);
		else if (!is_numeric(shell->tree->right->op))
			return handle_exit_error(shell, shell->tree->right->op, 2);
		if (shell->tree->right->right && is_numeric(shell->tree->right->op))
			return handle_exit_error(shell, "too many arguments", 1);
	}
	free_all_shell(shell, 0);
}
