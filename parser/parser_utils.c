/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:33:40 by lmery             #+#    #+#             */
/*   Updated: 2023/03/09 18:33:15 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	lst_add_command(t_list **lst_command, t_command *command)
{
	t_list	*new;

	new = NULL;
	new = ft_lstnew(command);
	if (new == NULL)
		return (-1);
	ft_lstadd_back(lst_command, new);
	return (1);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map == NULL)
		return ;
	while (map[i] != NULL)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

static void	add_to_map_utils(char ***map)
{
	if (*map != NULL)
	{
		free_map(*map);
		*map = NULL;
	}
}

int	add_str_to_map(char *str, char **map, char ***map_result)
{
	char		**new_map;
	size_t		i;

	i = 0;
	if (str == NULL)
	{
		*map_result = map;
		return (1);
	}
	new_map = malloc(sizeof(char *) * (ft_maplen_secure(map) + 2));
	if (new_map == NULL)
		return (-1);
	while (i < ft_maplen_secure(map))
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
			return(-1);
		i++;
	}
	new_map[i] = ft_strdup(str);
	if (!new_map[i])
		return(-1);
	new_map[i + 1] = NULL;
	add_to_map_utils(&map);
	*map_result = new_map;
	return (1);
}