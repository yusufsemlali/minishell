/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:33:42 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/18 10:33:42 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(char *s, int replace, int c)
{
	char	*tmp;

	tmp = s;
	while (*tmp)
	{
		if (*tmp == replace)
			*tmp = c;
		tmp++;
	}
	return (s);
}
