/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:07:26 by ysemlali          #+#    #+#             */
/*   Updated: 2024/12/02 20:53:16 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		if (g_modes.pid == 0)
		{
			ft_putstr_fd("\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_modes.exit_mode = CTRL_C;
		}
		else
		{
			ft_putstr_fd("\n", 1);
			g_modes.exit_mode = CTRL_C;
			g_modes.herdoc_mode = CTRL_C;
		}
	}
}

void	heredoc_signals(int sig)
{
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		g_modes.herdoc_mode = CTRL_C;
		g_modes.exit_mode = CTRL_C;
	}
}

void	handle_child_termination(int status)
{
	if (WEXITSTATUS(status) == 42)
		g_modes.exit_mode = CMD_NOT_FOUND;
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			if (WCOREDUMP(status))
				ft_putendl_fd("Quit (core dumped)", STDOUT);
			else
				ft_putendl_fd("Quit", STDOUT);
		}
		g_modes.exit_mode = 128 + WTERMSIG(status);
	}
	else
		g_modes.exit_mode = WEXITSTATUS(status);
}
