/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 04:56:17 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/13 05:41:33 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static char	*copy(char *dest, char *src, int *i)
{
	int		j;

	j = 0;
	while (src[j] != '\0')
	{
		dest[*i + j] = src[j];
		j++;
	}
	*i += j;
	return (dest);
}

char	*merge_strings(char *str1, char *str2)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(ft_strlen_secure(str1) + ft_strlen_secure(str2) + 1);
	if (result == NULL)
		return (NULL);
	if (str1 != NULL)
	{
		result = copy(result, str1, &i);
		free(str1);
	}
	if (str2 != NULL)
	{
		result = copy(result, str2, &i);
	}
	result[i] = '\0';
	return (result);
}
