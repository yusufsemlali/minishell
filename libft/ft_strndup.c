/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:19:38 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/14 19:30:24 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

char *ft_strndup(const char *s, size_t n)
{
    size_t i = 0;
    while (s[i] && i < n)
        i++;
    char *new = ft_calloc(i + 1, sizeof(char));
    i = 0;
    while (*s && n--)
        new[i++] = *s++;
    return (new);
}