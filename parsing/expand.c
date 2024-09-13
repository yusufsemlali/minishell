#include "../includes/minishell.h"

int	valid_expansion(char *s)
{
	while (*s)
	{
		if (*s == '$' && (*(s + 1) == ' ' || *(s + 1) == '\0'))
			return (1);
		if (*s == -'$' && *(s + 1) == '$')
			return (1);
		s++;
	}
}

void	expand(t_shell *shell)
{
	t_oken	*token;

	token = shell->token;
	while (token)
	{
		if (token->type == ARG && !valid_expansion(token->value))
			token->value = ft_strdup(expand_var(token->value, shell->env));
		token = token->next;
	}
}
