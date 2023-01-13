#include "libft.h"

size_t	ft_strlcat_secure(char *dst, const char *src, size_t size)
{
	char		*ptrdst;
	const char	*ptrsrc;
	size_t		len;
	size_t		i;

	ptrdst = dst;
	ptrsrc = src;
	i = size;
	while (i-- && *ptrdst)
		ptrdst++;
	len = ptrdst - dst;
	i = size - len;
	if (i == 0)
		return (len + ft_strlen_secure(src));
	while (*ptrsrc)
	{
		if (i > 1)
		{
			*ptrdst++ = *ptrsrc;
			i--;
		}
		ptrsrc++;
	}
	*ptrdst = 0;
	return (len + (ptrsrc - src));
}
