/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:39:24 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/26 23:39:17 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_pipe(t_shell *shell)
{
	if (shell->tree->right)
	{
		handle_exit_numeric(shell);
		if (shell->tree->right->right && g_modes.exit_mode != 2)
		{
			handle_exit_too_many_args();
			return ;
		}
	}
	else
		g_modes.exit_mode = 0;
	free_all_shell(shell, 1);
}

void	handle_exit_too_many_args(void)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	g_modes.exit_mode = 1;
}

void	handle_exit_numeric(t_shell *shell)
{
	if (is_numeric(shell->tree->right->op))
		g_modes.exit_mode = ft_atoi(shell->tree->right->op);
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(shell->tree->right->op, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		g_modes.exit_mode = 2;
	}
}

size_t	overfl(int exit_mode)
{
	if (exit_mode < 0)
		return (256 + (exit_mode % 256));
	return (exit_mode % 256);
}
