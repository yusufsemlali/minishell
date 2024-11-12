/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:31:56 by ysemlali          #+#    #+#             */
/*   Updated: 2024/11/12 14:31:56 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	t_type(char *s, t_oken *prev)
{
	if (ft_strcmp(s, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(s, "<") == 0)
		return (INPUT);
	else if (ft_strcmp(s, ">") == 0)
		return (OUTPUT);
	else if (ft_strcmp(s, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(s, "<<") == 0)
		return (HEREDOC);
	else if (prev == NULL )
  {
    if(prev->type == PIPE)
     return (CMD);
  }
	return (ARGS);
}

void	token(t_shell *shell)
{
	int	i;

	i = 0;
	/*shell->token = ft_lnew(shell->av[i], 0 , i, NULL);*/
	while (shell->av[i])
	{
		ft_lstadd_back(&shell->token, ft_lnew(shell->av[i], 0, i,
				ft_lstlast(shell->token)));
		i++;
	}
}

void	type(t_shell *shell)
{
	t_oken	*token;

	token = shell->token;
	while (token)
	{
		token->type = t_type(token->value, token->prev);
		token = token->next;
	}
}

int	get_variable_size(char *s, t_env *nv)
{
	int		len;
	char	env[BUFFER_SML];

	len = 0;
	while (*s)
	{
		if (ft_strncmp(s, "$?", 2) == 0)
			len += get_num_len(g_modes.exit_mode);
		if (ft_strncmp(s, "$$", 2) == 0)
			len += 2;
		if (ft_strncmp(s, "$#", 2) == 0 || ft_strncmp(s, "\"$\"", 3) == 0)
			len++;
		if (ft_strncmp(s, "$0", 2) == 0)
			len += ft_strlen("minishell");
		if (*s == '$' && (ft_isspace(*(s + 1)) || *(s + 1) == '\0'))
			len++;
		if (*s == '$' && !ft_isspace(*(s + 1)) && *(s + 1) != '/')
		{
			ft_strlcpy(env, s + 1, ft_strcspn(s + 1, "$ =\'\"\t\f\v\r/") + 1);
			len += (ft_strlen(get_env(nv, env)));
		}
		len++;
		s++;
	}
	return (len);
}


int	get_variables(char *s, char *buf, t_env *nv)
{
	char	env[1024];
	char	*tmp;

	if (ft_strncmp(s, "$?", 2) == 0)
		return (ft_strlcat(buf, (tmp = ft_itoa(g_modes.exit_mode)), BUFFER_SML),
			free(tmp), 2);
	if (ft_strncmp(s, "$$", 2) == 0)
		return (ft_strlcat(buf, "$$", BUFFER_SML), 2);
	if (ft_strncmp(s, "$#", 2) == 0)
		return (ft_strlcat(buf, "0", BUFFER_SML), 2);
	if (ft_strncmp(s, "\"$\"", 3) == 0)
		return (ft_strlcat(buf, "$", BUFFER_SML), 3);
	if (ft_strncmp(s, "$0", 2) == 0)
		return (ft_strlcat(buf, "minishell", BUFFER_SML), 2);
	if (*s == '$' && (ft_isspace(*(s + 1)) || *(s + 1) == '\0'))
		return (ft_strlcat(buf, "$", BUFFER_SML), 1);
	if (*s == '$' && !ft_isspace(*(s + 1)) && *(s + 1) != '/')
	{
		ft_strlcpy(env, s + 1, ft_strcspn(s + 1, "$ =\'\"\t\f\v\r/") + 1);
		ft_strlcat(buf, get_env(nv, env), BUFFER_SML);
		return (ft_strlen(env) + 1);
	}
	return (ft_strlcat(buf, s, ft_strlen(buf) + 2), 1);
}


char	*expanding(char *s, t_oken *prev, t_env *nv)
{
	char	*buf;

	if (prev == NULL || prev->type == HEREDOC || prev->type == APPEND
		|| prev->type == OUTPUT || prev->type == INPUT)
		return (NULL);
	buf = ft_calloc(get_variable_size(s, nv) + 2, 1);
  if (buf)
  {
	while (*s)
		s += get_variables(s, buf, nv);
  }
	return (buf);
}

void	expand(t_shell *shell)
{
	t_oken	*token;
	char	*new;

	token = shell->token;
	while (token)
	{
		new = expanding(token->value, token->prev, shell->nv);
		if (new)
		{
			free(token->value);
			token->value = ft_strreplace(new, -'$', '$');
		}
		token = token->next;
	}
}
