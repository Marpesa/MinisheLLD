/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:48:57 by gle-mini          #+#    #+#             */
/*   Updated: 2021/12/03 16:16:07 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atoi2(const char *str, int is_neg, int res, int i)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((res > INT_MAX / 10 || (res == INT_MAX / 10 && str[i] > '7')) \
				&& is_neg > 0)
			return (-1);
		if ((res < INT_MIN / 10 || (res == INT_MIN / 10 && str[i] > '8')) \
				&& is_neg < 0)
			return (0);
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	is_neg;
	int	res;

	is_neg = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_neg *= -1;
		i++;
	}
	res = 0;
	res = ft_atoi2(str, is_neg, res, i);
	return (res * is_neg);
}
