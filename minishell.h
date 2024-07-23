#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define SIGSPECIAL 1337

typedef struct s_mode
{
	int		input_mode;
	int		exit_mode;
	int		output_mode;
}			t_mode;
extern t_mode *modes;

typedef struct s_shell
{
	char	*line;
	char	**nv;
    char    **av;
	int		status;
}			t_shell;

// -- parsing -- //
void		handle_signals(int sig);

#endif
