/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:06:25 by ysemlali          #+#    #+#             */
/*   Updated: 2024/11/04 16:58:37 by ysemlali         ###   ########.fr       */
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
	char	buf[BUFFER_SML];

	ft_bzero(buf, BUFFER_SML);
	ft_strlcat(buf, "minishell: ", BUFFER_SML);
	ft_strlcat(buf, str, BUFFER_SML);
	perror(buf);
}

void	ambiguous_error(char *str)
{
	char	buf[BUFFER_SML];

	ft_bzero(buf, BUFFER_SML);
	ft_strlcat(buf, "minishell: ", BUFFER_SML);
	ft_strlcat(buf, str, BUFFER_SML);
	ft_strlcat(buf, ": ambiguous redirect", BUFFER_SML);
	ft_putendl_fd(buf, STDERR);
}

void	print_err(char *str, int i)
{
	char	buf[BUFFER_SML];

	ft_bzero(buf, BUFFER_SML);
	ft_strlcat(buf, "minishell: ", BUFFER_SML);
	if (i == 1)
	{
		ft_strlcat(buf, str, BUFFER_SML);
		ft_strlcat(buf, ": No such file or directory\n", BUFFER_SML);
	}
	else if (i == 0)
	{
		ft_strlcat(buf, str, BUFFER_SML);
		ft_strlcat(buf, ": Is a directory\n", BUFFER_SML);
	}
	else
	{
		ft_strlcat(buf, str, BUFFER_SML);
		ft_strlcat(buf, ": Permission denied\n", BUFFER_SML);
	}
	ft_putstr_fd(buf, STDERR);
}
