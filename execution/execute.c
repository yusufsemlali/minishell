/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:12:59 by aclakhda          #+#    #+#             */
/*   Updated: 2024/10/26 15:17:48 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tree	*create_tree(t_oken *tokens)
{
	t_oken	*last_redirection_pipe;

	last_redirection_pipe = NULL;
	last_redirection_pipe = last_p_r(tokens);
	if (last_redirection_pipe && last_redirection_pipe->read == 0 && \
		last_redirection_pipe->type == PIPE)
		return (creat_tree_pipe(tokens, last_redirection_pipe));
	else if (last_redirection_pipe && last_redirection_pipe->read == 0 && \
		!isnt_red(last_redirection_pipe->type))
		return (creat_tree_red(tokens, last_redirection_pipe));
	return (create_simple_tree(tokens));
}

t_herdoc	*set_up(t_oken *token)
{
	t_herdoc	*herdoc;
	t_oken		*current;
	int			j;

	herdoc = NULL;
	current = token;
	j = 0;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			current = current->next;
			if (!herdoc)
				herdoc = s(set(token));
			herdoc->line[j++] = ft_strdup(current->value);
		}
		current = current->next;
	}
	if (herdoc)
		herdoc->herdoc = j;
	return (herdoc);
}


void printAST(t_tree *root, int level, char *side) {
    if (root == NULL) return;
    for (int i = 0; i < level; i++) printf("    ");
    printf("%s (%s)\n", root->op, side);
    printAST(root->left, level + 1, "left");
    printAST(root->right, level + 1, "right");
}

int	execute(t_shell *shell)
{
	t_oken	*tmp;
	// t_tree	*root;

	g_modes->pipe_count = pipe_count(shell->token);
	shell->tree = create_tree(shell->token);
	// root = shell->tree;
	// printAST(root, 0, "root");
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
