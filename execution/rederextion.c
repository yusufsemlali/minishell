/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederextion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:35:04 by aclakhda          #+#    #+#             */
/*   Updated: 2024/08/27 14:50:57 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_rederect_in(t_shell *shell)
{
	int	fd;
	int	stdin_copy;

	fd = open(shell->tree->right->op, O_RDONLY | O_CREAT);
	if (fd < 0)
	{
		printf("Error: open failed\n");
		return ;
	}
	stdin_copy = dup(STDIN);
	dup2(fd, STDIN);
	close(fd);
	shell->tree = shell->tree->left;
	executing(shell);
	dup2(stdin_copy, STDIN);
	close(stdin_copy);
}

void	ft_exec_rederect_out(t_shell *shell)
{
	int	fd;
	int	stdout_copy;

	stdout_copy = dup(STDOUT);
	fd = open(shell->tree->right->op, O_RDONLY| O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0)
	{
		printf("Error: open failed\n");
		return ;
	}
	dup2(fd, STDOUT);
	close(fd);
	shell->tree = shell->tree->left;
	executing(shell);
	dup2(stdout_copy, STDOUT);
	close(stdout_copy);
}


void	ft_exec_rederect_out_append(t_shell *shell)
{
	int	fd;
	int	stdout_copy;

	stdout_copy = dup(STDOUT);
	fd = open(shell->tree->right->op, O_RDONLY| O_WRONLY | O_CREAT | O_APPEND);
	if (fd < 0)
	{
		printf("Error: open failed\n");
		return ;
	}
	dup2(fd, STDOUT);
	close(fd);
	shell->tree = shell->tree->left;
	executing(shell);
	dup2(stdout_copy, STDOUT);
	close(stdout_copy);
}

void	ft_exec_rederect(t_shell *shell)
{
	if (ft_strcmp(shell->tree->op, ">") == 0)
		ft_exec_rederect_out(shell);
	else if (ft_strcmp(shell->tree->op, ">>") == 0)
		ft_exec_rederect_out_append(shell);
	else if (ft_strcmp(shell->tree->op, "<") == 0)
		ft_exec_rederect_in(shell);
}
