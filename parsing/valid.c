/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:05:11 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/18 18:18:41y ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*validate(char *s)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (s[i] != '\0')
	{
		in_quote = inquotes(s, i, in_quote);
		if (!in_quote)
		{
			if (s[i + 1] != '\0')
			{
				if ((s[i] == '<' && s[i + 1] == '>') || (s[i] == '>' && s[i
						+ 1] == '<'))
					return (NULL);
				if (s[i] == '|' || s[i] == '&' || s[i] == ';')
				{
					if (s[i + 1] != s[i])
						return (NULL);
				}
			}
		}
		i++;
	}
	return (s);
}
