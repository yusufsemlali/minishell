/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali & aclakhda <ysemlali & aclackd    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 06:01:17 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/03 00:00:01 by ysemlali &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>

t_mode	*g_modes;

void	minishell(t_shell *shell)
{
	shell->status = execute(shell);
	(void)shell;
}

int	error(t_shell *shell)
{
	if (shell->s == NULL)
		return (g_modes->exit_mode = STDERR, 1);
	if (shell->err == ERR_SYNTAX)
	{
		g_modes->exit_mode = EXIT_ERROR;
		return (ft_putstr_fd("syntax error\n", STDERR), 1);
	}
	return (0);
}

void	init_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	free_shell_av(char ***av)
{
	if (*av != NULL)
	{
		for (int i = 0; (*av)[i]; i++)
			free((*av)[i]);
	}
	free(*av);
	*av = NULL;
}

void	reset(t_shell *shell)
{
	shell->err = 0;
	shell->status = 0;
	g_modes->input_mode = 0;
	g_modes->output_mode = 0;
	free_shell_av(&(shell->av));
	ft_lstclear(&shell->token, del);
	free(shell->s);
}

int	main(const int ac, char **av, char **nv)
{
	t_shell	*shell;

	init(&shell, ac, av, nv);
	init_signals();
	shell->env = nv;
	while (shell->status == 0)
	{
		reset(shell);
		parse(shell);
		if (error(shell))
			continue ;
		ft_exit(shell);
		if (shell->s && shell->s[0] != '\0' && shell->status == 0)
			minishell(shell);
	}
	return (g_modes->exit_mode);
}
