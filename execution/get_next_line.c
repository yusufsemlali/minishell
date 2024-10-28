/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:44:33 by aclakhda          #+#    #+#             */
/*   Updated: 2024/10/26 15:49:12 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *ft_strjoin__(char *s, char c)
{
    char *new;
    int i = 0;

    while (s && s[i])
        i++;
    if (!(new = malloc(i + 2)))
        return (NULL);
    i = 0;
    while (s && s[i])
    {
        new[i] = s[i];
        i++;
    }
    new[i] = c;
    new[i + 1] = '\0';
    free(s);
    return (new);
}

char	*get_next_line(int fd)
{
    static char buf[1];
    static int pos = 0, bytes = 0;
    char *line = NULL;
    char c;

    if (fd < 0)
        return (NULL);
    while (1)
    {
        if (pos >= bytes)
        {
            pos = 0;
            if ((bytes = read(fd, buf, 1)) <= 0)
                break;
        }
        c = buf[pos++];
        if (!(line = ft_strjoin__(line, c)))
            return (NULL);
        if (c == '\n')
            break;
    }
    return (line);
}
