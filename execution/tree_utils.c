/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:00:54 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/27 01:05:35 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tree	*create_redirection_node(t_oken *last_r_pip)
{
	t_tree	*root;

	root = creat_node(last_r_pip->value, last_r_pip->next->value);
	last_r_pip->read = 1;
	return (root);
}

t_oken	*find_next_token(t_oken *current)
{
	while (current && (current->type != PIPE || isnt_red(current->type)))
		current = current->next;
	return (current);
}

t_tree	*creat_tree_red(t_oken *tokens, t_oken *last_r_pip)
{
	t_tree	*root;

	root = NULL;
	if (last_r_pip->next)
	{
		root = create_redirection_node(last_r_pip);
		handle_left_subtree(root, tokens, last_r_pip);
		handle_right_subtree(root, last_r_pip);
	}
	return (root);
}

t_oken	*creat_token_pipe(t_oken *tokens, t_oken *last_red_p)
{
	t_oken	*pipe_left;
	t_oken	*tmp;
	t_oken	*tmp2;

	if (!tokens)
		return (NULL);
	tmp2 = NULL;
	tmp = tokens;
	while (tmp != last_red_p)
	{
		pipe_left = ft_lstnew(ft_strdup(tmp->value), tmp->type);
		pipe_left->read = tmp->read;
		ft_lstadd_back(&tmp2, pipe_left);
		tmp = tmp->next;
	}
	return (tmp2);
}

t_tree	*creat_tree_pipe(t_oken *tokens, t_oken *last_red_p)
{
	t_tree	*root;
	t_oken	*pipe_left;
	t_oken	*pipe_right;

	pipe_left = creat_token_pipe(tokens, last_red_p);
	pipe_right = last_red_p->next;
	root = NULL;
	g_modes->pipe_count--;
	last_red_p->read = 1;
	g_modes->has_pipe = 1;
	root = creat_node(last_red_p->value, NULL);
	if (last_red_p->next)
		root->right = create_tree(pipe_right);
	root->left = create_tree(pipe_left);
	ft_free_token(pipe_left);
	return (root);
}