/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali & aclakhda <ysemlali & aclackd    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:26:56 by aclakhda          #+#    #+#             */
/*   Updated: 2024/08/29 12:13:00 by ysemlali &       ###   ########.fr       */
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
	t_var	var;

	var.pid = fork();
	if (var.pid == -1)
	{
		perror("fork");
		return ;
	}
	if (var.pid == 0)
	{
		cmd_maker(shell, var.av);
		var.cmd_path = find_cmd_path(var.av);
		if (!var.cmd_path)
		{
			printf("command not found\n");
			return ;
		}
		// var.env = creat_env(shell->nv);
		if (execve(var.cmd_path, var.av,shell->env) == -1)
			perror("execve");
		free(var.cmd_path);
		s_free(var.env);
	}
	else
		waitpid(var.pid, &shell->status, 0);
}

void	ft_exec_cmd(t_shell *shell)
{
	if (ft_strcmp(shell->tree->op, "echo") == 0)
		echo(shell);
	else if (ft_strcmp(shell->tree->op, "cd") == 0)
		cd(shell);
	else if (ft_strcmp(shell->tree->op, "env") == 0)
		env(shell);
	else if (ft_strcmp(shell->tree->op, "pwd") == 0)
		pwd(shell);
	else if (ft_strcmp(shell->tree->op, "export") == 0)
		export(shell);
	else if (ft_strcmp(shell->tree->op, "unset") == 0)
		unset(shell);
}

void	executing(t_shell *shell)
{
	if (!shell->tree)
		return ;
	if (!ft_strcmp(shell->tree->op, "|"))
	{
		//ft_exec_pipe(shell);
	}
	else if (is_rederaction(shell->tree->op))
	{
		ft_exec_rederect(shell);
	}
	else if (check_cmd(shell))
		ft_exec_cmd(shell);
	else
		ft_exec_bin(shell);
}
