/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:19:32 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/07 05:59:57 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tokenize(t_shell *shell)
{
	// shell->line = delimiter(shell->line, '|');
	shell->av = ft_split(shell->line, ' ');
}
