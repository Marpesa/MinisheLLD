/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:07:12 by lmery             #+#    #+#             */
/*   Updated: 2023/01/17 20:10:51 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

size_t	ft_maplen(char **map)
{
	char **end_map;

	end_map = map;
	while (end_map != NULL)
		end_map++;
	return (map - end_map); 
}

void	print_map(char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		printf("%s ", map[i]);
		i++;
	}
	printf("\n");
}

char **create_map(int size, ...)
{
	va_list	args;
	char	**map;
	//char	*str;
	int		i;

	i = 0;
	if (size == 0)
		return (NULL);
	map = malloc(sizeof(char *) * (size + 1));	
	if (map == NULL)
		return (NULL);
	va_start(args, size);
	while (i < size)
	{
		char *str = va_arg(args, char *);
		map[i] = ft_strdup(str);
		i++;
	}
	va_end(args);
	map[i] = NULL;
	return (map);
}
// NOUBLIE PAS QUE CE SONT DES LST COMMANDE QUE ON COMPAR
t_list	*create_lst_command_test(int size, ...) 
{
	t_list		*lst_command;
	t_command	*command;
	va_list		args;
	int			i;

	i = 0;
	lst_command = NULL;
	va_start(args, size);
	while (i < size)
	{
		command = NULL;
		command = malloc(sizeof(command));
		if (command == NULL)
			return (NULL);
		command->word = va_arg(args, char **);
		command->redir = va_arg(args, char **);	
		lst_command= lst_add_token(lst_command, command);
		i++;
	}
	va_end(args);
	return (lst_command);
}


void	print_command(t_command *command)
{
	printf("-------word-------\n");
	print_map(command->word);	
	printf("-------redir-------\n");
	print_map(command->redir);	
}

/*
int main()
{
	t_list		*lst_command;
	t_command	*command;

	lst_command = NULL;
	lst_command = create_lst_command_test(2, create_map(2, "echo", "bonjour"), NULL, create_map(2, "cat", "main.c"), create_map(1, "test"));
	while (lst_command != NULL)
	{
		command = lst_command->content;
		print_command(command);
		lst_command = lst_command->next;
	}
}
*/
