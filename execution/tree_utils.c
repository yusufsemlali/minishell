/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:00:54 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/25 00:34:41 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tree	*creat_tree_red(t_oken *tokens, t_oken *last_r_pip)
{
	t_tree	*root;
	t_oken	*tmp;
	t_oken	*new_token;

	root = NULL;
	tmp = NULL;
	new_token = NULL;
	last_r_pip->read = 1;
	if (last_r_pip->next)
	{
		root = creat_node(last_r_pip->value, last_r_pip->next->value);
		if (last_r_pip->next->next)
		{
			new_token = creat_token(tokens, last_r_pip);
			root->left = create_tree(new_token);
			ft_free_token(new_token);
		}
		else if (last_r_pip != tokens)
			root->left = create_tree(tokens);
		tmp = last_r_pip->next->next;
		while (tmp && (tmp->type != PIPE || isnt_red(tmp->type)))
			tmp = tmp->next;
		if (last_r_pip->next->next && tmp && tmp->read == 0)
			root->right = create_tree(tmp);
		else
			root->right = NULL;
	}
	return (root);
}

t_oken	*last_p_r(t_oken *tokens)
{
	t_oken	*current;
	t_oken	*last_redirection_pipe;

	last_redirection_pipe = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == PIPE && current->read == 0)
			last_redirection_pipe = current;
		else if (!g_modes->pipe_count)
		{
			last_redirection_pipe = NULL;
			break ;
		}
		current = current->next;
	}
	if (!last_redirection_pipe)
	{
		current = tokens;
		while (current)
		{
			if (!isnt_red(current->type) && current->read == 0)
				last_redirection_pipe = current;
			current = current->next;
		}
	}
	return (last_redirection_pipe);
}

t_tree	*creat_tree_pipe(t_oken *tokens, t_oken *last_red_p)
{
	t_tree	*root;

	root = NULL;
	g_modes->pipe_count--;
	last_red_p->read = 1;
	g_modes->has_pipe = 1;
	root = creat_node(last_red_p->value, NULL);
	if (last_red_p->next)
		root->right = create_tree(last_red_p->next);
	root->left = create_tree(tokens);
	return (root);
}

t_tree	*creat_node(char *str, char *file_name)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	node->op = strdup(str);
	if (file_name)
		node->file_name = ft_strdup(file_name);
	else
		node->file_name = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_oken	*creat_token(t_oken *tokens, t_oken *last_redirection)
{
	t_oken	*current;
	t_oken	*tmp;
	t_oken	*new;

	current = tokens;
	tmp = NULL;
	new = NULL;
	while (current != last_redirection)
	{
		new = ft_lstnew(strdup(current->value), current->type);
		new->read = current->read;
		ft_lstadd_back(&tmp, new);
		current = current->next;
	}
	current = last_redirection->next->next;
	while (current && current->type != PIPE && isnt_red(current->type))
	{
		new = ft_lstnew(strdup(current->value), current->type);
		new->read = current->read;
		ft_lstadd_back(&tmp, new);
		current = current->next;
	}
	return (tmp);
}
