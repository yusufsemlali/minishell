/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:26:56 by aclakhda          #+#    #+#             */
/*   Updated: 2024/11/07 19:02:03 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_child_process(t_shell *shell, t_var *var)
{
	var->av = cmd_maker(shell);
	var->cmd_path = find_cmd_path(var->av, shell->nv);
	check_directory(var, shell);
	if (!var->cmd_path || !ft_strlen(shell->tree->op))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(var->av[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		var->av = av_m();
		execve("/bin/sh", var->av, NULL);
		perror("execve");
	}
	else
	{
		var->env = creat_env(shell->nv);
		if (execve(var->cmd_path, var->av, var->env) == -1)
		{
			g_modes.exit_mode = -1;
		}
	}
}

void	wait_for_child_process(void)
{
	waitpid(g_modes.pid, &g_modes.exit_mode, 0);
	if (g_modes.exit_mode == 10752)
		g_modes.exit_mode = 127;
	else
	{
		if (WIFEXITED(g_modes.exit_mode))
			g_modes.exit_mode = WEXITSTATUS(g_modes.exit_mode);
		else
		{
			if (g_modes.exit_mode == 0)
				g_modes.exit_mode = 1;
			else
				g_modes.exit_mode = CTRL_C;
		}
	}
}

void	ft_exec_bin(t_shell *shell)
{
	t_var	var;

	g_modes.pid = fork();
	if (g_modes.pid == -1)
	{
		perror("fork");
		return ;
	}
	if (g_modes.pid == 0)
		exec_child_process(shell, &var);
	else
		wait_for_child_process();
}

void	ft_exec_cmd(t_shell *shell)
{
	if (ft_strcmp(shell->tree->op, "echo") == 0)
	{
		echo(shell);
		g_modes.exit_mode = 0;
	}
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
	else if (ft_strcmp(shell->tree->op, "exit") == 0)
		ft_exit(shell, 1, 1);
}

void	executing(t_shell *shell)
{
	if (!shell->tree)
		return ;
	else if (shell->tree->type == PIPE)
		ft_pipe(shell);
	else if (is_rederaction(shell->tree->op) && type_check(shell->tree))
		ft_exec_rederect(shell);
	else if (check_cmd(shell))
		ft_exec_cmd(shell);
	else
		ft_exec_bin(shell);
}
