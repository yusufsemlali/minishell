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
	rl_replace_line("", 0);
	RL_REDISPLAY();
	G_MODES->EXIT_MODE = 1;
}

VOID	SIGNAL_QUIT(INT SIG)
{
	(VOID)SIG;
	PRINTF("qUIT: 3\N");
	RL_REPLACE_LINE("", 0);
}

VOID	SIGNAL_SPECIAL(INT SIG)
{
	(VOID)SIG;
	IF (G_MODES->INPUT_MODE == -1)
		PRINTF("HELLO\N");
	EXIT(0);
	// RL_REPLACE_LINE("", 0);
}

VOID	init_signals(int sig)
{
	IF (SIG == sigint)
		SIGNAL(sigint, SIGNAL_INTERRUPT);
	ELSE IF (SIG == sigchld)
		SIGNAL(sigchld, SIGNAL_QUIT);
	ELSE IF (SIG == sigspecial)
		SIGNAL(sigint, SIGNAL_SPECIAL);
	ELSE IF (SIG == sigquit)
		SIGNAL(sigquit, SIGNAL_QUIT);
}
