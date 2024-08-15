/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 06:01:17 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/14 20:03:27 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_mode	*g_modes;

void	minishell(t_shell *shell)
{
	shell->status = execute(shell);
}

int	error(t_shell *shell)
{
	if (ft_strncmp(shell->line, "exit", 4) == 0)
		return (ft_putstr_fd("exit\n", STDOUT), shell->status = 1, 1);
	if (shell->err == ERR_SYNTAX)
		return (ft_putstr_fd("syntax error\n", STDERR), 1);
	return (0);
}

void	init_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

// void	print_av(char **av)
// {
// 	int	i;

// 	if (!av || !*av)
// 		return ;
// 	i = 0;
// 	while (av[i])
// 	{
// 		ft_putstr_fd(av[i], STDOUT);
// 		ft_putstr_fd("\n", STDOUT);
// 		i++;
// 	}
// }

// void print_env(t_shell *shell)
// {
// 	int i = 0;
// 	while (shell->nv[i].key != NULL)
// 	{
// 		printf("%s      %s\n", shell->nv[i].key, shell->nv[i].value);
// 		i++;
// 	}
// }

int	main(int ac, char **av, char **nv)
{
	t_shell	*shell;

	init(&shell, ac, av, nv);
	// print_env(shell);
	// init_signals();
	while (shell->status == 0)
	{
		parse(shell);
		// print_av(shell->av);
		if (error(shell))
			break ;
		if (shell->line == NULL || shell->line[0] == '\0')
			;
		else
			minishell(shell);
	}
	return (EXIT_SUCCESS);
}
