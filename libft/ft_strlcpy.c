/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 07:07:12 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/06 16:57:58 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	i;

	srcsize = ft_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}

/*
size_t ft_strlcpy(char *dst, const char *src, size_t size)
{
 
    size_t i;
	i = 0;
    while (i < size && src[i] != '\0')
	{
        dst[i] = src[i];
		i++;
    }
    if (i <= size) {
        dst[i] = '\0';
    } else if (size > 0) {
        dst[size - 1] = '\0';
    }
    return i;
}*/

