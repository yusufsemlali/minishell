/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:58:53 by ysemlali          #+#    #+#             */
/*   Updated: 2024/11/14 21:02:33 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_mode	g_modes;

void	ctrl_c_remove(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	minishell(t_shell *shell)
{
	shell->status = execute(shell);
	(void)shell;
}

void	free_keys(char *key, char *value)
{
	free(key);
	free(value);
}

void	reset(t_shell *shell)
{
	free(shell->s);
	ft_lstclear(&shell->token);
	shell->err = 0;
	shell->begin = 0;
	shell->status = 0;
	shell->end = 0;
	g_modes.has_pipe = 0;
	g_modes.input_mode = 0;
	g_modes.output_mode = 0;
	g_modes.herdoc_mode = 0;
	g_modes.herdoc_mode = 0;
	g_modes.pipe_count = 0;
	g_modes.pid2 = 0;
	g_modes.pid = 0;
	g_modes.d_change = 0;
	shell->s = NULL;
}

int	main(const int ac, char **av, char **nv)
{
	t_shell	*shell;

	if (*nv == NULL)
		init(&shell, ac, av, NULL);
	else
		init(&shell, ac, av, nv);
	ctrl_c_remove();
	while (shell->status == 0)
	{
		reset(shell);
		parse(shell);
		shell->r_fd = 0;
		if (shell->err == 0 && shell->token)
			minishell(shell);
	}
	return (0);
}
