/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:38:44 by ysemlali          #+#    #+#             */
/*   Updated: 2024/11/19 18:38:44 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"


char	*joining(char *s1, char *s2)
{
  char	*result;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = ft_calloc(sizeof(char) * (len1 + len2 + 1), 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	return (result);
}


void append(t_shell *shell, char *buf, int *run)
{
  char buffer[BUFFER_SML];

  ft_bzero(buffer, BUFFER_SML);
  if( (shell->t->quote == SINGLE && *shell->r == '\'') || ( shell->t->quote == DOUBLE && *shell->r == '\"'))
    return;
  if (shell->t->expand == EXPAND)
  {
    shell->t += expand(shell, buffer, shell->r, shell->t->prev );
    shell->r = ft_strdup(buffer);
    shell->t->expand = 0;
    return;
  }
  if(*run == 0)
  {
    buf+= ft_strlen(buf);
   *buf++ = *shell->r;
  }
}
