/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:38:22 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/17 17:04:00 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_interrupt(int sig)
{
	(void)sig;
	if (g_modes->input_mode == -1)
		printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
	g_modes->exit_mode = 1;
}

void	signal_quit(int sig)
{
	(void)sig;
	printf("Quit: 3\n");
	// rl_replace_line("", 0);
}

void	signal_special(int sig)
{
	(void)sig;
	if (g_modes->input_mode == -1)
		printf("hello\n");
	exit(0);
	// rl_replace_line("", 0);
}

void	handle_signals(int sig)
{
	if (sig == SIGINT)
		signal(SIGINT, signal_interrupt);
	else if (sig == SIGCHLD)
		signal(SIGCHLD, signal_quit);
	else if (sig == SIGSPECIAL)
		signal(SIGINT, signal_special);
	else if (sig == SIGQUIT)
		signal(SIGQUIT, signal_quit);
}
