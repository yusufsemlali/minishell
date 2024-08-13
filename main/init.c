/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:56:29 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/13 14:38:47 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init(t_shell **shell, int ac, char **av, char **nv)
{
	(void)ac;
	(void)av;
	*shell = ft_calloc(1, sizeof(t_shell));
	(*shell)->nv = nv;
	(*shell)->status = 0;
	(*shell)->nv = nv;
	g_modes = ft_calloc(1, sizeof(t_mode));
}
