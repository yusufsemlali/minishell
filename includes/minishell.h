#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define SIGSPECIAL 1337

// error type def
# define ERR_SYNTAX 1
# define ERR_CMD 2 // command not found
# define ERR_FILE 3 // no such find or directory
# define ERR_PERM 4 // permission denied
# define ERR_FORK 5 // fork failed
# define ERR_EXEC 6 // execve failed

# define BUFFER_SIZE 1024
# define CMD_MAX_LENGTH 256

typedef struct s_mode
{
	int		input_mode;
	int		exit_mode;
	int		output_mode;
}			t_mode;
extern t_mode *modes;

typedef struct s_tree
{
	char			*op;
    struct s_tree	*left;
    struct s_tree	*right;
}					t_tree;

typedef struct s_shell
{
	char	*line;
	char	**nv;
    char    **av;
	int		status;
	int		fd;
	int		err;
	t_tree	*tree;
}			t_shell;

typedef struct s_var
{
	int		i;
	int		has_pipe;
	int		has_rederect;
}			t_var;


// -- parsing -- //
void		handle_signals(int sig);
void		parse(t_shell *shell);
//---execution---//
int	execute(t_shell *shell);
int	ft_strcmp(char *s1, char *s2);
int	ft_size(char **av);
void	ft_found(t_shell *shell, t_var *var, int start, int end);

#endif
