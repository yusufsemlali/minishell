/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:59:07 by ysemlali          #+#    #+#             */
/*   Updated: 2024/11/11 19:03:28 by ysemlali         ###   ########.fr       */
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
		return (g_modes.exit_mode = 127, shell->err = ERR_SYNTAX, 0);
	return (1);
}

char	*prompt(t_shell *shell, char *pwd, char *home)
{
	static char	prompt[BUFFER_SML];

	pwd = get_env(shell->nv, pwd);
	home = getenv(home);
	ft_bzero(prompt, BUFFER_SML);
	ft_strlcat(prompt, COLOR_GREEN, BUFFER_SML);
	ft_strlcat(prompt, getenv("USER"), BUFFER_SML);
	ft_strlcat(prompt, "@", BUFFER_SML);
	ft_strlcat(prompt, getenv("USERNAME"), BUFFER_SML);
	ft_strlcat(prompt, COLOR_RED, BUFFER_SML);
	ft_strlcat(prompt, ":", BUFFER_SML);
	if (pwd && home && !ft_strncmp(pwd, home, ft_strlen(home)))
	{
		ft_strlcat(prompt, "~", BUFFER_SML);
		ft_strlcat(prompt, pwd + ft_strlen(home), BUFFER_SML);
	}
	else
		ft_strlcat(prompt, pwd, BUFFER_SML);
	ft_strlcat(prompt, COLOR_RESET, BUFFER_SML);
	ft_strlcat(prompt, "$ ", BUFFER_SML);
	return (prompt);
}

void	parse(t_shell *shell)
{
	shell->s = readline(prompt(shell, "PWD", "HOME"));
	if (error(shell->s, shell))
		return ;
	add_history(shell->s);
	shell->len = ft_strlen(shell->s);
	if (closed_checker(shell, shell->s))
	{
		spacing(shell);
    lexer(shell);
    expand(shell);
		valid(shell);
	}
}


/*token(shell);*/
    /*type(shell);*/
    /*for(t_oken *t = shell->token; t != NULL; t = t->next)*/
    /*  printf("%s %d\n", t->value, t->type);*/
