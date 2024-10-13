/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shams </var/spool/mail/shams>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:03:55 by shams             #+#    #+#             */
/*   Updated: 2024/10/09 19:03:55 by shams            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	metachar(char c)
{
	return (ft_strchr("|<>", c) != NULL);
}

char	*get_env(t_env *nv, char *key)
{
	t_env	*tmp;

	tmp = nv;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

size_t	len_av(char **av)
{
	size_t	len;

	len = 0;
	while (*av)
	{
		len++;
		if (ft_strchr(*av, - '#'))
			len--;
		av++;
	}
	return (len);
}

int	getcount(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (ft_isspace(*s))
		{
			count++;
			while (*s && ft_isspace(*s))
				s++;
		}
		if (*s)
		{
			count++;
			while (*s && !ft_isspace(*s))
				s++;
		}
	}
	return (count);
}
