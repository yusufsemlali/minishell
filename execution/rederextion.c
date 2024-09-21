/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederextion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:35:04 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/21 23:00:07 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_rederect_in(t_shell *shell)
{
	int	fd;
	int	stdin_copy;

	fd = open(shell->tree->file_name, O_RDONLY);
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
	fd = open(shell->tree->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("Error: open failed\n");
		return ;
	}
	if (shell->r_fd)
		dup2(shell->r_fd, STDOUT);
	else
	{
		shell->r_fd = fd;
		dup2(fd, STDOUT);
	}
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
	fd = open(shell->tree->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("Error: open failed\n");
		return ;
	}
	if (shell->r_fd)
		dup2(shell->r_fd, STDOUT);
	else
	{
		shell->r_fd = fd;
		dup2(fd, STDOUT);
	}
	close(fd);
	shell->tree = shell->tree->left;
	executing(shell);
	dup2(stdout_copy, STDOUT);
	close(stdout_copy);
}

void	ft_continue_rederect_herd(t_shell *shell)
{
	int	fd;
	int	stdin_copy;

	fd = open("tmp", O_RDONLY);
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

void	ft_exec_rederect_herd(t_shell *shell, int j)
{
	char		*line;
	char		*tmp;
	int			i;

	i = 0;
	if (j)
	{
		while (shell->herdoc->herdoc && g_modes->herdoc_mode != CTRL_C)
		{
			line = readline("> ");
			if (line)
			{
				if (ft_strcmp(line, shell->herdoc->line[i]) == 0)
				{
					free(line);
					i++;
					shell->herdoc->herdoc--;
					continue;
				}
				tmp = line;
				if (!ft_strcmp(line = var(line, shell->nv), ""))
					line = tmp;
				write(shell->fd, line, ft_strlen(line));
				write(shell->fd, "\n", 1);
				free(line);
			}
			else
				break ;
		}
	}
	else
	{
		if (ft_strcmp(shell->tree->op, "<<") == 0)
			ft_continue_rederect_herd(shell);
	}
}

void	ft_exec_rederect(t_shell *shell)
{
	if (ft_strcmp(shell->tree->op, ">") == 0)
		ft_exec_rederect_out(shell);
	else if (ft_strcmp(shell->tree->op, ">>") == 0)
		ft_exec_rederect_out_append(shell);
	else if (ft_strcmp(shell->tree->op, "<") == 0)
		ft_exec_rederect_in(shell);
	else if (ft_strcmp(shell->tree->op, "<<") == 0)
		ft_exec_rederect_herd(shell, 0);
}
