# include "../includes/minishell.h"



void token(t_shell *shell)
{
  int i = 0;
  shell->av = ft_split(shell->s, ' ' );

  /*shell->token = ft_lnew(shell->av[i], 0 , i, NULL);*/
  while (shell->av[i])
  {
		ft_lstadd_back(&shell->token, ft_lnew(shell->av[i], 0, i, ft_lstlast(shell->token)));
    i++;
  }
}




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
  else if(prev == NULL || prev->type == PIPE)
    return(CMD);
  else 
    return(ARGS);
}



void type(t_shell *shell)
{
  t_oken *token = shell->token;
  while (token)
  {
    token->type = t_type(token->value, token->prev);
    token = token->next;
  }
}
