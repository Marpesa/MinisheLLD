/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:49:05 by gle-mini          #+#    #+#             */
/*   Updated: 2021/12/03 17:54:27 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	size;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < len)
		size = ft_strlen(s);
	else
		size = len;
	str = (char *)malloc(sizeof(*s) * (size + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (i >= start && j < len)
			str[j++] = s[i];
	}
	str[j] = 0;
	return (str);
}
