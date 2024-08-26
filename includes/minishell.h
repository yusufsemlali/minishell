/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:41:57 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/26 11:38:15 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define ARGS 0    // arguments
# define PIPE 1    // "|"
# define CMD 2     // command
# define OUTPUT 3  // ">"
# define INPUT 4   // "<"
# define APPEND 5  // ">>"
# define HEREDOC 6 // "<<"
# define AND 7     // "&"
# define OR 8      // "||"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define EXIT_SUCCESS 0
# define EXIT_ERROR 2
# define SIGSPECIAL 1337

// error type def
# define CTRL_C 130        // ctrl c
# define MISS_USAGE 1      // wrong usage of command
# define ERR_EXECUTE 126   // command invoked cannot execute
# define ERR_SIGFAULT 139  // segmentation fault
# define CMD_NOT_FOUND 127 // comand not found

// error custom
# define ERR_SYNTAX 258 // syntax error

# define BUFFER_SIZE 1024
# define CMD_MAX_LENGTH 1024

typedef struct s_mode
{
	int				input_mode;
	int				exit_mode;
	int				output_mode;
}					t_mode;

typedef struct s_tree
{
	char			*op;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}					t_oken;

typedef struct s_shell
{
	char			*s;
	t_env			*nv;
	char			**av;
	int				status;
	int				fd;
	int				err;
	int				begin;
	t_tree			*tree;
	t_oken			*token;
	char			**env;
}					t_shell;

typedef struct s_var
{
	int				i;
	int				has_pipe;
	int				has_rederect;
	char			*av[CMD_MAX_LENGTH];
	char			*cmd_path;
	int 			value_len;
	int 			key_len;
	char			**env;
	int				size;
	pid_t 			pid;
}					t_var;

// -- init -- //
void				init(t_shell **shell, int ac, char **av, char **nv);
// -- parsing -- //
void				handle_signals(int sig);
void				parse(t_shell *shell);
void				tokenize(t_shell *shell);
char				*spacing(char *s);
char				*validate(char *s);
int					inquotes(char *s, int i, int x);
int					metachar(char c, char prev);
//---execution---//
int					execute(t_shell *shell);
int					ft_size(char **av);
void				ft_found(t_shell *shell, t_var *var, int start, int end);
void				ft_free_tree(t_tree *root);
void				executing(t_shell *shell);
int					is_rederaction(char *c);
char				*ft_strcat(char *dest, char *src);
char				*ft_strcpy(char *dest, char *src);
char				*creating_cmd_path(int len, char **path_split, int i,
						char *av);
void				s_free(char **av);
int					check_cmd(t_shell *shell);
int					is_rederaction(char *c);
void				cmd_maker(t_shell *shell, char **av);
char				**creat_env(t_env *nv);
void				lazy_free(char **env, int i);
int					env_size(t_env *nv);
void				ft_exec_rederect(t_shell *shell);
// -- built in -- //
void				echo(t_shell *shell);
void				cd(t_shell *shell);
void				env(t_shell *shell);
void				pwd(t_shell *shell);
void				export(t_shell *shell);
void				unset(t_shell *shell);

extern t_mode		*g_modes;
#endif
