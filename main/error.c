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
		exit(g_modes.exit_mode);
	}
	else if (ft_strncmp(ptr, "", 1) == 0)
		return (shell->err = 1, 1);
	return (0);
}
