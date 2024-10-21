/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:12:15 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/19 15:08:26 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->nv;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			printf("%s\n", tmp->value);
			return ;
		}
		tmp = tmp->next;
	}
	g_modes.exit_mode = 0;
}
