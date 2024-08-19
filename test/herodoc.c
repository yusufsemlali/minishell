#include "../includes/minishell.h"



void simulate_heredoc(const char *end_marker) {
    char *input;
    printf("Enter heredoc content (end with '%s'):\n", end_marker);
    while (1) {
        input = readline("> ");
        if (strcmp(input, end_marker) == 0) {
            free(input);
            break;
        }
        printf("%s\n", input); // Simulate processing the input
        free(input);
    }
}

int main(int ac, char **av) {
    (void)ac;
    simulate_heredoc(av[1]);
    return 0;
}