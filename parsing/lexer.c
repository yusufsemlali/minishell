/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:06:04 by ysemlali &        #+#    #+#             */
/*   Updated: 2024/11/16 16:27:14 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_next_token(char **str)
{
	char	buf[BUFFER_SML];
	int		i;
	char	*s;

	i = 0;
	s = *str;
	ft_bzero(buf, BUFFER_SML);
	while (s[i])
	{
		if (ft_isspace(s[i]) && !inquotes(s, i, 0))
			break ;
		ft_strlcat(buf, s + i, ft_strlen(buf) + 2);
		i++;
	}
	*str += i;
	return (ft_strdup(buf));
}

int	skip_whitespace(char **s)
{
	while (**s && ft_strchr(" \t\r\v\f", **s))
		(*s)++;
	if (**s == '\0')
		return (-1);
	return (0);
}

void	lexer(t_shell *shell)
{
  char buf[BUFFER_SML];
  char *s = shell->s;
  int i = 0;
  shell->t = ft_lnew("", 0, i++, ft_lstlast(shell->token));
  ft_bzero(buf, BUFFER_SML);
	while (1)
	{
    type(shell, *s);
    append(shell, *s, buf);
    if(shell->start)
    {
      printf("%s %d %d\n", shell->t->value, shell->t->type, shell->t->index);
		  ft_lstadd_back(&shell->token, shell->t);
      shell->t = ft_lnew("", 0 , i++, ft_lstlast(shell->token));
      ft_bzero(buf, BUFFER_SML);
     skip_whitespace(&s);
    }
    else
      s++;
    if(shell->end)
      break;
	}
}
