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


void	closed_checker(t_shell *shell, char *s)
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
	{
		shell->err = ERR_SYNTAX;
		shell->begin = NULL;
	}
}

void parse(t_shell *shell)
{
	// const char *prompt = "\033[0;36m\033[1mminishell \033[1;93m✗ \033[0m";
	shell->line = readline("\033[0;36m\033[1mminishell \033[1;93m✗ \033[0m ");
    if (shell->line == NULL) {
        shell->status = 0;
        return;
    }
	add_history(shell->line);
    closed_checker(shell, shell->line);
	seperators_checker(shell, shell->line);
    shell->av = ft_split(shell->line, ' ');
}