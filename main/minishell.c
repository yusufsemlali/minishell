/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 06:01:17 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/20 17:19:00 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_mode	*g_modes;

void	minishell(t_shell *shell)
{
	shell->status = execute(shell);
	(void)shell;
}

int	error(t_shell *shell)
{
	if (shell->s == NULL)
	{
		g_modes->exit_mode = EXIT_ERROR;
		return (0);
	}
	if (ft_strcmp(shell->s, "exit") == 0)
		return (ft_putstr_fd("exit\n", STDOUT), shell->status = 0, 1);
	if (shell->err == ERR_SYNTAX)
	{
		g_modes->exit_mode = EXIT_ERROR;
		return (ft_putstr_fd("syntax error\n", STDERR), 0);
	}
	return (0);
}

void	init_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void free_shell_av(char ***av)
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
	g_modes->exit_mode = 0;
	g_modes->input_mode = 0;
	g_modes->output_mode = 0;
	free_shell_av(&(shell->av));
}

int	main(int ac, char **av, char **nv)
{
	t_shell	*shell;

	init(&shell, ac, av, nv);
	shell->env = nv;
	while (1)
	{
		reset(shell);
		parse(shell);
		// for (int i = 0; shell->av[i] != NULL; i++)
		// 	printf("%s\n" , shell->av[i]);
		if (error(shell))
			break ;
		if (shell->s == NULL || shell->s[0] == '\0')
			continue ;
		else
			minishell(shell);
	}
	return (shell->status);
}
