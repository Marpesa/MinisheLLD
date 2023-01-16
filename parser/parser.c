/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:20:24 by lmery             #+#    #+#             */
/*   Updated: 2023/01/16 21:27:49 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

/*
cd
export
unset 
exit[___]
*/

//A modifier pour etre utiliser dans le parser et associer les cmd
t_list	*lst_add_token(t_list *lst_token, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (new == NULL)
		return (NULL);
	ft_lstadd_back(&lst_token, new);
	return (lst_token);
}

t_command	*parser(t_list *lst_token)
{
	t_token	*token;
	t_token	*token_next;
	t_command *command;
	t_bool	heredoc_before;
	// t_list	*lst_command;
	int	i;
	int	j;

	j = 0;
	i = 0;
	// lst_command = NULL;
	command = malloc(sizeof(t_command));
	if (!command)
		return (0);
	command->word = malloc(sizeof(char *) * ft_lstsize(lst_token) + 1);
	if (! command->word)
		return (0);
	command->redir = malloc(sizeof(char *) * ft_lstsize(lst_token) + 1);
	if (! command->redir)
		return (0);
	// Gestion garbage collector 
	while (lst_token)
	{
		token = lst_token->content;
		if (lst_token->next)
		 	token_next = lst_token->next->content;
		if (token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_REDIRECT_OUT || \
		(token_next != NULL && token->type == TOKEN_WORD && token_next->type == TOKEN_REDIRECT_OUT) || \
		(token->type == TOKEN_WORD && heredoc_before == true))
		{
			printf("test\n");
			command->redir[j] = ft_strdup(token->text);
			if (token->type == TOKEN_REDIRECT_IN)
				heredoc_before = true;
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
	}
	command->word[i] = NULL;
	command->redir[j] = NULL;
	i = 0;
	j = 0;
	while (command->word[i] || command->redir [j])
	{
		if (command->word[i++])
			printf (_BOLD "Word %d = %s\n"_END, i, command->word[i - 1]);
		if (command->redir[j++])
			printf (_BOLD "Redir %d = %s\n"_END, i, command->redir[j - 1]);
	}
	return (command);
}