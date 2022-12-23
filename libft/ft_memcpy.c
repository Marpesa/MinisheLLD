/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 02:24:58 by gle-mini          #+#    #+#             */
/*   Updated: 2021/12/06 02:25:14 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptrdest;

	if (!dest && !src)
		return (NULL);
	ptrdest = (unsigned char *)dest;
	while (n--)
		*ptrdest++ = *(unsigned char *)src++;
	return (dest);
}
