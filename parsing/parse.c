/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:37:36 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/13 14:37:41 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	closed_checker(t_shell *shell, char *s)
{
	int	one_open;
	int	two_open;

	one_open = 0;
	two_open = 0;
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

void	parse(t_shell *shell)
{
	// const char *prompt = "\033[0;36m\033[1mminishell \033[1;93m✗ \033[0m";
	shell->line = readline("\033[0;36m\033[1mminishell \033[1;93m✗ \033[0m ");
	if (shell->line == NULL || shell->line[0] == '\0')
		return ;
	add_history(shell->line);
	closed_checker(shell, shell->line);
	tokenize(shell);
}
