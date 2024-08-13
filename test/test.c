#include "includes/minishell.h"
#include <readline/readline.h>

int	main(int argc, char *envp[])
{
	char *input;

	while (1)
	{
		input = readline("shell> ");
		if (input == NULL)
		{
			break ; // Exit on EOF (Ctrl+D)
		}

		if (strncmp(input, "exit", 4) == 0)
		{
			fprintf(stderr, "exit\n");
			free(input);
			exit(0);
		}

		if (strncmp(input, "ls", 2) == 0)
		{
			pid_t pid = fork();
			if (pid == -1)
			{
				perror("fork");
				free(input);
				exit(1);
			}
			else if (pid == 0)
			{
				char *args[] = {"/bin/ls", NULL};
				execve("/bin/ls", args, envp);
				perror("execve");
				exit(1);
			}
			else
			{
				int status;
				waitpid(pid, &status, 0);
			}
		}

		free(input);
	}

	return (0);
}