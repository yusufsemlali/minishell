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

void change_signals(int type)
{
  if(type == 1)
    signal(SIGINT, run_mode);
  else if(type == 2)
      signal(SIGINT, readline_mode);
}


void run_mode(int sig)
{
  (void)sig;
  ft_putstr_fd("\n", 1);
  exit_mode = CTRL_C;
}

void	readline_mode(int sig)
{
  (void)sig;
  ft_putstr_fd("\n", 1);
  rl_on_new_line();
  rl_replace_line("", 0);
  rl_redisplay();
  exit_mode = CTRL_C;
}

void	heredoc_signals(int sig)
{
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		exit_mode = CTRL_C;
	}
}

void	handle_child_termination(int status)
{
	if (WEXITSTATUS(status) == 42)
		exit_mode = CMD_NOT_FOUND;
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			if (WCOREDUMP(status))
				ft_putendl_fd("Quit (core dumped)", STDOUT);
			else
				ft_putendl_fd("Quit", STDOUT);
		}
		exit_mode = 128 + WTERMSIG(status);
	}
	else
		exit_mode = WEXITSTATUS(status);
}
