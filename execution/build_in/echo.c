/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali & aclakhda <ysemlali & aclackd    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:29:56 by aclakhda          #+#    #+#             */
/*   Updated: 2024/08/24 23:14:53 by ysemlali &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	echo(t_shell *shell)
{
	char	*av[CMD_MAX_LENGTH];
	int		i;


	if (ft_arrlen(shell->av) <= 1)
		return;
	cmd_maker(shell, av);
	if (ft_strcmp(av[1], "-n") == 0)
	{
		i = 2;
		while (av[i])
		{
			ft_putstr_fd(av[i], 1);
			if (av[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	else
	{
		i = 1;
		while (av[i])
		{
			printf("%s", av[i]);
			if (av[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
}
