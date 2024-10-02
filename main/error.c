/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:37:12 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/21 22:28:44 by aclakhda         ###   ########.fr       */
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
		exit(g_modes->exit_mode);
	}
	else if (ft_strncmp(ptr, "", 1) == 0)
		return (shell->err = 1, 1);
	return (0);
}
