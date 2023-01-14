/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:07:36 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/14 14:57:16 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		printf("%s ", map[i]);
		i++;
	}
}

char	**convert_to_map(t_list *lst_token)
{
	t_token	*token;
	char	**map;
	int		i;

	i = 0;
	map = malloc(sizeof(char *) * ft_lstsize(lst_token) + 1);
	while (lst_token != NULL)
	{
		token = lst_token->content;
		map[i] = token->text;
		lst_token = lst_token->next;
		i++;
	}
	map[i] = NULL;	
	return (map);
}
