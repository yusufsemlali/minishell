/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:29:56 by aclakhda          #+#    #+#             */
/*   Updated: 2024/08/14 11:35:27 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_quote(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[0] != '\"' && str[0] != '\'')
		return ;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	// printf("str: %s\n", str);
}


void	echo(t_shell *shell)
{
	char	*av[CMD_MAX_LENGTH];
	int		i;

	cmd_maker(shell, av);
	remove_quote(av[1]);
	if (ft_strcmp(av[1], "-n") == 0)
	{
		i = 2;
		while (av[i])
		{
			ft_putstr_fd(av[i], 1);
			if (av[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	else
	{
		i = 1;
		while (av[i])
		{
			remove_quote(av[i]);
			printf("%s", av[i]);
			if (av[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
}
