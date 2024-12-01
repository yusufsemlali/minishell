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

void        heredoc_signals(int sig)
{
  if (sig == SIGINT)
  {
    close(STDIN_FILENO);
		g_modes.herdoc_mode = CTRL_C;
    g_modes.exit_mode = CTRL_C;
  }
}



