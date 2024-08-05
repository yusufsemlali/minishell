/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:46:55 by aclakhda          #+#    #+#             */
/*   Updated: 2024/08/05 11:37:36 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_size(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

void	ft_found(t_shell *shell, t_var *var, int start, int end)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	var->i = start;
	while (var->i < end)
	{
		if (ft_strcmp(shell->av[var->i], "|") == 0 && i == 0)
		{
			i++;
			var->has_pipe = var->i;
		}
		if (!ft_strcmp(shell->av[var->i], ">") \
			|| !ft_strcmp(shell->av[var->i], "<") \
				|| !ft_strcmp(shell->av[var->i], ">>"))
		{
			if (j == 0)
				var->has_rederect = var->i;
		}
		var->i++;
	}
}

void	ft_free_tree(t_tree *root)
{
	if (root == NULL)
		return ;
	ft_free_tree(root->left);
	ft_free_tree(root->right);
	free(root->op);
	free(root);
}
