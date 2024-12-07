/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_last_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:50:05 by aclakhda          #+#    #+#             */
/*   Updated: 2024/11/18 22:27:19 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			nothing(t);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	ambig(t_oken *tmp)
{
	if (ft_strncmp(tmp->next->value, "$", 1) == 0)
	{
		ambiguous_error(tmp->next->value);
		exit_mode = 1;
		return (1);
	}
	return (0);
}

int	v_alide(int area_len, t_oken *tmp)
{
	while (tmp && area_len)
	{
		if (!isnt_red(tmp->type, 0))
		{
			if (ambig(tmp))
				return (0);
			if (file_creation(tmp))
				return (0);
		}
		area_len--;
		tmp = tmp->next;
	}
	return (1);
}

int	area_check(t_shell *shell)
{
	t_var	var;
	t_oken	*tmp;

	var.begin = 0;
	tmp = return_tmp(shell);
	var.end = tmp->index;
	tmp = tmp->prev;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->index == 0)
			break ;
		tmp = tmp->prev;
	}
	var.begin = tmp->index;
	var.area_len = var.end - var.begin;
	if (!v_alide(var.area_len, tmp))
		return (1);
	return (0);
}

int	checks_err(t_shell *shell)
{
	if (area_check(shell))
		return (1);
	return (0);
}
