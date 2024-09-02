/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali & aclakhda <ysemlali & aclackd    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:00:56 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/02 23:26:58 by ysemlali &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_oken	*ft_lstnew(char *value, int type)
{
	t_oken	*result;

	result = malloc(sizeof(t_oken));
	if (!result)
		return (NULL);
	result->value = value;
	result->type = type;
	result->next = NULL;
	return (result);
}
