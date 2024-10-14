/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:37:17 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/18 10:37:17 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_av(char ***av)
{
	int	i;

	i = 0;
	if (*av != NULL)
	{
		while ((*av)[i])
		{
			free((*av)[i]);
			i++;
		}
	}
	free(*av);
	*av = NULL;
}

void	free_nv(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*env = NULL;
}

void	free_all(t_shell *shell)
{
	free(shell->s);
	free_av(&(shell->av));
	ft_lstclear(&shell->token, del);
	if (shell->end != 0)
	{

		free_nv(&(shell->nv));
		free(shell);
		free(g_modes);
	}
}
