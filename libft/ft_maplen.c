#include "libft.h"

size_t	ft_maplen(char **map)
{
	size_t	i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i); 
}

