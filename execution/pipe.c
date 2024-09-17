/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:22:54 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/16 18:06:30 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(int fd[], t_shell *shell)
{
	int stdout_copy;

	stdout_copy = dup(STDOUT);
	close(fd[0]);
	dup2(fd[1], STDOUT);
	close(fd[1]);
	shell->tree = shell->tree->left;
	executing(shell);
	dup2(stdout_copy, STDOUT);
	close(stdout_copy);
}

void	parent_process(int fd[], t_shell *shell, pid_t pid)
{
	int stdin_copy;

	stdin_copy = dup(STDIN);
	close(fd[1]);
	dup2(fd[0], STDIN);
	close(fd[0]);
	shell->tree = shell->tree->right;
	executing(shell);
	waitpid(pid, NULL, 0);
	dup2(stdin_copy, STDIN);
	close(stdin_copy);
}

void	ft_pipe(t_shell *shell)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		printf("Error: pipe failed\n");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		printf("Error: fork failed\n");
		return ;
	}
	if (pid == 0)
	{
		child_process(fd, shell);
		exit(0);
	}
	else
		parent_process(fd, shell, pid);
}


