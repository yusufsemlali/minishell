# include <stdlib.h>

int main(void)
{
	void *ptr = malloc(sizeof(char) * 1);
	void *ptr1 = malloc(sizeof(char) * 1);
	void *ptr11 = malloc(sizeof(char) * 1);
	void *ptr111 = malloc(sizeof(char) * 1);
	void *ptr1111 = malloc(sizeof(char) * 1);
	void *ptr11111 = malloc(sizeof(char) * 1);
	free(ptr);
	free(ptr1);
	free(ptr11);
	free(ptr111);
	free(ptr1111);
	free(ptr11111);
	return(100);
}
