#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	char	*args[] = {"/nonexistent", NULL};

	if (execve(args[0], args, NULL) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	return (0);
}
