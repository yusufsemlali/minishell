/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:59:22 by ysemlali          #+#    #+#             */
/*   Updated: 2024/11/04 16:59:26 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_error(char *s)
{
	ft_putstr_fd("MiniShell: export: `", 2);
	ft_putstr_fd(s, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	g_modes.d_change = 1;
	g_modes.exit_mode = 1;
}

int	valid_plus(char current, char next)
{
	if (current == '+' && next != '=')
		return (1);
	return (0);
}

int	validate(char *s)
{
	char	*tmp;

	tmp = s;
	if (ft_isdigit(s[0]) || s[0] == '=')
	{
		write_error(tmp);
		return (1);
	}
	while (*s && *s != '=')
	{
		if (*s == '-' || *s == '!' || *s == '@' || *s == '#' || *s == '%'
			|| *s == '^' || *s == '&' || *s == '*' || *s == '(' || *s == ')'
			|| *s == '[' || *s == ']' || *s == '{' || *s == '}' || *s == ';'
			|| *s == ':' || *s == '"' || *s == '\'' || *s == '\\' || *s == '|'
			|| *s == '<' || *s == '>' || *s == '?' || *s == ',' || *s == '.'
			|| *s == '/' || *s == ' ' || *s == '$' || valid_plus(*s, *(s + 1)))
		{
			write_error(tmp);
			return (1);
		}
		s++;
	}
	return (0);
}
