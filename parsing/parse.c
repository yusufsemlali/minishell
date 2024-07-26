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

void	read_line(char **line)
{
	size_t	bufsize;

	bufsize = 0;
	getline(line, &bufsize, stdin);

}

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

void	parse(t_shell *shell)
{
	ft_putstr_fd("\033[0;36m\033[1mminishell \033[1;93m✗ \033[0m", STDERR);
	read_line(&shell->line);
	closed_check(shell, shell->line);
	shell->av = ft_split(shell->line, ' ');
	if (ft_strncmp(*shell->av, "exit", 4) == 0)
	{
		ft_putendl_fd("exit", STDOUT);
		shell->status = 0;
	}
}