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

void append(t_shell *shell, char c, char *buf)
{

  if( (shell->t->quote == SINGLE && c == '\'') || ( shell->t->quote == DOUBLE && c == '\"'))
    return;
  if(c == '$' && shell->t->type == expand)
    expand(shell, buf, shell->s + &c);
  if(shell->start == 0)
  {
    buf+= ft_strlen(buf);
   *buf++ = c;
  }
  if (shell->start == 1)
    shell->t->value = ft_strdup(buf);
}
