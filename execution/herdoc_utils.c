/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:07:08 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/27 02:54:13 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_herdoc(t_herdoc *herdoc)
{
	int	i;

	i = 0;
	if (herdoc)
	{
		while (herdoc->line[i])
		{
			free(herdoc->line[i]);
			i++;
		}
		free(herdoc->line);
		free(herdoc);
		herdoc = NULL;
	}
}

void	handle_exec_error(t_var *var, t_shell *shell)
{
	perror("execve");
	free(var->cmd_path);
	lazy_free(var->env, env_size(shell->nv));
	exit(g_modes->exit_mode);
}

int	set(t_oken *token)
{
	t_oken	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			i++;
		tmp = tmp->next;
	}
	return (i);
}