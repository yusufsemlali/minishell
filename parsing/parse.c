/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:44:55 by ysemlali          #+#    #+#             */
/*   Updated: 2024/09/25 16:45:52 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	closed_checker(t_shell *shell, char *s)
{
	int	one_open;
	int	two_open;

	one_open = 0;
	two_open = 0;
	while (*s)
	{
		if (*s == '\'' && two_open % 2 == 0)
			one_open++;
		else if (*s == '\"' && one_open % 2 == 0)
			two_open++;
		s++;
	}
	if (one_open % 2 != 0)
		ft_putendl_fd("minishell: syntax error near unexpected token `'", 2);
	if (two_open % 2 != 0)
		ft_putendl_fd("minishell: syntax error near unexpected token `\"'", 2);
	if (one_open % 2 != 0 || two_open % 2 != 0)
		return (g_modes->exit_mode = 127, shell->err = ERR_SYNTAX, 0);
	return (1);
}

char	*get_prompt(t_shell *shell)
{
	char	prompt[BUFFER_SIZE];
	char	*pwd;
	char	*home;

	pwd = get_env(shell->nv, "PWD");
	home = get_env(shell->nv, "HOME");
	ft_bzero(prompt, BUFFER_SIZE);
	ft_strlcat(prompt, COLOR_GREEN, BUFFER_SIZE);
	ft_strlcat(prompt, get_env(shell->nv, "USER"), BUFFER_SIZE);
	ft_strlcat(prompt, "@", BUFFER_SIZE);
	ft_strlcat(prompt, get_env(shell->nv, "USERNAME"), BUFFER_SIZE);
	ft_strlcat(prompt, COLOR_RED, BUFFER_SIZE);
	ft_strlcat(prompt, ":", BUFFER_SIZE);
	if (ft_strncmp(pwd, home, ft_strlen(home)) == 0)
	{
		ft_strlcat(prompt, "~", BUFFER_SIZE);
		ft_strlcat(prompt, pwd + ft_strlen(home), BUFFER_SIZE);
	}
	else
		ft_strlcat(prompt, pwd, BUFFER_SIZE);
	ft_strlcat(prompt, COLOR_RESET, BUFFER_SIZE);
	ft_strlcat(prompt, "$ ", BUFFER_SIZE);
	return (ft_strdup(prompt));
}

/*shell->s= readline("\033[1;36mminishell \033[1;93m✗ \033[0m");*/
void	parse(t_shell *shell)
{
	char	*prompt;

	prompt = get_prompt(shell);
	shell->s = readline(prompt);
	free(prompt);
	if (error(shell->s, shell))
		return ;
	add_history(shell->s);
	if (closed_checker(shell, shell->s))
	{
		spacing(shell);
		expand(shell);
		lexer(shell);
		squish(shell);
    for (int i=0;shell->av[i];i++)
      printf("[%s] ",shell->av[i]);
    printf("\n");
		token_lst(shell);
		valid(shell);
	}
}
