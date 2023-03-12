/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_merge_secure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 04:14:35 by gle-mini          #+#    #+#             */
/*   Updated: 2023/03/12 05:56:40 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_merge_secure(char *str1, char *str2)
{
	char	*result;

	result = malloc(ft_strlen_secure(str1) + ft_strlen_secure(str2) + 1);
	if (result == NULL)
		return (NULL);
	if (str1 != NULL)
	{
		ft_memcpy(result, str1, ft_strlen_secure(str1));
		free(str1);
		str1 = NULL;
	}
	if (str2 != NULL)
	{
		ft_memcpy(result, str2, ft_strlen_secure(str2));
		free(str2);
		str2 = NULL;
	}
	result[ft_strlen_secure(str1) + ft_strlen_secure(str2) + 1] = '\0';
	return (result);
}
