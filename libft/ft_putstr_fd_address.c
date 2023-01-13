/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_address.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:06:16 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/13 03:07:45 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_putstr_fd_address(char *start, char *end, int fd)
{
	if (!start)
		return ;
	if (!end)
		return ;
	if (start > end)
		return ;
	write(fd, start, end - start);
	write(fd, "\n", 1);
}
