/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 06:01:17 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/13 16:34:06 by aclakhda         ###   ########.fr       */
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

void	reset(t_shell *shell)
{
	shell->err = 0;
	shell->status = 0;
	shell->begin = 0;
	g_modes->input_mode = 0;
	g_modes->output_mode = 0;
	free_av(&(shell->av));
	ft_lstclear(&shell->token, del);
	free(shell->s);
}

int	main(const int ac, char **av, char **nv)
{
	t_shell	*shell;

	init(&shell, ac, av, nv);
	shell->env = nv;
	while (shell->status == 0)
	{
		reset(shell);
		parse(shell);
		if (shell->err == 0)
		  minishell(shell);
	}
	return (free_all(shell));
}
