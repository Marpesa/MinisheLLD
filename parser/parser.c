/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:20:24 by lmery             #+#    #+#             */
/*   Updated: 2023/01/17 20:56:21 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

/*
cd
export
unset 
exit[___]
*/

// A modifier pour etre utiliser dans le parser et associer les cmd
static t_list	*lst_add_command(t_list *lst_token, void *command)
{
	t_list	*new;

	new = ft_lstnew(command);
	if (new == NULL)
		return (NULL);
	ft_lstadd_back(&lst_token, new);
	return (lst_token);
}

void	lst_print_command(t_list *cmd)
{
	t_command	*content;

	//content = malloc(sizeof(t_command));
	int	i;
	int	j;
	int	n;
	

	j = 0;
	i = 0;
	n = 0;
	printf("\n___________________________________________ \n\n");
	while (cmd)
	{
		content = cmd->content;
		while (content->word[i])
		{
			printf("commande %d word %d : %s\n", n, i, content->word[i]);
			i++;
		}
		while (content->redir[j])
		{	
			printf("command %d redir %d : %s\n", n, j, content->redir[j]);
			j++;
		}
		n++;
		cmd = cmd->next;
	}
}

/*
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
*/


t_list	*parser(t_list *lst_token)
{
	t_token	*token;
	// t_token	*token_next;
	t_command *command;
	t_bool	heredoc_before;
	t_list	*lst_command;
	int	i;
	int	j;

	j = 0;
	i = 0;
	heredoc_before = false;
	lst_command = NULL;
	command = NULL;
	command = malloc(sizeof(t_command));
	if (!command)
		return (0);
	command->word = malloc(sizeof(char *) * (ft_lstsize(lst_token) + 1));
	if (! command->word)
		return (0);
	command->redir = malloc(sizeof(char *) * (ft_lstsize(lst_token) + 1));
	if (! command->redir)
		return (0);

	// Gestion garbage collector 
	while (lst_token)
	{
		token = lst_token->content;
		// if (lst_token->next)
		//  	token_next = lst_token->next->content;
		if (token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_REDIRECT_OUT || \
		(token->type == TOKEN_WORD && heredoc_before == true))
		{
			// printf("test\n");
			command->redir[j] = ft_strdup(token->text);
			if (token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_REDIRECT_OUT)
				heredoc_before = true;
			else
			{
				heredoc_before = false;
				lst_command = lst_add_command(lst_command, command);
			}
			//Ajouter ici tous les words en cours et la redir dans un maillon lst_cmd
			j++;
		}
		else if (token->type == TOKEN_WORD)
		{
			command->word[i] = ft_strdup(token->text);
			heredoc_before = false;
			i++;
		}
		lst_token = lst_token->next;
		if (lst_command == NULL)
		{
			printf("TEST2\n");
			lst_command = lst_add_command(lst_command, command);
		}
	}
	printf("I = %d\n", i);
	printf("J = %d\n", j);

	command->word[i] = NULL;
	command->redir[j] = NULL;

	i = 0;
	j = 0;
	while (command->word[i])
		{
			printf (_BOLD "Word %d = %s\n"_END, i, command->word[i]);
			i++;
		}
	while (command->redir[j])
		{
			printf (_BOLD "Redir %d = %s\n"_END, j, command->redir[j]);
			j++;
		}
	print_lst_command_test(lst_command);
	return (lst_command);
}
