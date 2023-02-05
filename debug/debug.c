#include "minisheLLD.h"

void	print_map(char **map)
{
	size_t		i;

	i = 0;
	if (map == NULL)
		return ;
	while (i < ft_maplen_secure(map))
	{
		printf("%s ", map[i]);
		i++;
	}
	printf("\n");
}

void	print_command(t_command *command)
{
	printf(_BOLD _BLUE_LLD"\n------- WORD --------\n"_END);
	print_map(command->word);
	printf(_BOLD _BLUE_LLD"\n------- REDIR -------\n" _END);
	print_map(command->redir);
}

void	print_lst_command(t_list *lst_command)
{
	t_command	*command;

	while (lst_command != NULL)
	{
		command = lst_command->content;
		print_command(command);
		lst_command = lst_command->next;	
		printf("__________________\n");
	}
}


