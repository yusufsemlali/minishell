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

int	main(int ac, char **av, char **nv)
{
	t_shell	*shell;

	(void)av;
	// handle_signals(SIGINT);
	// handle_signals(SIGQUIT);
	shell->status = 0;
	while (shell->status == 0)
	{
		parse(shell);
		if (ft_strncmp(*shell->av, "exit", 3) == 0)
		{
			ft_putendl_fd("exit", STDOUT);
			shell->status = -1;
		}
		else
			minishell(shell);
	}
	return (EXIT_SUCCESS);
}
