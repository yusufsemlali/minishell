#include <signal.h>
#include <unistd.h>

void	signal_interrupt(int sig)
{
	(void)sig;
	printf("Interrupted\n");
}
void	signal_quit(int sig)
{
	(void)sig;
	printf("Quit\n");
}

int	main(void)
{
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, signal_quit);
	while (1)
	{
		write(1, "Hello\n", 6);
		sleep(1);
	}
	return (0);
}
