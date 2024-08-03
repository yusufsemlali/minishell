/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:16:01 by ysemlali          #+#    #+#             */
/*   Updated: 2024/07/23 18:55:12y ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_mode	*modes;

void	minishell(t_shell *shell)
{
	shell->status = execute(shell);
}


int error(t_shell *shell)
{
	if (ft_strncmp(shell->line, "exit", 4) == 0)
		return (ft_putstr_fd("exit\n", STDOUT), shell->status = 1 , 1);
	if (shell->err == ERR_SYNTAX)
		return (ft_putstr_fd("syntax error\n", STDERR), 1);
	return (0);
}
void init_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void print_av(char **av)
{
	int i = 0;
	while (av[i])
	{
		ft_putstr_fd(av[i], STDOUT);
		ft_putstr_fd("\n", STDOUT);
		i++;
	}
}

int	main(int ac, char **av, char **nv)
{
	t_shell	*shell;
	init(&shell, ac, av, nv);
	// init_signals();
	while (shell->status == 0)
	{
		parse(shell);
		if (error(shell))
			break;
		print_av(shell->av);
		else
			minishell(shell);
	}
	return (EXIT_SUCCESS);
}
