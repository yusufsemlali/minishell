/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 06:01:17 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/14 23:49:54by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_mode	*g_modes;

void	minishell(t_shell *shell)
{
	// shell->status = execute(shell);
	(void)shell;
}

int	error(t_shell *shell)
{
	if (ft_strcmp(shell->s, "exit") == 0)
		return (ft_putstr_fd("exit\n", STDOUT), shell->status = 0, 1);
	if (shell->err == ERR_SYNTAX)
	{
		g_modes->exit_mode = EXIT_ERROR;
		return (ft_putstr_fd("syntax error\n", STDERR), 0);
	}
	if (!shell->s || !*shell->s)
	{
		g_modes->exit_mode = EXIT_ERROR;
		return (1);
	}
	return (0);
}

void	init_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}


void reset(t_shell *shell)
{
	shell->err = 0;
	g_modes->exit_mode = 0;
	g_modes->input_mode = 0;
	g_modes->output_mode = 0;
}

int	main(int ac, char **av, char **nv)
{
	t_shell	*shell;

	init(&shell, ac, av, nv);
	while (1)
	{
		reset(shell);
		parse(shell);
		if (error(shell))
			break ;
		if (shell->s[0] == '\0')
			continue ;
		else
			minishell(shell);
	}
	return (shell->status);
}
