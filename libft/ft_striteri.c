/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 03:42:53 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/13 04:25:56 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;
	int	j;

	j = 0;
	if (s != NULL && f != NULL)
	{
		i = ft_strlen(s);
		while (j < i)
		{
			(f)(j, s);
			s++;
			j++;
		}
	}
}
