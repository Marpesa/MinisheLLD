/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extend_malloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:16:35 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/14 18:31:12 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_extend_malloc(void **ptr, size_t new_size)
{
	void	*new_ptr;

	if (*ptr == NULL)
	{
		*new_ptr = malloc(new_size);
		if (*new_ptr == NULL)
			return (1);
		return (0);
	}
	if (new_size == 0)
	{
		free(*ptr);
		*ptr = NULL;
		return (NULL);
	}
	*new_ptr = malloc(new_size);
	free(*ptr);
	*ptr = NULL;	
	if (*new_ptr == NULL)
		return (1);
	ft_memcpy(new_ptr, ptr, new_size);
	*ptr = new_ptr;
	return (0);
}
