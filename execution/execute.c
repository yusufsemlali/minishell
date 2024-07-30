/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:12:59 by aclakhda          #+#    #+#             */
/*   Updated: 2024/07/30 18:21:23 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// void printAST(t_tree *root, int level, char *side) {
//     if (root == NULL) return;
//     for (int i = 0; i < level; i++) printf("    ");
//     printf("%s (%s)\n", root->op, side);
//     printAST(root->left, level + 1, "left");
//     printAST(root->right, level + 1, "right");
// }

void	ft_free_tree(t_tree *root)
{
	if (root == NULL)
		return;
	ft_free_tree(root->left);
	ft_free_tree(root->right);
	free(root->op);
	free(root);
}

t_tree	*creat_node(char *str)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	node->op = ft_strdup(str);
	node->right = NULL;
	node->left = NULL;
	return (node);
}

t_tree	*tree_attatch(t_tree *root, int start, int end, char **av)
{
	t_tree	*current;
	t_tree	*node;
	int		i;

	current = root;
	i = start + 1;
	while (i <= end)
	{
		node = creat_node(av[i]);
		current->right = node;
		current = node;
		i++;
	}
	return (root);
}

t_tree	*create_tree(t_shell *shell, int start, int end)
{
	t_tree	*root;
	int		i;
	int		has_pipe;

	if (start > end)
		return (NULL);
	has_pipe = 0;
	i = start;
	while (i < end)
	{
		if(ft_strcmp(shell->av[i], "|") == 0)
		{
			has_pipe = i;
			break;
		}
		i++;
	}
	if (!has_pipe)
	{
		root = creat_node(shell->av[start]);
		return (tree_attatch(root, start, end, shell->av));
	}
	root = creat_node(shell->av[has_pipe]);
	root->left = create_tree(shell, start, has_pipe - 1);
	root->right = create_tree(shell, has_pipe + 1, end);
	return (root);
}


int	execute(t_shell *shell)
{
	shell->tree = create_tree(shell, 0, ft_size(shell->av) - 1);//function that creat a tree for my execution algho
	// printAST(shell->tree, 0, "root");//print tree for debugin
	ft_free_tree(shell->tree);
	return(1);
}
