/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:08:11 by ysemlali          #+#    #+#             */
/*   Updated: 2023/12/07 21:05:15 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(char *str);
size_t	ln_exists(char *buf);
size_t	ln_index(char *buf);
char	*ft_strjoin(char *line, char *buf);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif