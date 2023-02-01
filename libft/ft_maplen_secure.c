#include "libft.h"

size_t	ft_maplen_secure(char **map)
{
	size_t	i;

	i = 0;
	if (map == NULL)
		return (0);
	while (map[i] != NULL)
		i++;
	return (i); 
}

