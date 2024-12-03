/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:07:26 by ysemlali          #+#    #+#             */
/*   Updated: 2024/11/04 16:58:28 by ysemlali         ###   ########.fr       */
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

int	interp_status(int status, StatusType type)
{
	if (type == W_EXITSTATUS)
		return ((status & 0xFF00) >> 8);
	else if (type == W_TERMSIG)
		return (status & 0x7F);
	else if (type == W_STOPSIG)
		return ((status & 0xFF00) >> 8);
	else if (type == W_IFEXITED)
		return ((status & 0x7F) == 0);
	else if (type == W_IFSIGNALED)
		return ((status & 0x7F) != 0 && (status & 0x7F) != 0x7F);
	else if (type == W_IFSTOPPED)
		return ((status & 0xFF) == 0x7F);
	else if (type == W_IFCONTINUED)
		return (status == 0xFFFF);
	else if (type == W_COREDUMP)
		return (status & 0x80);
	return (-1);
}

void	handle_child_termination(int status)
{
	if (interp_status(status, W_IFSIGNALED) && interp_status(status,
			W_TERMSIG) == SIGQUIT)
	{
		if (interp_status(status, W_COREDUMP))
		{
			fprintf(stderr, "Quit (core dumped)\n");
			g_modes.exit_mode = 131;
		}
		else
		{
			fprintf(stderr, "Quit\n");
			g_modes.exit_mode = 131;
		}
	}
	else if (interp_status(status, W_IFSIGNALED) && interp_status(status,
			W_TERMSIG) == SIGINT)
		g_modes.exit_mode = 130;
	else if (interp_status(status, W_IFEXITED))
		g_modes.exit_mode = interp_status(status, W_EXITSTATUS);
}
