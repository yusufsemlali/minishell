/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederextion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:35:04 by aclakhda          #+#    #+#             */
/*   Updated: 2024/10/16 16:22:05 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_file(t_tree *tree, char *file_name)
{
	t_tree	*tmp;

	tmp = tree->left;
	while (tmp)
	{
		if (tmp->file_name != NULL && !ft_strcmp(tmp->file_name, file_name))
			return (1);
		// if (tmp->file_name)
		// 	open(tmp->file_name, O_CREAT, 0644);
		tmp = tmp->right;
	}
	return (0);
}

void	ft_exec_rederect_in(t_shell *shell)
{
	int		fd;
	int		stdin_copy;
	t_tree	*tmp;

	if (check_file(shell->tree, shell->tree->file_name))
		fd = open(shell->tree->file_name, O_RDWR | O_CREAT, 0644);
	else
	{
		print_errrror(shell->tree->file_name);
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

void	ft_exec_rederect_out(t_shell *shell)
{
	int		fd;
	int		stdout_copy;
	t_tree	*tmp;

	stdout_copy = dup(STDOUT);
	fd = open_file_for_writing(shell->tree->file_name);
	if (fd < 0)
	{
		print_errrror(shell->tree->file_name);
		g_modes.exit_mode = 1;
		return ;
	}
	redirect_output(shell, fd);
	close(fd);
	tmp = shell->tree;
	shell->tree = shell->tree->left;
	executing(shell);
	shell->tree = tmp;
	dup2(stdout_copy, STDOUT);
	close(stdout_copy);
}

void	ft_exec_rederect_out_append(t_shell *shell)
{
	int		fd;
	int		stdout_copy;
	t_tree	*tmp;

	stdout_copy = dup(STDOUT);
	fd = open(shell->tree->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("Error: open failed\n");
		g_modes.exit_mode = 1;
		return ;
	}
	redirect_output(shell, fd);
	close(fd);
	tmp = shell->tree;
	shell->tree = shell->tree->left;
	executing(shell);
	shell->tree = tmp;
	dup2(stdout_copy, STDOUT);
	close(stdout_copy);
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
