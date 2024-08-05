/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:26:56 by aclakhda          #+#    #+#             */
/*   Updated: 2024/08/05 11:37:04 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_cmd(t_shell *shell)
{
	if (!ft_strcmp("echo", shell->tree->op) \
		|| !ft_strcmp("cd", shell->tree->op) \
			|| !ft_strcmp("pwd", shell->tree->op) \
				|| !ft_strcmp("export", shell->tree->op) \
					|| !ft_strcmp("unset", shell->tree->op) \
						|| !ft_strcmp("env", shell->tree->op) \
							|| !ft_strcmp("exit", shell->tree->op))
		return (1);
	return (0);
}

void	ft_exec_bin(t_shell *shell)
{
	char	*av[CMD_MAX_LENGTH];
	int		i;
	t_tree	*tmp;

	i = 0;
	tmp = shell->tree;
	while (tmp)
	{
		av[i] = tmp->op;
		tmp = tmp->right;
		i++;
	}
	av[i] = NULL;
	while (av[i])
	{
		printf("av[%d] = %s\n", i, av[i]);
		i++;
	}
	if (execve(av[0], av, shell->nv) == -1)
		perror("execve");
}

void	ft_exec_cmd(t_shell *shell)
{
	(void) shell;
	printf("hey im here ^^");
}

void	executing(t_shell *shell)
{
	if (check_cmd(shell))
		ft_exec_cmd(shell);
	else
		ft_exec_bin(shell);
}
