/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:12:15 by aclakhda          #+#    #+#             */
/*   Updated: 2024/08/15 15:43:21 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_shell *shell)
{
	int	i;

	i = 0;
	while(shell->nv[i].key)
	{
		if (!ft_strcmp(shell->nv[i].key, "PWD"))
		{
			printf("%s\n", shell->nv[i].value);
			return ;
		}
		i++;
	}
}
