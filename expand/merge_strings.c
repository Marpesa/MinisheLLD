/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 04:56:17 by gle-mini          #+#    #+#             */
/*   Updated: 2023/03/11 23:14:21 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

char	*m_s(char *str1, char *str2)
{
	char	*result;

	result = malloc(ft_strlen_secure(str1) + ft_strlen_secure(str2) + 1);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, ft_strlen_secure(str1) + ft_strlen_secure(str2) + 1);
	if (str1 != NULL)
		ft_strlcpy_secure(result, str1, ft_strlen_secure(str1) + 1);
	if (str2 != NULL)
		ft_strlcat_secure(result, str2, ft_strlen_secure(result) \
				+ ft_strlen_secure(str2) + 1);
	free(str1);
	str1 = NULL;
	return (result);
}
