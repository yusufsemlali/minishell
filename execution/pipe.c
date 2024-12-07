/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:22:54 by aclakhda          #+#    #+#             */
/*   Updated: 2024/11/29 00:29:53 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_2(t_shell *shell, int fd[])
{
	t_tree	*tmp;
	int		stdin_copy;

	shell->allow = 0;
	tmp = shell->tree;
	shell->allow = 1;
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

	shell->allow = 0;
	tmp = shell->tree;
	shell->allow = 1;
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
	shell->pid = fork();
	if (shell->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		child_process(fd, shell);
	}
}

void	handle_child_2_process(int fd[], t_shell *shell)
{
	int	status;
	int	bocchi;

	bocchi = 0;
	status = 0;
	shell->pid2 = fork();
	if (shell->pid2 == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		child_2(shell, fd);
	}
	waitpid(shell->pid, &bocchi, 0);
	close(fd[1]);
	waitpid(shell->pid2, &status, 0);
	close(fd[0]);
	handle_child_termination(status);
}

void	ft_pipe(t_shell *shell)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("failed to open pipe\n", 2);
		return ;
	}
	handle_child_process(fd, shell);
	handle_child_2_process(fd, shell);
}
