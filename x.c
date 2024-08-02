#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_shell {
    int status;
    char *line;
    // other members...
} t_shell;

void parse(t_shell *shell) {
    // Your parsing logic here
}

int execute(t_shell *shell) {
    // Your execution logic here
    return 1; // or 0 to exit
}

void minishell(t_shell *shell) {
    shell->status = 1;
    while (shell->status) {
        shell->line = readline("minishell ✗ ");
        if (shell->line && *shell->line) {
            add_history(shell->line);
            parse(shell);
            shell->status = execute(shell);
            free(shell->line);
        }
    }
}

int main(int ac, char **av, char **nv) {
    (void)av;
    t_shell shell;
    minishell(&shell);
    return 0;
}
