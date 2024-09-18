/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:38:05 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/18 10:38:05 by ysemlali         ###   ########.fr       */
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

char	*get_line(void)
{
	if (g_modes->exit_mode == 0)
		return (readline("🤍 \033[1;36mminishell \033[1;93m✗ \033[0m "));
	return (readline("🖤 \033[1;36mminishell \033[1;93m✗ \033[0m "));
}

void	parse(t_shell *shell)
{
	shell->s = get_line();
	if (error(shell->s))
		return ;
	add_history(shell->s);
	if (closed_checker(shell, shell->s))
	{
		shell->av = ft_token(spacing(shell->s), " \t\r\f\v");
		shell->token = token_lst(shell);
		valid(shell);
		expand(shell);
	}
}
