/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:22:54 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/25 21:30:01 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(int fd[], t_shell *shell)
{
	int		stdout_copy;
	t_tree	*tmp;

	printf("child %s\n", shell->tree->left->op);
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

void	parent_process(int fd[], t_shell *shell, pid_t pid)
{
	int		stdin_copy;
	t_tree	*tmp;

	tmp = shell->tree;
	stdin_copy = dup(STDIN);
	close(fd[1]);
	dup2(fd[0], STDIN);
	close(fd[0]);
	shell->tree = shell->tree->right;
	waitpid(pid, NULL, 0);
	executing(shell);
	shell->tree = tmp;
	dup2(stdin_copy, STDIN);
	close(stdin_copy);
}

void	ft_pipe(t_shell *shell)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		printf("Error: pipe failed\n");
		return ;
	}
	g_modes->pid = fork();
	if (g_modes->pid == -1)
	{
		printf("Error: fork failed\n");
		return ;
	}
	if (g_modes->pid == 0)
	{
		child_process(fd, shell);
		exit(0);
	}
	else
		parent_process(fd, shell, g_modes->pid);
}
