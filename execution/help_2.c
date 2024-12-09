/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:02:12 by aclakhda          #+#    #+#             */
/*   Updated: 2024/11/09 22:37:25 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_file(t_shell *shell)
{
	int		range;
	t_oken	*tmp;

	tmp = shell->token;
	range = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			range++;
			tmp = tmp->next;
			continue ;
		}
		if (tmp->type == HEREDOC)
		{
			tmp->fd = creat_fd(shell, range, 0);
		}
		tmp = tmp->next;
	}
	creat_fd(shell, range, 1);
}

int	creat_fd(t_shell *shell, int range, int reset)
{
	static int	i;
	static int	fd;

	if (reset)
	{
		i = 0;
		fd = 0;
	}
	else if (!range && !fd)
	{
		fd = set_up_file_name(shell, range);
		return (fd);
	}
	else if (range != i)
	{
		fd = set_up_file_name(shell, range);
		i = range;
		return (fd);
	}
	return (fd);
}

void	_reset(t_oken *token)
{
	t_oken	*tmp;

	tmp = token;
	while (tmp)
	{
		tmp->read = 0;
		tmp = tmp->next;
	}
}

int	check_is_dir_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

void	for_norminet(t_var *var, t_shell *shell)
{
	g_exit_status = 126;
	handle_exec_error(var, shell, 0);
}
