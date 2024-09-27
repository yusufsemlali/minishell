/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:22:54 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/27 00:42:50 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_2(t_shell *shell, int fd[])
{
	t_tree	*tmp;
	int		stdin_copy;

	tmp = shell->tree;
	stdin_copy = dup(STDIN);
	close(fd[1]);
	dup2(fd[0], STDIN);
	close(fd[0]);
	shell->tree = shell->tree->right;
	executing(shell);
	shell->tree = tmp;
	dup2(stdin_copy, STDIN);
	close(stdin_copy);
	free_all_shell(shell, 0);
}

void	child_process(int fd[], t_shell *shell)
{
	t_tree	*tmp;
	int		stdout_copy;

	tmp = shell->tree;
	stdout_copy = dup(STDOUT);
	close(fd[0]);
	dup2(fd[1], STDOUT);
	close(fd[1]);
	shell->tree = shell->tree->left;
	executing(shell);
	shell->tree = tmp;
	dup2(stdout_copy, STDOUT);
	close(stdout_copy);
	free_all_shell(shell, 0);
}

void	handle_child_process(int fd[], t_shell *shell)
{
	int	status;

	g_modes->pid = fork();
	if (g_modes->pid == 0)
		child_process(fd, shell);
	waitpid(g_modes->pid, &status, 0);
	if (WIFEXITED(status))
		g_modes->exit_mode = WEXITSTATUS(status);
	else
		g_modes->exit_mode = 1;
}

void	handle_child_2_process(int fd[], t_shell *shell)
{
	g_modes->pid2 = fork();
	if (g_modes->pid2 == 0)
		child_2(shell, fd);
}

void	ft_pipe(t_shell *shell)
{
	int	fd[2];
	int	status;

	if (pipe(fd) == -1)
	{
		printf("Error: pipe failed\n");
		return ;
	}
	handle_child_process(fd, shell);
	if (g_modes->exit_mode == 130)
	{
		close(fd[0]);
		close(fd[1]);
		return ;
	}
	handle_child_2_process(fd, shell);
	close(fd[0]);
	close(fd[1]);
	waitpid(g_modes->pid2, &status, 0);
	if (WIFEXITED(status))
		g_modes->exit_mode = WEXITSTATUS(status);
	else
		g_modes->exit_mode = 1;
}
