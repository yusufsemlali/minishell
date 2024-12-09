/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:06:25 by ysemlali          #+#    #+#             */
/*   Updated: 2024/12/09 09:19:30 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error(void *ptr, t_shell *shell)
{
	if (ptr == NULL)
	{
		ft_putendl_fd("exit", 0);
		rl_clear_history();
		shell->end = 1;
		free_all(shell);
		exit(g_exit_status);
	}
	else if (ft_strncmp(ptr, "", 1) == 0)
		return (shell->err = 1, 1);
	return (0);
}

void	open_error(char *str)
{
	char	buf[ONEKB];

	ft_bzero(buf, ONEKB);
	ft_strlcat(buf, "minishell: ", ONEKB);
	ft_strlcat(buf, str, ONEKB);
	perror(buf);
}

void	ambiguous_error(char *str)
{
	char	buf[ONEKB];

	ft_bzero(buf, ONEKB);
	ft_strlcat(buf, "minishell: ", ONEKB);
	ft_strlcat(buf, str, ONEKB);
	ft_strlcat(buf, ": ambiguous redirect", ONEKB);
	ft_putendl_fd(buf, STDERR);
}

void	heredoc_warning(void)
{
	char	buf[ONEKB];

	ft_bzero(buf, ONEKB);
	ft_strlcat(buf, "warning: here-document ", ONEKB);
	ft_strlcat(buf, "delimited by end-of-file\n", ONEKB);
	ft_putstr_fd(buf, STDERR);
}

void	print_err(char *str, int i)
{
	char	buf[ONEKB];

	ft_bzero(buf, ONEKB);
	ft_strlcat(buf, "minishell: ", ONEKB);
	if (i == 1)
	{
		ft_strlcat(buf, str, ONEKB);
		ft_strlcat(buf, ": No such file or directory\n", ONEKB);
	}
	else if (i == 0)
	{
		ft_strlcat(buf, str, ONEKB);
		ft_strlcat(buf, ": Is a directory\n", ONEKB);
	}
	else
	{
		ft_strlcat(buf, str, ONEKB);
		ft_strlcat(buf, ": Permission denied\n", ONEKB);
	}
	ft_putstr_fd(buf, STDERR);
}
