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
static char **add_str_to_map(char *str, char **map)
{
	char	**new_map;
	size_t		i;

	i = 0;
	if (str == NULL)
		return (map);
	new_map = malloc(sizeof(char *) * (ft_maplen_secure(map) + 2));
	while (i < ft_maplen_secure(map))
	{
		//ft_strncpy(new_map[i], map[i], ft_strlen_secure(map[i]));
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
	return (new_map);
}

static t_list	*lst_add_command(t_list **lst_command, t_command *command)
{
	t_list	*new;

	new = NULL;
	new = ft_lstnew(command);
	if (new == NULL)
		return (NULL);
	ft_lstadd_back(lst_command, new);
	return (*lst_command);
}

t_list	*parser(t_list	*lst_token)
{
	t_list		*lst_command;
	t_command	*command;	
	t_token		*token;
	t_token		*token_previous;

	command = malloc(sizeof(t_command));
	command->word = NULL;
	command->redir = NULL;
	lst_command = NULL;
	token_previous = NULL;
	lst_add_command(&lst_command, command);
	while (lst_token)
	{
		token = lst_token->content;
		if (token->type == TOKEN_PIPE)
		{
			command = malloc(sizeof(t_command));
			command->word = NULL;
			command->redir = NULL;
			lst_add_command(&lst_command, command);
		}
		else if (token->type == TOKEN_REDIRECT_IN || 
				 token->type == TOKEN_REDIRECT_OUT || 
				 token->type == TOKEN_REDIRECT_APPEND) 
		{
			//printf("%s\n", token->text);
			command->redir = add_str_to_map(token->text, command->redir);
			//print_map(command->redir);
			
		}
		else if (token_previous != NULL && 
				(token_previous->type == TOKEN_REDIRECT_IN || 
				 token_previous->type == TOKEN_REDIRECT_OUT || 
				 token_previous->type == TOKEN_REDIRECT_APPEND))
		{
			command->redir = add_str_to_map(token->text, command->redir);
			//print_map(command->redir);
		}
		else if (token->type == TOKEN_WORD)
		{
			//printf("%s\n", token->text);
			command->word = add_str_to_map(token->text, command->word);
			//print_map(command->word);
			//print_command(command);
		}
		else
		{
			printf(_ORANGE "\nERROR\n" _END);
		}
		token_previous = lst_token->content;
		lst_token = lst_token->next;
	}
	return (lst_command);
}
