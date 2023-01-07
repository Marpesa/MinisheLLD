/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 03:42:53 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/07 17:23:13 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;
	int	j;

	j  = 0;
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
