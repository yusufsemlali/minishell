/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:29:56 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/23 17:30:45 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_flag(char *av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (av[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(t_shell *shell)
{
	t_tree	*tmp;
	int		flag;
	int		j;

	tmp = shell->tree->right;
	flag = 0;
	j = 0;
	while (tmp)
	{
		if (tmp->op[0] == '-' && is_flag(tmp->op) && j == 0)
		{
			if (tmp->op[1] != '\0')
				flag = 1;
		}
		else
		{
			printf("%s", tmp->op);
			if (tmp->right)
				printf(" ");
			j = 1;
		}
		tmp = tmp->right;
	}
	if (flag == 0)
		printf("\n");
}
