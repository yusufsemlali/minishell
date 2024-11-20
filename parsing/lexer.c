/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:06:04 by ysemlali &        #+#    #+#             */
/*   Updated: 2024/11/20 02:07:03 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_whitespace(char **s)
{
	while (**s && ft_isspace(**s))
		(*s)++;
	if (**s == '\0')
		return (-1);
	return (0);
}

void	lexer(t_shell *shell)
{
	char	*buffer = ft_calloc(shell->len, 1);
	char	token[BUFFER_SML];
	int		run;
	int		i;
	run = 0;
	i = 0;
	ft_bzero(token, BUFFER_SML);
	shell->t = ft_lnew(NULL, 0, i++, NULL);
	ft_strlcpy(buffer, shell->s, shell->len);
	shell->r = buffer;
	while (1)
	{
		type(shell, *shell->r, &run);
		append(shell, token , &run);
		if (run == END)
		{
			shell->t->value = ft_strdup(token);
			ft_lstadd_back(&shell->token, shell->t);
			shell->t = ft_lnew(NULL, 0, i++, ft_lstlast(shell->token));
			ft_bzero(token, BUFFER_SML);
			skip_whitespace(&shell->r);
			if (*shell->r == '\0')
				break ;
		}
    else
			shell->r++;
	}
}
