/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:14:36 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/26 21:31:29 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	validate(char *s, t_shell *shell)
{
	if (ft_isdigit(s[0]) || s[0] == '=')
	{
		printf("minishell: export: `%s': not a valid identifier\n", s);
		return (shell->err = 1, g_modes->exit_mode = 1);
	}
	while (*s && *s != '=')
	{
		if (*s == '-' || *s == '+' || *s == '!' || *s == '@' || *s == '#'
			|| *s == '%' || *s == '^' || *s == '&' || *s == '*' || *s == '('
			|| *s == ')' || *s == '[' || *s == ']' || *s == '{' || *s == '}'
			|| *s == ';' || *s == ':' || *s == '"' || *s == '\'' || *s == '\\'
			|| *s == '|' || *s == '<' || *s == '>' || *s == '?' || *s == ','
			|| *s == '.' || *s == '/' || *s == ' ')
		{
			printf("minishell: export: `%s': not a valid identifier\n", s);
			return (shell->err = 1, g_modes->exit_mode = 1);
		}
		s++;
	}
	return (0);
}

void	export_error(t_shell *shell, t_oken *next)
{
	while (next->type == ARGS)
	{
		validate(next->value, shell);
		next = next->next;
	}
}
