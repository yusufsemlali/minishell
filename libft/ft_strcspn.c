/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:14:08 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/20 07:14:09 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s, const char *d)
{
	size_t		count;
	const char	*dlim = d;

	count = 0;
	while (*s)
	{
		d = dlim;
		while (*d)
		{
			if (*s == *d)
				return (count);
			d++;
		}
		s++;
		count++;
	}
	return (count);
}
