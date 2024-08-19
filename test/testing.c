# include <stdio.h>


// char **parsing(char *s)
// {
// 	char **line = 

// }

int main(int ac, char **av)
{
	char **line = parsing(av[1]);
	int i = 0;
	while (line[i] != NULL)
	{
		printf("[%s]\n", line[i]);
		i++;
	}
}
