/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:37:29 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/18 10:37:29 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_shell *shell)
{
	if (shell->av && ft_strcmp(shell->av[0], "exit") == 0)
	{
		shell->status = EXIT_ERROR;
		ft_putstr_fd("exit\n", STDOUT);
		if (shell->err == ERR_SYNTAX)
			g_modes->exit_mode = STDOUT;
		else if (ft_arrlen(shell->av) == 2 && ft_numvalid(shell->av[1]))
			g_modes->exit_mode = ft_atoi(shell->av[1]);
		else if (ft_arrlen(shell->av) == 2)
		{
			ft_putstr_fd("minishell: exit: ", STDOUT);
			ft_putstr_fd(shell->av[1], STDOUT);
			ft_putstr_fd(": numeric argument required\n", STDOUT);
			g_modes->exit_mode = STDERR;
		}
		else if (ft_arrlen(shell->av) > 2)
		{
			shell->status = EXIT_SUCCESS;
			ft_putstr_fd("exit", STDOUT);
			ft_putstr_fd(": too many arguments\n", STDOUT);
			g_modes->exit_mode = STDOUT;
		}
	}
}
