/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:22:58 by ysemlali          #+#    #+#             */
/*   Updated: 2024/07/26 01:43:02by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	closed_check(t_shell *shell, char *s)
{
	int one_open = 0;
	int two_open = 0;
	while (*s)
	{
		if (*s == '\'' && *(s - 1) != '\\' && two_open % 2 == 0)
			one_open++;
		if (*s == '\"' && *(s - 1) != '\\' && one_open % 2 == 0)
			two_open++;
		s++;
	}
	if (one_open % 2 != 0 || two_open % 2 != 0)
		shell->err = ERR_SYNTAX;
}

// void	parse(t_shell *shell)
// {
// 	shell->line = "\033[0;36m\033[1mminishell \033[1;93m✗ \033[0m";
// 	// ft_putstr_fd("\033[0;36m\033[1mminishell \033[1;93m✗ \033[0m", STDERR);
// 	readline(shell->line);
// 	closed_check(shell, shell->line);
// 	shell->av = ft_split(shell->line, ' ');
// 	if (ft_strncmp(*shell->av, "exit", 4) == 0)
// 	{
// 		ft_putendl_fd("exit", STDOUT);
// 		shell->status = 0;
// 	}
// }
void parse(t_shell *shell)
{
    char *prompt = "\032[0;36m\033[1mminishell \033[1;93m✗ \033[0m";
    shell->line = readline(prompt);
    if (shell->line == NULL) {
        shell->status = 0;
        return;
    }
    closed_check(shell, shell->line);
    shell->av = ft_split(shell->line, ' ');
    if (ft_strncmp(*shell->av, "exit", 4) == 0)
    {
        ft_putendl_fd("exit", STDOUT);
        shell->status = 0;
    }
}