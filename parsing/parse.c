/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:22:58 by ysemlali          #+#    #+#             */
/*   Updated: 2024/07/26 00:35:45 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*read_line(char **line)
{
	char	*line;
	size_t	bufsize;

	line = NULL;
	bufsize = 0;
	getline(line, &bufsize, stdin);
	return (line);
}

void	closed_check(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->line[i])
	{
		if (shell->line[i] == '\"' || shell->line[i] == '\'')
		{
			i++;
			while (shell->line[i] != '\"' || shell->line[i] != '\'')
				i++;
		}
		if (shell->line[i] == '\\')
			i++;
		i++;
	}
	if (shell->line[i] == '\0')
		shell->err = 1;
}

void	parse(t_shell *shell)
{
	printf("minishell$ ");
	read_line(&shell->line);
	closed_check(shell->line);
	shell->av = ft_split(shell->line, ' ');
	if (ft_strncmp(*shell->av, "exit", 4) == 0)
	{
		printf("exit\n");
		shell->status = 0;
	}
}