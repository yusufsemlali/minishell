/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:16:01 by ysemlali          #+#    #+#             */
/*   Updated: 2024/07/23 18:21:43 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mode	*modes;

char	*read_line(void)
{
	char	*line;
	size_t	bufsize;

	line = NULL;
	bufsize = 0;
	getline(&line, &bufsize, stdin);
	return (line);
}
void	minishell(t_shell *shell)
{
	shell->status = 1;
	while (shell->status)
	{
		printf("minishell$ ");
		shell->line = read_line();
		shell->av = ft_split(shell->line, ' ');
        if (ft_strncmp(*shell->av, "exit", 4) == 0)
        {
            printf("exit\n");
            exit(EXIT_SUCCESS);
        }
		shell->status = execute(shell->av);
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