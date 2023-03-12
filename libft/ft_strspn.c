/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:26:42 by gle-mini          #+#    #+#             */
/*   Updated: 2023/03/12 05:38:26 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strspn(const char *s1, const char *s2)
{
	const char	*p;
	size_t		span;

	span = 0;
	while (*s1)
	{
		p = s2;
		while (*p && *p != *s1)
			p++;
		if (*p == '\0')
			break ;
		s1++;
		span++;
	}
	return (span);
}
