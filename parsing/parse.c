/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 01:38:32 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/29 11:38:53 by aclakhda         ###   ########.fr       */
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
		if (s > shell->s && *(s - 1) == '\\')
			;
		else if (*s == '\'' && two_open % 2 == 0)
			one_open++;
		else if (*s == '\"' && one_open % 2 == 0)
			two_open++;
		s++;
	}
	if (one_open % 2 != 0 || two_open % 2 != 0)
		shell->err = ERR_SYNTAX;
}

char	*get_line(void)
{
	char	*ok;
	char	*ko;

	ok = "🤍 \033[1;36mminishell \033[1;93m✗ \033[0m ";
	ko = "🖤 \033[1;36mminishell \033[1;93m✗ \033[0m ";
	if (g_modes->exit_mode == 0)
		return (readline(ok));
	else
		return (readline(ko));
}

void	parse(t_shell *shell)
{
	shell->s = get_line();
	if (shell->s == NULL || shell->s[0] == '\0')
		return ;
	add_history(shell->s);
	closed_checker(shell, shell->s);
	tokenize(shell);
}
