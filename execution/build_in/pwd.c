/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:12:15 by aclakhda          #+#    #+#             */
/*   Updated: 2024/08/19 11:46:22 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_shell *shell)
{
	int		i;
	t_env	*tmp;

	if (shell->tree->right)
	{
		printf("pwd : too many arguments\n");
		return ;
	}
	tmp = shell->nv;
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			printf("%s\n", tmp->value);
			return ;
		}
		tmp = tmp->next;
	}
}
