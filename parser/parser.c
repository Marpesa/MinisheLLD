#include "minisheLLD.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map == NULL)
		return ;
	while(map[i] != NULL)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}
static int	add_str_to_map(char *str, char **map, char ***map_result)
{
	char	**new_map;
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
		i++;
	}
	new_map[i] = ft_strdup(str);
	new_map[i + 1] = NULL;
	if (map != NULL)
	{
		free_map(map);
		map = NULL;
	}
	print_map(new_map);
	*map_result = new_map;
	return (1);
}

static int	lst_add_command(t_list **lst_command, t_command *command)
{
	t_list	*new;

	new = NULL;
	new = ft_lstnew(command);
	if (new == NULL)
		return (-1);
	ft_lstadd_back(lst_command, new);
	return (1);
}

int	parser(t_list	*lst_token, t_list **lst_result)
{
	t_list		*lst_command;
	t_command	*command;	
	t_token		*token;
	t_token		*token_previous;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		return (-1);
	command->word = NULL;
	command->redir = NULL;
	lst_command = NULL;
	token_previous = NULL;

	if (lst_add_command(&lst_command, command) == -1)
		return (-1);
	print_lst_token(lst_token);
	while (lst_token != NULL)
	{
		token = lst_token->content;
		if (token->type == TOKEN_PIPE)
		{
			command = malloc(sizeof(t_command));
			if (command == NULL)
				return (-1);
			command->word = NULL;
			command->redir = NULL;
			lst_add_command(&lst_command, command);
		}
		else if (token->type == TOKEN_REDIRECT_IN || 
				 token->type == TOKEN_REDIRECT_OUT || 
				 token->type == TOKEN_REDIRECT_APPEND) 
		{
			//printf("%s\n", token->text);
			if (add_str_to_map(token->text, command->redir, &command->redir) == -1)
				return (-1);
			//print_map(command->redir);
			
		}
		else if (token_previous != NULL && 
				(token_previous->type == TOKEN_REDIRECT_IN || 
				 token_previous->type == TOKEN_REDIRECT_OUT || 
				 token_previous->type == TOKEN_REDIRECT_APPEND))
		{
			if (add_str_to_map(token->text, command->redir, &command->redir) == -1)
				return (-1);
			//print_map(command->redir);
		}
		else if (token->type == TOKEN_WORD)
		{
			//printf("%s\n", token->text);
			if (add_str_to_map(token->text, command->word, &command->word) == -1)
				return (-1);
			//print_map(command->word);
			//print_command(command);
		}
		// else
		// {
		// 	printf(_ORANGE "\nERROR\n" _END);
		// }
		token_previous = lst_token->content;
		lst_token = lst_token->next;
	}
//	print_lst_command(lst_command);
	*lst_result = lst_command;
	return (1);
}
