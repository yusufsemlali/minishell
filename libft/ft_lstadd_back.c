/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:38:12 by ysemlali          #+#    #+#             */
/*   Updated: 2024/07/06 21:30:12 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_oken **token, t_oken *new)
{
	t_oken	*last;

	if (!token || !new)
		return ;
	if (!*token)
	{
		*token = new;
		return ;
	}
	last = ft_lstlast(*token);
	last->next = new;
}
