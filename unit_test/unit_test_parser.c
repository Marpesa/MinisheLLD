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
	size_t	i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i); 
}

void	print_map(char **map)
{
	int		i;

	i = 0;
	if (map == NULL)
		return ;
	while (map[i])
	{
		printf("%s ", map[i]);
		i++;
	}
	printf("\n");
}

char	**ft_mapdup(char **map)
{
	size_t	i;
	char	**dup_map;
	
	i = 0;
	dup_map = malloc(sizeof(char **) * ft_maplen(map));
	if (dup_map == NULL)
		return (NULL);
	while (map[i] != NULL)
	{
		dup_map[i] = ft_strdup(map[i]);	
		ft_putstr_fd("\n", 1);
		i++;
	}
		ft_putstr_fd("NULL\n", 1);
	return (map);
}

char **create_map(int size, ...)
{
	va_list	args;
	char	**map;
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
// NOUBLIE PAS QUE CE SONT DES LST COMMANDE QUE ON COMPARt
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
		command = malloc(sizeof(t_command));
		if (command == NULL)
			return (NULL);
		char **word = va_arg(args, char **);
		command->word = ft_mapdup(word);
	//	print_map(command->word);
		char **redir = va_arg(args, char **);	
		command->redir = ft_mapdup(redir);
	//	print_map(command->redir);
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

void	print_lst_command_test(t_list *lst_command)
{
	t_command	*command;

	while (lst_command != NULL)
	{
		command = lst_command->content;
		print_command(command);
		lst_command = lst_command->next;	
	}
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
