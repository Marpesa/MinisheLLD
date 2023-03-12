/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:19:11 by gle-mini          #+#    #+#             */
/*   Updated: 2023/03/12 05:43:43 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtok_r(char *s, const char *delim, char **save_ptr)
{
	char	*end;

	if (s == NULL)
		s = *save_ptr;
	if (*s == '\0')
	{
		*save_ptr = s;
		return (NULL);
	}
	s += ft_strspn (s, delim);
	if (*s == '\0')
	{
		*save_ptr = s;
		return (NULL);
	}
	end = s + ft_strcspn (s, delim);
	if (*end == '\0')
	{
		*save_ptr = end;
		return (s);
	}
	*end = '\0';
	*save_ptr = end + 1;
	return (s);
}
