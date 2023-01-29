/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:07:12 by lmery             #+#    #+#             */
/*   Updated: 2023/01/29 17:41:37 by gle-mini         ###   ########.fr       */
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
		i++;
	}
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
static size_t	ft_min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

t_bool	command_compare(t_command *command1, t_command *command2)
{
	//t_command	*command1;
	//t_command	*command2;
	char		**word1;
	char 		**word2;
	char		**redir1; 
	char		**redir2; 
	int			i;
	int			j;

	i = 0;
	j = 0;
	word1 = command1->word;
	word2 = command2->word;
	if (ft_maplen(word1) != ft_maplen(word2))
	{
		printf("command word size if different, word1: %ld | word2: %ld", ft_maplen(word1), ft_maplen(word2));
	}
	while (word1[i] != NULL && word2[j] != NULL)
	{
		if (strncmp(word1[i], word2[j], ft_min(ft_strlen(word1[i]), ft_strlen(word2[j]))) != 0)
		{
			printf("word1: %s | word2: %s\n", word1[i], word2[j]);
			return (false);
		}
		i++;
		j++;
	}
	i = 0;
	j = 0;
	redir1 = command1->word;
	redir2 = command2->word;
	while (redir1[i] != NULL && redir2[j] != NULL)
	{
		if (strncmp(redir1[i], redir2[j], ft_min(ft_strlen(redir1[i]), ft_strlen(redir2[j]))) != 0)
		{
			printf("word1: %s | word2: %s\n", redir1[i], redir2[j]);
			return (false);
		}
		i++;
		j++;
	}
	return (true);
}

t_bool	lst_command_compare(t_list *lst_command1, t_list *lst_command2)
{
	if (ft_lstsize(lst_command1) != ft_lstsize(lst_command2))
	{
		printf("size of lst_command is different, size lst_command1 : %d | size lst_command2 : %d\n", ft_lstsize(lst_command1), ft_lstsize(lst_command2));
		return (false);
	}
	while (lst_command1 && lst_command2)
	{
		if (command_compare(lst_command1->content, lst_command2->content) == false)
			return (false);
		lst_command1 = lst_command1->next;
		lst_command2 = lst_command2->next;
	}
	return (true);
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
