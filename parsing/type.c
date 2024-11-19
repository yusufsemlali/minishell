/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:59:33 by ysemlali          #+#    #+#             */
/*   Updated: 2024/11/19 18:33:46 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	type(t_shell *shell, char c)
{
	shell->start = 0;
	if (c == '\"' && shell->t->quote == DOUBLE)
    shell->t->quote = 0;
  if( c== '\'' && shell->t->quote == SINGLE)
    shell->t->quote = 0;
	if (c == '\"' && shell->t->quote == 0)
		shell->t->quote = DOUBLE;
	if (c == '\'' && shell->t->quote == 0)
		shell->t->quote = SINGLE;
	if (c == '|' && shell->t->quote == 0)
		shell->t->type = PIPE;
	if (c == '>' && shell->t->quote == 0 && shell->t->type != OUTPUT)
		shell->t->type = OUTPUT;
  if (c == '<' && shell->t->quote == 0 && shell->t->type != INPUT)
    shell->t->type = INPUT; 
	if (c == '>' && shell->t->quote == 0 && shell->t->type == OUTPUT)
		shell->t->type = APPEND;
  if (c == '<' && shell->t->quote == 0 && shell->t->type == INPUT)
    shell->t->type = HEREDOC;
  if(ft_isalnum(c) && shell->t->index == 0)
    shell->t->type = CMD;
  if(ft_isalnum(c) && shell->t->index != 0)
    shell->t->type = ARGS;
  if (c == '$' && shell->t->quote != SINGLE )
    shell->t->expand = 1;
  if ((ft_isspace(c) && shell->t->quote == 0 ) || c == '\0')  
    shell->start = 1;
  if(c == '\0')
    shell->end = 1;
}
