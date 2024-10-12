/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:00:56 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/10 23:21:22 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_oken	*ft_lstnew(char *value, int type, int index)
{
	t_oken	*result;

	result = malloc(sizeof(t_oken));
	if (!result)
		return (NULL);
	result->value = value;
	result->type = type;
	result->read = 0;
  result->index = index;
	result->next = NULL;
	return (result);
}
