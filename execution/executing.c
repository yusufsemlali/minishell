/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:26:56 by aclakhda          #+#    #+#             */
/*   Updated: 2024/08/09 21:44:16 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_cmd(t_shell *shell)
{
	if (!ft_strcmp("echo", shell->tree->op) \
		|| !ft_strcmp("cd", shell->tree->op) \
			|| !ft_strcmp("pwd", shell->tree->op) \
				|| !ft_strcmp("export", shell->tree->op) \
					|| !ft_strcmp("unset", shell->tree->op) \
						|| !ft_strcmp("env", shell->tree->op) \
							|| !ft_strcmp("exit", shell->tree->op))
		return (1);
	return (0);
}

void	s_free(char	**av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

char	*creating_cmd_path(int len, char **path_split, int i, char *av)
{
	char	*cmd_path;

	cmd_path = malloc(len * sizeof(char));
	if (!cmd_path)
	{
		s_free(path_split);
		return (NULL);
	}
	ft_strcpy(cmd_path, path_split[i]);
	ft_strcat(cmd_path, "/");
	ft_strcat(cmd_path, av);
	return (cmd_path);
}

char	*find_cmd_path(char	**av, char **nv)
{
	char	**path_split;
	char	*cmd_path;
	int		i;

	(void)nv;
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

void	ft_exec_bin(t_shell *shell)
{
	char	*av[CMD_MAX_LENGTH];
	char	*cmd_path;
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
	cmd_path = find_cmd_path(av, shell->nv);
	printf("path = %s\n", cmd_path);
	if (!cmd_path)
	{
		printf("command not found\n");
		return ;
	}
	if (execve(cmd_path, av, shell->nv) == -1)
		perror("execve");
	free(cmd_path);
}

void	ft_exec_cmd(t_shell *shell)
{
	(void) shell;
	printf("hey im here ^^");
}

int		is_rederaction(char *c)
{
	if (!ft_strcmp(c, ">") \
		|| !ft_strcmp(c, "<") \
			|| !ft_strcmp(c, ">>"))
		return (1);
	return (0);
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
