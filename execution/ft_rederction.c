/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rederction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:15:09 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/26 23:31:07 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_continue_rederect_herd(t_shell *shell)
{
	int		fd;
	int		stdin_copy;
	t_tree	*tmp;

	fd = open("tmp", O_RDWR);
	if (fd < 0)
	{
		printf("Error: open failed\n");
		g_modes->exit_mode = 1;
		return ;
	}
	stdin_copy = dup(STDIN);
	dup2(fd, STDIN);
	close(fd);
	tmp = shell->tree;
	shell->tree = shell->tree->left;
	executing(shell);
	shell->tree = tmp;
	dup2(stdin_copy, STDIN);
	close(stdin_copy);
}

void	handle_heredoc_line(t_shell *shell, char *line, int *i)
{
	char	*tmp;

	if (ft_strcmp(line, shell->herdoc->line[*i]) == 0)
	{
		free(line);
		(*i)++;
		shell->herdoc->herdoc--;
		return ;
	}
	tmp = line;
	line = var(line, shell->nv);
	if (!ft_strcmp(line, ""))
	{
		free(line);
		line = tmp;
	}
	else
		free(tmp);
	write(shell->fd, line, ft_strlen(line));
	write(shell->fd, "\n", 1);
	free(line);
}

void	process_heredoc(t_shell *shell)
{
	char	*line;
	int		i;

	i = 0;
	while (shell->herdoc->herdoc && g_modes->herdoc_mode != CTRL_C)
	{
		line = readline("> ");
		if (line)
			handle_heredoc_line(shell, line, &i);
		else
		{
			g_modes->exit_mode = 0;
			exit(g_modes->exit_mode);
		}
	}
	if (!shell->herdoc->herdoc || g_modes->herdoc_mode != CTRL_C)
		g_modes->exit_mode = 0;
	exit(g_modes->exit_mode);
}

void	ft_exec_rederect_herd(t_shell *shell, int j)
{
	if (j)
	{
		g_modes->pid = fork();
		if (g_modes->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			process_heredoc(shell);
		}
		else
			waitpid(g_modes->pid, &g_modes->exit_mode, 0);
	}
	else
	{
		if (ft_strcmp(shell->tree->op, "<<") == 0)
			ft_continue_rederect_herd(shell);
	}
}
