/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:25:03 by lmery             #+#    #+#             */
/*   Updated: 2023/03/12 01:28:30 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	increment_list(t_token **token_prev, t_list **lst_token)
{
	(*token_prev) = (*lst_token)->content;
	(*lst_token) = (*lst_token)->next;
}

int	parse_token(t_list **lst_token, t_token **token_prev, \
		t_command **command, t_list **lst_command)
{
	t_token	*token;

	token = (*lst_token)->content;
	if (token->type == TOKEN_PIPE)
	{
		if (first_command(command, lst_command) == -1)
			return (-1);
	}
	else if (is_add_token(token))
	{
		if (!add_str_to_map(token->text, (*command)->redir, &(*command)->redir))
			return (-1);
	}
	else if (is_add_prev_token(*token_prev))
	{
		if (!add_str_to_map(token->text, (*command)->redir, &(*command)->redir))
			return (-1);
	}
	else if (token->type == TOKEN_WORD)
	{
		if (!add_str_to_map(token->text, (*command)->word, &(*command)->word))
			return (-1);
	}
	increment_list(token_prev, lst_token);
	return (1);
}

int	parser(t_list	*lst_token, t_list **lst_result)
{
	t_list		*lst_command;
	t_command	*command;	
	t_token		*token_previous;

	if (lst_token == NULL)
		return (1);
	command = malloc(sizeof(t_command));
	if (command == NULL)
		return (-1);
	init_cmd(&command, &lst_command, &token_previous);
	if (lst_add_command(&lst_command, command) == -1)
		return (-1);
	while (lst_token != NULL)
		parse_token(&lst_token, &token_previous, &command, &lst_command);
	*lst_result = lst_command;
	return (1);
}
