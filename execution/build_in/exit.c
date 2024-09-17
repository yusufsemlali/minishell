/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:55:33 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/17 17:56:49 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_shell *shell)
{
	printf("here\n");
	if (shell->tree->right)
	{
		if (shell->tree->right->op)
		{
			if (is_numeric(shell->tree->right->op))
				g_modes->exit_mode = ft_atoi(shell->tree->right->op);
			else
			{
				ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
				ft_putstr_fd(shell->tree->right->op, STDERR_FILENO);
				ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
				g_modes->exit_mode = 2;
			}
		}
		else
			g_modes->exit_mode = 255;
	}
	else
		g_modes->exit_mode = 0;
	if (shell->tree->right && shell->tree->right->right)
	{
		shell->tree->right->right->op = "1";
		if (!is_numeric(shell->tree->right->op))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(shell->tree->right->op, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit(2);
		}
		else
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			g_modes->exit_mode = 1;
			return;
		}
	}
	free_herdoc(shell->herdoc);
	ft_free_tree(shell->tree);
	close(shell->fd);
	unlink("tmp");
	free_all(shell);
	exit(g_modes->exit_mode);
}
