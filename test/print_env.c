#include "../includes/minishell.h"


int	main(int ac, char **av, char **env)
{
	t_shell *shell = ft_calloc(1, sizeof(t_shell));
	init_env(&shell, env);
    int i = 0;
    while (shell->nv[i].key != NULL)
    {
        printf("key= %s    -   value = %s", shell->nv[i].key, shell->nv[i].value);
    }
	return (0);
}