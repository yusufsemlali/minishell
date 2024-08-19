/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:32:37 by aclakhda          #+#    #+#             */
/*   Updated: 2024/08/15 15:48:23 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->nv[i].key)
	{
		printf("%s=%s\n", shell->nv[i].key, shell->nv[i].value);
		i++;
	}
}
