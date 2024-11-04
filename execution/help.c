/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:18:41 by aclakhda          #+#    #+#             */
/*   Updated: 2024/10/16 16:18:57 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_errrror(char *file_name)
{
	ft_putstr_fd("minishell: failed to open file \"", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd("\" >~<\n", 2);
}

int	type_check(t_tree *tree)
{
	if (tree->type == OUTPUT || tree->type == INPUT ||\
		tree->type == APPEND || tree->type == HEREDOC)
		return (1);
	return (0);
}