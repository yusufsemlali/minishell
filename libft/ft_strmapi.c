/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:25:57 by ysemlali          #+#    #+#             */
/*   Updated: 2024/07/06 21:14:56 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
  char *d = (char *)s;

	if (!s || !f)
		return (0);
	result = ft_calloc(ft_strlen(s) + 1, 1);
	while (*s)
	{
		*result = f(s -d, *s);
    s++;
    result++;
	}
	return (result);
}


char toggle(unsigned int i , char c)
{
  (void)i;
  return(ft_toupper(c));
}

int main()
{
  printf("%s \n", ft_strmapi("hello word", toggle));
}
