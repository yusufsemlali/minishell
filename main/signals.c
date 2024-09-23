/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:38:22 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/21 16:38:10 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
    if (g_modes->pid == 0)
    {
		  ft_putstr_fd("\n", 1);
		  rl_on_new_line();
		  rl_replace_line("", 0);
      rl_redisplay();
		  g_modes->exit_mode = CTRL_C;
      if (g_modes->herdoc_mode == CTRL_C)
        g_modes->herdoc_mode = 0;
      else
        g_modes->herdoc_mode = CTRL_C;
    }
    else {
      ft_putstr_fd("\n", 1);
      g_modes->exit_mode = CTRL_C;
      g_modes->herdoc_mode = CTRL_C;
    }
	}
	else if (sig == SIGQUIT)
		return ;
}

