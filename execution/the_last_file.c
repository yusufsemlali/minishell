/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_last_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:50:05 by aclakhda          #+#    #+#             */
/*   Updated: 2024/11/10 16:27:13 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	creat_fd_2(char *file_name, int i)
{
	int	fd;

	if (i)
	{
		fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			print_errrror(file_name);
			g_modes.exit_mode = 1;
			return (-1);
		}
	}
	else
	{
		fd = open_file_for_writing(file_name);
		if (fd < 0)
		{
			print_errrror(file_name);
			g_modes.exit_mode = 1;
			return (-1);
		}
	}
	close(fd);
	return (1);
}

int	file_creation(t_oken *t)
{
	int	fd;

	if (t->type == OUTPUT)
	{
		fd = creat_fd_2(t->next->value, 0);
		if (fd < 0)
			return (1);
	}
	else if (t->type == APPEND)
	{
		fd = creat_fd_2(t->next->value, 1);
		if (fd < 0)
			return (1);
	}
	else if (t->type == INPUT)
	{
		fd = open(t->next->value, O_RDWR, 0644);
		if (fd < 0)
		{
			print_errrror(t->next->value);
			g_modes.exit_mode = 1;
			return (1);
		}
	}
	return (0);
}

int	checks_err(t_shell *shell)
{
	t_oken	*tmp;

	if (g_modes.has_pipe)
	{
		
	}
	else
		tmp = shell->token;
	while (tmp)
	{
		if (!isnt_red(tmp->type))
		{
			if (file_creation(tmp))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}