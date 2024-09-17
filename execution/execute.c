/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:12:59 by aclakhda          #+#    #+#             */
/*   Updated: 2024/09/17 15:28:04 by aclakhda         ###   ########.fr       */
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

t_tree *creat_node(char *str, char *file_name)
{
	t_tree *node = malloc(sizeof(t_tree));
	node->op = strdup(str);
	node->file_name = file_name ? strdup(file_name) : NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

int	isnt_red(int type)
{
	if (type == OUTPUT || type == INPUT || type == APPEND || type == HEREDOC)
		return 0;
	return 1;
}

t_oken	*creat_token(t_oken *tokens, t_oken *last_redirection)
{
	t_oken *current = tokens;
	t_oken *tmp = NULL;
	t_oken *new = NULL;

	while (current != last_redirection)
	{
		new = ft_lstnew(strdup(current->value), current->type);
		new->read = current->read;
		ft_lstadd_back(&tmp, new);
		current = current->next;
	}
	current = last_redirection->next->next;
	while(current && current->type != PIPE && isnt_red(current->type))
	{
		new = ft_lstnew(strdup(current->value), current->type);
		new->read = current->read;
		ft_lstadd_back(&tmp, new);
		current = current->next;
	}
	return tmp;
}

void	ft_free_token(t_oken *token)
{
	t_oken *tmp;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}

t_tree *create_tree(t_oken *tokens)
{
	t_tree *root = NULL;
	t_oken *current = tokens;
	t_oken *last_redirection_pipe = NULL;
	t_oken *new_token = NULL;
	t_oken *tmp = NULL;

	while (current)
	{
		if ((current->type == PIPE || !isnt_red(current->type)) && current->read == 0)
			last_redirection_pipe = current;
		current = current->next;
	}
	if (last_redirection_pipe && last_redirection_pipe->read == 0 && last_redirection_pipe->type == PIPE)
	{
		last_redirection_pipe->read = 1;
		root = creat_node(last_redirection_pipe->value, NULL);
		root->left = create_tree(tokens);
		if (last_redirection_pipe->next)
			root->right = create_tree(last_redirection_pipe->next);
		return root;
	}
	// current = tokens;
	// while (current)
	// {
	// 	if (!current->read && !isnt_red(current->type))
	// 		last_redirection = current;
	// 	current = current->next;
	// }
	else if (last_redirection_pipe && last_redirection_pipe->read == 0 && !isnt_red(last_redirection_pipe->type))
	{
		last_redirection_pipe->read = 1;
		if (last_redirection_pipe->next)
		{
			root = creat_node(last_redirection_pipe->value, last_redirection_pipe->next->value);
			// if (last_redirection->next->next && (last_redirection->next->next->type == PIPE || !isnt_red(last_redirection->next->next->type)))
			if (last_redirection_pipe != tokens)
				root->left = create_tree(tokens);
			else if (last_redirection_pipe->next->next)
			{
				new_token = creat_token(tokens, last_redirection_pipe);
				root->left = create_tree(new_token);
				ft_free_token(new_token);
			}
			tmp = last_redirection_pipe->next->next;
			while (tmp && (tmp->type != PIPE || isnt_red(tmp->type)))
				tmp = tmp->next;
			if (last_redirection_pipe->next->next && tmp && tmp->read == 0)
				root->right = create_tree(tmp);
			else
				root->right = NULL;
		}
		return root;
	}
	if (tokens)
	{
		root = creat_node(tokens->value, NULL);
		if (tokens->next && (tokens->next->type == ARGS || tokens->next->type == CMD))
			root->right = create_tree(tokens->next);
		return root;
	}
	return NULL;
}

t_herdoc	*set_up(t_tree *tree)
{
	char **new_line;

	new_line = NULL;
	t_herdoc *herdoc = malloc(sizeof(t_herdoc));
	if (!herdoc)
		return NULL;
	herdoc->herdoc = 0;
	herdoc->line = NULL;
	if (tree)
	{
		if (tree->left)
			herdoc = set_up(tree->left);
		else if (tree->right)
			herdoc = set_up(tree->right);
		if (tree->op && !ft_strcmp(tree->op, "<<"))
		{
			new_line = realloc(herdoc->line, (herdoc->herdoc + 1) * sizeof(char *));
			if (new_line == NULL)
			{
				int j = 0;
				while (j < herdoc->herdoc) {
					free(herdoc->line[j]);
					j++;
				}
				free(herdoc->line);
				free(herdoc);
				return NULL;
			}
			herdoc->line = new_line;
			herdoc->line[herdoc->herdoc] = strdup(tree->file_name);
			if (herdoc->line[herdoc->herdoc] == NULL)
			{
				int j = 0;
				while (j < herdoc->herdoc)
				{
					free(herdoc->line[j]);
					j++;
				}
				free(herdoc->line);
				free(herdoc);
				return NULL;
			}
			herdoc->herdoc++;
		}
	}
	return herdoc;
}

void free_herdoc(t_herdoc *herdoc)
{
	if (herdoc)
	{
		int i = 0;
		while (i < herdoc->herdoc)
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
	t_tree	*tmp;

	shell->tree = create_tree(shell->token);
	tmp = shell->tree;
	// printAST(shell->tree, 0, "root");
	shell->herdoc = set_up(tmp);
	if (shell->herdoc)
	{
		shell->fd = open("tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
		ft_exec_rederect_herd(shell, 1);
	}
	executing(shell);
	free_herdoc(shell->herdoc);
	ft_free_tree(shell->tree);
	close(shell->fd);
	unlink("tmp");
	return (0);
}
