/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rederction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:15:09 by aclakhda          #+#    #+#             */
/*   Updated: 2024/12/02 20:30:46 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_continue_rederect_herd(t_shell *shell)
{
	int		fd;
	int		stdin_copy;
	t_tree	*tmp;

	fd = open(g_modes.name_list[shell->tree->fd - 3], O_RDWR);
	if (fd < 0)
	{
		open_error(NULL);
		g_modes.exit_mode = 1;
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

t_oken	*next(t_oken *token, int i)
{
	t_oken	*tmp;

	if (i)
		_reset(token);
	tmp = token;
	while (tmp)
	{
		if (tmp->type == HEREDOC && tmp->read == 0)
		{
			tmp->read = 1;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (tmp);
}

void	handle_heredoc_line(t_shell *shell, char *line, int *i)
{
	char	*tmp;

	if (ft_strcmp(line, shell->herdoc->line[*i]) == 0)
	{
		shell->tmp = next(shell->tmp, 0);
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
	write(shell->tmp->fd, line, ft_strlen(line));
	write(shell->tmp->fd, "\n", 1);
	free(line);
}

void	process_heredoc(t_shell *shell)
{
	char	*line;
	int		i;

	i = 0;
	shell->tmp = shell->token;
	shell->tmp = next(shell->token, 1);
	while (shell->herdoc->herdoc && g_modes.herdoc_mode != CTRL_C)
	{
		line = readline("> ");
		if (line)
			handle_heredoc_line(shell, line, &i);
		else
		{
			if (shell->herdoc->line[i + 1])
				i++;
			else
			{
				g_modes.exit_mode = 0;
				free_all_shell(shell, 0);
			}
		}
	}
	if (!shell->herdoc->herdoc || g_modes.herdoc_mode != CTRL_C)
		g_modes.exit_mode = 0;
	free_all_shell(shell, 0);
}

void	ft_exec_rederect_herd(t_shell *shell, int j)
{
	int	status;

	status = 0;
	if (j)
	{
		g_modes.pid = fork();
		if (g_modes.pid == 0)
		{
			signal(SIGINT, heredoc_signals);
			g_modes.allow = 0;
			process_heredoc(shell);
		}
		else
			waitpid(g_modes.pid, &status, 0);
		if (WIFEXITED(status))
			g_modes.exit_mode = WEXITSTATUS(status);
	}
	else
	{
		if (ft_strcmp(shell->tree->op, "<<") == 0)
			ft_continue_rederect_herd(shell);
	}
}
