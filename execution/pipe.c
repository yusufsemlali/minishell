/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:22:54 by aclakhda          #+#    #+#             */
/*   Updated: 2024/08/29 11:57:16 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipe(t_shell *shell)
{
	int		fd[2];
	int		stdout_copy;
	int		stdin_copy;
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
		close(fd[0]);
		stdout_copy = dup(STDOUT);
		dup2(fd[1], STDOUT);
		close(fd[1]);
		shell->tree = shell->tree->left;
		printf("left = %s\n", shell->tree->op);
		executing(shell);
		dup2(stdout_copy, STDOUT);
		close(stdout_copy);
		exit(0);
	}
	else
	{
		close(fd[1]);
		stdin_copy = dup(STDIN);
		dup2(fd[0], STDIN);
		close(fd[0]);
		shell->tree = shell->tree->right;
		executing(shell);
		dup2(stdin_copy, STDIN);
		close(stdin_copy);
		waitpid(pid, NULL, 0);
	}
}
