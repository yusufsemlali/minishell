
#include <string.h>
# include <stdio.h>
# include <stdlib.h>

char *strjoin(char *s, char *d)
{
	if (!s || !d )
		return NULL;
	int len = strlen(s);
	int len_d = strlen(d);

	char *res = malloc(len + len_d + 1);
	if (!res)
		return(NULL);
	char *tmp = res;
	while (*s)
	{
		*res = *s;
		res++;
		s++;
	}
	while(*d)
	{
		*res = *d;
		res++;
		*d++;
	}
	*res = 0;
	return(tmp);
}

int main()
{
	char s[] = "hello";
	char d[] = "world";
	printf("%s\n", strjoin(s, d));
}


