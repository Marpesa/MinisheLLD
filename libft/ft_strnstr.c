/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 04:06:54 by gle-mini          #+#    #+#             */
/*   Updated: 2021/12/06 04:09:23 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;

	if (!*little)
		return ((char *)big);
	while (*big && len)
	{
		if (*big == *little)
		{
			i = 0;
			while ((len - i) && big[i] && little[i] && big[i] == little[i])
				i++;
			if (!little[i])
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (NULL);
}
