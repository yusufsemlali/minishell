# include "../includes/minishell.h"

void error(void *ptr)
{
    if (ptr == NULL)
    {
        ft_putendl_fd("exit", 0);
        rl_clear_history();
        free(ptr);
        exit(g_modes->exit_mode);
    }
}