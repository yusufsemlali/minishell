/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:56:29 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/02 21:58:18 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"


void init(t_shell *shell, char **nv)
{
    shell = ft_calloc(1, sizeof(t_shell));
	modes = ft_calloc(1, sizeof(t_mode));
	modes->input_mode = -1;
	shell->nv = nv;
	shell->status = 0;
}