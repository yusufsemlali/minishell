/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:26:56 by aclakhda          #+#    #+#             */
/*   Updated: 2024/08/11 20:56:42 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_cmd_path(char	**av)
{
	char	**path_split;
	char	*cmd_path;
	int		i;

	i = 0;
	if (!access(av[0], X_OK))
		return (av[0]);
	path_split = ft_split(getenv("PATH"), ':');
	if (!path_split)
		return (NULL);
	while (path_split[i])
	{
		cmd_path = creating_cmd_path(strlen(path_split[i]) + strlen(av[0]) + 2, path_split, i, av[0]);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
		{
			s_free(path_split);
			return (cmd_path);
		}
		i++;
		free(cmd_path);
	}
	s_free(path_split);
	return (NULL);
}
void	cmd_maker(t_shell *shell, char **av)
{
	int		i;
	t_tree	*tmp;

	i = 0;
	tmp = shell->tree;
	while (tmp)
	{
		av[i] = tmp->op;
		tmp = tmp->right;
		i++;
	}
	av[i] = NULL;
}

void	ft_exec_bin(t_shell *shell)
{
	char	*av[CMD_MAX_LENGTH];
	char	*cmd_path;
	pid_t 	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		cmd_maker(shell, av);
		cmd_path = find_cmd_path(av);
		if (!cmd_path)
		{
			printf("command not found\n");
			return ;
		}
		if (execve(cmd_path, av, shell->nv) == -1)
			perror("execve");
		free(cmd_path);
	}
	else
		waitpid(pid, &shell->status, 0);
}

void	ft_exec_cmd(t_shell *shell)
{
	(void) shell;
	printf("hey im here ^^");
}

void	executing(t_shell *shell)
{
	if (!ft_strcmp(shell->tree->op, "|"))
	{
		//ft_exec_pipe(shell);
	}
	else if (is_rederaction(shell->tree->op))
	{
		//ft_exec_rederect(shell);
	}
	else if (check_cmd(shell))
		ft_exec_cmd(shell);
	else
		ft_exec_bin(shell);
}
