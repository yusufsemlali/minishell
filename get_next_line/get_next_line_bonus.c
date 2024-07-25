/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:08:09 by ysemlali          #+#    #+#             */
/*   Updated: 2023/12/07 17:56:33 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ln_exists(char *buf)
{
	size_t	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_remainder(char *line)
{
	char	*result;

	if (!ln_exists(line))
		return (free(line), NULL);
	result = ft_substr(line, ln_index(line) + 1, ft_strlen(line));
	free(line);
	return (result);
}

char	*read_buffer(int fd, char *line)
{
	char	*tmp;
	ssize_t	rd;

	tmp = (char *)malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	tmp[0] = '\0';
	rd = 1;
	while (rd > 0 && !ln_exists(tmp))
	{
		rd = read(fd, tmp, BUFFER_SIZE);
		if (rd < 0)
			return (free(tmp), free(line), NULL);
		tmp[rd] = '\0';
		line = ft_strjoin(line, tmp);
	}
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line[1024];
	char		*output;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = read_buffer(fd, line[fd]);
	if (!line[fd] || !line[fd][0])
		return (free(line[fd]), NULL);
	output = ft_substr(line[fd], 0, ln_index(line[fd]) + 1);
	line[fd] = ft_remainder(line[fd]);
	return (output);
}
