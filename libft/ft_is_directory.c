/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:02:49 by gle-mini          #+#    #+#             */
/*   Updated: 2023/03/14 20:04:55 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_bool	ft_is_directory(const char *str)
{
	struct stat	statbuf;

	if (access(str, R_OK | X_OK | F_OK) == 0)
	{
		if (stat(str, &statbuf) == 0)
			return (S_ISDIR(statbuf.st_mode));
	}
	return (false);
}
