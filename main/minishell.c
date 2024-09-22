/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 06:01:17 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/22 00:51:42 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_mode	*g_modes;

void	minishell(t_shell *shell)
{
	shell->status = execute(shell);
	(void)shell;
}

void	reset(t_shell *shell)
{
	shell->err = 0;
	shell->begin = 0;
	shell->status = 0;
	shell->end = 0;
	g_modes->input_mode = 0;
	g_modes->output_mode = 0;
	g_modes->has_pipe = 0;
	free_all(shell);
	shell->s = NULL;
}

int	main(const int ac, char **av, char **nv)
{
	t_shell	*shell;

	if (*nv == NULL)
		init(&shell, ac, av, NULL);
	else
		init(&shell, ac, av, nv);
	while (shell->status == 0)
	{
		reset(shell);
		parse(shell);
		shell->r_fd = 0;
		if (shell->err == 0)
			minishell(shell);
	}
	return (0);
}
