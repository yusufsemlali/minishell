/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_u2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 00:51:56 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/27 00:52:55 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_oken	*find_last_pipe(t_oken *tokens)
{
	t_oken	*current;
	t_oken	*last_pipe;

	last_pipe = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == PIPE && current->read == 0)
			last_pipe = current;
		else if (!g_modes.pipe_count)
			return (NULL);
		current = current->next;
	}
	return (last_pipe);
}

t_oken	*find_last_redirection(t_oken *tokens)
{
	t_oken	*current;
	t_oken	*last_redirection;

	last_redirection = NULL;
	current = tokens;
	while (current)
	{
		if (!isnt_red(current->type) && current->read == 0)
			last_redirection = current;
		current = current->next;
	}
	return (last_redirection);
}

t_oken	*last_p_r(t_oken *tokens)
{
	t_oken	*last_redirection_pipe;

	last_redirection_pipe = find_last_pipe(tokens);
	if (!last_redirection_pipe)
		last_redirection_pipe = find_last_redirection(tokens);
	return (last_redirection_pipe);
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
		new = ft_lstnew(ft_strdup(current->value), current->type, 0);
		new->read = current->read;
		ft_lstadd_back(&tmp, new);
		current = current->next;
	}
	current = last_redirection->next->next;
	while (current && current->type != PIPE && isnt_red(current->type))
	{
		new = ft_lstnew(ft_strdup(current->value), current->type, 0);
		new->read = current->read;
		ft_lstadd_back(&tmp, new);
		current = current->next;
	}
	return (tmp);
}

t_tree	*creat_node(char *str, char *file_name)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	node->op = ft_strdup(str);
	if (file_name)
		node->file_name = ft_strdup(file_name);
	else
		node->file_name = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
