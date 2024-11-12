# include "../includes/minishell.h"


char 	*quotes(char *s)
{
  char token[BUFFER_SML];
	int		i;
	int		x;

	i = 0;
	x = 0;
  ft_bzero(token, BUFFER_SML);
  if (s == NULL)
    return(NULL);
	while (s[i])
	{
		while ((s[i] == '\"' || s[i] == '\'') && !inquotes(s, i, 0))
			x = s[i++];
		if (s[i] == '\0' || (ft_isspace(s[i]) && !inquotes(s, i, 0)))
			break ;
		if (s[i] != '\0' && x != s[i])
			ft_strlcat(token, s + i, ft_strlen(token) + 2);
		i++;
	}
  free(s);
  return(ft_strdup(token));
}
