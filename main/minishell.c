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

// void	minishell(t_shell *shell)
// {
// 	shell->status = execute(shell);
// }


int error(t_shell *shell)
{
	if (shell->err == ERR_SYNTAX)
	{
		ft_putstr_fd("minishell: syntax error\n", STDERR);
		return (1);
	}
	if (shell->err == ERR_SYNTAX)
	{
		ft_putstr_fd("minishell: syntax error\n", STDERR);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **nv)
{
	t_shell	*shell;
	// handle_signals(SIGINT);
	// handle_signals(SIGQUIT);
	init(&shell, ac, av, nv);
	while (shell->status == 0)
	{
		parse(shell);
		if (error(shell))
			break;
		// else
			// minishell(shell);
	}
	return (EXIT_SUCCESS);
}
