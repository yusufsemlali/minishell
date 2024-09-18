/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:45:07 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/18 10:45:07 by ysemlali         ###   ########.fr       */
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
	shell->begin = 0;
	shell->status = 0;
	g_modes->input_mode = 0;
	g_modes->output_mode = 0;
	free_av(&(shell->av));
	ft_lstclear(&shell->token, del);
	free(shell->s);
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
		if (shell->err == 0)
			minishell(shell);
	}
	return (free_all(shell));
}
