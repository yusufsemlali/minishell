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

char 	*save_error(char *s)
{
  char tmp[1024];
  ft_bzero(tmp, 1024);
	ft_strlcpy(tmp, "minishell: export: `", 1024);
  ft_strlcat(tmp, s, 1024);
	ft_strlcat(tmp,"': not a valid identifier", 1024);
  return (ft_strdup(tmp));
}

void	validate(char *s, t_shell *shell)
{
	char	*tmp;

	tmp = s;
	if (ft_isdigit(s[0]) || s[0] == '=')
	{
		shell->export_error = save_error(tmp);
		return;
	}
	while (*s && *s != '=')
	{
		if (*s == '-' || *s == '+' || *s == '!' || *s == '@' || *s == '#'
			|| *s == '%' || *s == '^' || *s == '&' || *s == '*' || *s == '('
			|| *s == ')' || *s == '[' || *s == ']' || *s == '{' || *s == '}'
			|| *s == ';' || *s == ':' || *s == '"' || *s == '\'' || *s == '\\'
			|| *s == '|' || *s == '<' || *s == '>' || *s == '?' || *s == ','
			|| *s == '.' || *s == '/' || *s == ' ' || *s == '$')
		{
			shell->export_error = save_error(tmp);
			return;
		}
		s++;
	}
}

void	export_error(t_shell *shell, t_oken *next)
{
	while (next->type == ARGS)
	{
		validate(next->value, shell);
		next = next->next;
	}
}
