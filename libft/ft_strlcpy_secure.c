/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy_secure.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:29:31 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/11 12:05:10 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy_secure(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	i;

	srcsize = ft_strlen_secure(src);
	i = 0;
	if (srcsize == 0)
		return (0);
	
	if (dstsize != 0)
	{
		//write(1, "test\n", 5);
		while (src[i] != '\0' && i < (dstsize - 1))
		{
		//write(1, "test\n", 5);
			dst[i] = src[i];
			//ft_putchar_fd(src[i], 1);
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}
