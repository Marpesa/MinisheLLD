/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 04:28:03 by gle-mini          #+#    #+#             */
/*   Updated: 2021/12/06 04:29:42 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*ptrdest;
	char	*ptrsrc;

	if (!dest && !src)
		return (NULL);
	ptrdest = (char *)dest;
	ptrsrc = (char *)src;
	if (dest < src)
		return (ft_memcpy(dest, src, len));
	while (len-- > 0)
		ptrdest[len] = ptrsrc[len];
	return (dest);
}
