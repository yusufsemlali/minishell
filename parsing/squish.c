/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 06:18:38 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/20 06:18:38 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	squish(t_shell *shell)
{
	char	buf[BUFFER_BIG];
	char	**av;
	char	**tmp;
	size_t	index;

	tmp = shell->av;
	index = 0;
	ft_bzero(buf, BUFFER_BIG);
	av = ft_calloc(len_av(shell->av) + 1, sizeof(char *));
	while (*shell->av)
	{
		while (*shell->av && !ft_strchr(*shell->av, - '#'))
		{
			ft_strlcat(buf, *shell->av, BUFFER_BIG);
			free(*shell->av++);
		}
		if (*shell->av && ft_strchr(*shell->av, - '#'))
			free(*shell->av++);
		av[index++] = ft_strdup(buf);
		ft_bzero(buf, BUFFER_BIG);
	}
	av[index] = NULL;
	free(tmp);
	shell->av = av;
}
