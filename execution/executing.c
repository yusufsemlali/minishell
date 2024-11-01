/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:26:56 by aclakhda          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	random_number_gen(void)
{
	unsigned int r_num;
	int fd;

	fd = open("/dev/urandom", O_RDONLY);
	read(fd, &r_num, sizeof(r_num));
	close(fd);
	return ((r_num % 10));
}

char	*random_name_gen(void)
{
	char arr[10] = "aSDmNoZ@_k";
	char *str;
	int i;

	i = 0;
	str = (char *)malloc(sizeof(char) * 11);
	while (i < 9)
	{
		str[i] = arr[random_number_gen()];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	printt(char *file_name)
{
	char	*line;
	int		fd;

	fd = open(file_name, O_CREAT | O_RDWR, 0644);
	line = get_next_line(fd);
	if (line)
	{
		ft_putstr_fd(line, 2);
		free(line);
	}
	close(fd);
}

void	random_err(char **av)
{
	int			fd;
	char		*r_file;
	char		*n_file;

	r_file = random_name_gen();
	n_file = ft_strjoin(".", r_file);
	fd = open (n_file, O_CREAT | O_RDWR | O_APPEND, 0644);
	int  i = rand() % 10000 ;
	while (i)
		i--;
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(av[0], fd);
	ft_putstr_fd(": is a directory\n", fd);
	close(fd);
	printt(n_file);
	free(r_file);
	unlink(n_file);
	free(n_file);
}

void	print_err(char *str, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (i == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a file\n", 2);
	}
}

void check_directory(t_var *var, t_shell *shell)
{
	struct stat path_stat;

	if (stat(var->cmd_path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			print_err(var->av[0], 0);
			g_modes.exit_mode = 126;
			handle_exec_error(var, shell, 0);
		}
	}
}

void	exec_child_process(t_shell *shell, t_var *var)
{
	var->av = cmd_maker(shell);
	var->cmd_path = find_cmd_path(var->av, shell->nv);
	if (var->cmd_path)
		check_directory(var, shell);
	if (!var->cmd_path && ft_strcmp(var->av[0], "./minishell") != 0)
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
	else if (!ft_strcmp(shell->tree->op, "|"))
		ft_pipe(shell);
	else if (is_rederaction(shell->tree->op))
		ft_exec_rederect(shell);
	else if (check_cmd(shell))
		ft_exec_cmd(shell);
	else
		ft_exec_bin(shell);
}
