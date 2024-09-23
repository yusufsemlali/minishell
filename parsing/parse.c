/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:44:55 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/21 18:10:40 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	closed_checker(t_shell *shell, char *s)
{
	int	one_open;
	int	two_open;

	one_open = 0;
	two_open = 0;
	while (*s)
	{
		if (*s == '\'' && two_open % 2 == 0)
			one_open++;
		else if (*s == '\"' && one_open % 2 == 0)
			two_open++;
		s++;
	}
	if (one_open % 2 != 0)
		ft_putendl_fd("minishell: syntax error near unexpected token `'", 2);
	if (two_open % 2 != 0)
		ft_putendl_fd("minishell: syntax error near unexpected token `\"'", 2);
	if (one_open % 2 != 0 || two_open % 2 != 0)
		return (shell->err = ERR_SYNTAX, 0);
	return (1);
}



void	parse(t_shell *shell)
{
	shell->s = readline("\033[1;36mminishell \033[1;93m✗ \033[0m ");
	if (error(shell->s, shell))
		return ;
	add_history(shell->s);
	if (closed_checker(shell, shell->s))
	{
		shell->av = ft_token(spacing(shell->s), " \t\r\f\v");
		expand(shell);
		squish(shell);
		token_lst(shell);
		valid(shell);
	}
}
