#include "libft.h"

char	*ft_strpbrk(const char *s, const char *accept)
{
	const char	*a;

	while (*s)
	{
		a = accept;
		while (*a)
		{
			if (*s == *a)
				return ((char *)s);
			a++;
		}
		s++;
	}
	return (NULL);
}
