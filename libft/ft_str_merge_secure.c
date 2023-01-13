/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_merge_secure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 04:14:35 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/13 04:30:29 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_merge_secure(char *str1, char *str2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(ft_strlen_secure(str1) + ft_strlen_secure(str2) + 1);
	if (result == NULL)
		return (NULL);
	if (str1 != NULL)
	{
		ft_memcpy(result, str1, ft_strlen_secure(str1));
		free(str1);
	}
	if (str2 != NULL)
	{
		ft_memcpy(result, str2, ft_strlen_secure(str2));
		free(str2);
	}
	result[ft_strlen_secure(str1) + ft_strlen_secure(str2) + 1] = '\0';
	return (result);
}
