/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:12:59 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/23 17:23:59 by aclakhda         ###   ########.fr       */
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

int	isnt_red(int type)
{
	if (type == OUTPUT || \
		type == INPUT || type == APPEND || type == HEREDOC)
		return (0);
	return (1);
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

void	ft_free_token(t_oken *token)
{
	while (token)
	{
		free(token->value);
		free(token);
		token = token->next;
	}
}

t_tree	*create_tree(t_oken *tokens)
{
	t_tree	*root;
	t_oken	*current;
	t_oken	*last_redirection_pipe;
	t_oken	*new_token;
	t_oken	*tmp;

	root = NULL;
	current = tokens;
	last_redirection_pipe = NULL;
	new_token = NULL;
	tmp = NULL;
	while (current)
	{
		if ((current->type == PIPE || !isnt_red(current->type)) && \
			current->read == 0)
			last_redirection_pipe = current;
		current = current->next;
	}
	if (last_redirection_pipe && last_redirection_pipe->read == 0 && \
		last_redirection_pipe->type == PIPE)
	{
		last_redirection_pipe->read = 1;
		g_modes->has_pipe = 1;
		root = creat_node(last_redirection_pipe->value, NULL);
		root->left = create_tree(tokens);
		if (last_redirection_pipe->next)
			root->right = create_tree(last_redirection_pipe->next);
		return (root);
	}
	else if (last_redirection_pipe && last_redirection_pipe->read == 0 && \
		!isnt_red(last_redirection_pipe->type))
	{
		last_redirection_pipe->read = 1;
		if (last_redirection_pipe->next)
		{
			root = creat_node(last_redirection_pipe->value, last_redirection_pipe->next->value);
			if (last_redirection_pipe->next->next)
			{
				new_token = creat_token(tokens, last_redirection_pipe);
				root->left = create_tree(new_token);
				ft_free_token(new_token);
			}
			else if (last_redirection_pipe != tokens)
				root->left = create_tree(tokens);
			tmp = last_redirection_pipe->next->next;
			while (tmp && (tmp->type != PIPE || isnt_red(tmp->type)))
				tmp = tmp->next;
			if (last_redirection_pipe->next->next && tmp && tmp->read == 0)
				root->right = create_tree(tmp);
			else
				root->right = NULL;
		}
		return (root);
	}
	if (tokens)
	{
		root = creat_node(tokens->value, NULL);
		if (tokens->next && (tokens->next->type == ARGS || \
			tokens->next->type == CMD))
			root->right = create_tree(tokens->next);
		return (root);
	}
	return (root);
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

t_herdoc	*set_up(t_oken *token)
{
	t_herdoc	*herdoc;
	t_oken		*current;
	int			i;
	int			j;

	herdoc = NULL;
	current = token;
	j = 0;
	i = set(token);
	while (current && i)
	{
		if (current->type == HEREDOC)
		{
			current = current->next;
			if (!herdoc)
			{
				herdoc = malloc(sizeof(t_herdoc));
				herdoc->line = malloc(sizeof(char *) * (i + 1));
				herdoc->line[j] = ft_strdup(current->value);
				herdoc->line[i] = NULL;
			}
			else
				herdoc->line[j] = ft_strdup(current->value);
			j++;
		}
		current = current->next;
	}
	if (herdoc)
		herdoc->herdoc = i;
	return (herdoc);
}

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
	}
}

int	execute(t_shell *shell)
{
	t_oken	*tmp;

	shell->tree = create_tree(shell->token);
	// printAST(shell->tree, 0, "root");
	tmp = shell->token;
	shell->herdoc = set_up(tmp);
	if (shell->herdoc != NULL)
	{
		shell->fd = open("tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
		ft_exec_rederect_herd(shell, 1);
	}
	if (g_modes->herdoc_mode != CTRL_C)
		executing(shell);
	free_herdoc(shell->herdoc);
  if (shell->fd != 0)
    close(shell->fd);
	ft_free_tree(shell->tree);
	if (shell->fd)
		close(shell->fd);
	unlink("tmp");
	return (0);
}
