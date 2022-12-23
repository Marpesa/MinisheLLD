/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 03:18:17 by gle-mini          #+#    #+#             */
/*   Updated: 2021/12/06 03:18:20 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
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
		return (len + ft_strlen(src));
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
