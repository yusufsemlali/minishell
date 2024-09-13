#include "../includes/minishell.h"

void	free_av(char ***av)
{
	int	i;

	i = 0;
	if (*av != NULL)
	{
		while ((*av)[i])
		{
			free((*av)[i]);
			i++;
		}
	}
	free(*av);
	*av = NULL;
}

void	free_nv(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	free(tmp);
	*env = NULL;
}

int	free_all(t_shell *shell)
{
	free_av(&(shell->av));
	free_nv(&(shell->nv));
	free(shell->s);
	free(shell);
	free(g_modes);
	return (g_modes->exit_mode);
}

