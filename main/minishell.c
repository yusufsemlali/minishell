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
	shell->status = 1;
	while (shell->status)
	{
		
		parse(shell);
		// shell->status = execute(shell->av);
		// free(shell->line);
		// free(shell->av);
	}
}

int	main(int ac, char **av, char **nv)
{
	(void)av;
	t_shell *shell;
	shell = ft_calloc(1, sizeof(t_shell));
	modes = ft_calloc(1, sizeof(t_mode));
	modes->input_mode = -1;
	shell->nv = nv;

	handle_signals(SIGINT);
	handle_signals(SIGQUIT);
	if (ac > 1)
	{
		printf("Usage: use without arguments\n");
		free(shell);
		return (EXIT_FAILURE);
	}
	minishell(shell);

	return (EXIT_SUCCESS);
}