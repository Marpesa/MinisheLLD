/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_secure.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 10:40:51 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/08 17:14:14 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_secure(const char *str)
{
	const char	*s;

	if (str == NULL)
		return (0);
	s = str;
	while (*s)
		s++;
	return (s - str);
}
