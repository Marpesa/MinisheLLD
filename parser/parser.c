/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:25:03 by lmery             #+#    #+#             */
/*   Updated: 2023/03/12 00:49:37 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	init_cmd(t_command	**command, t_list **lst_cmd, t_token **token_prev)
{
	(*command)->word = NULL;
	(*command)->redir = NULL;
	(*command)->fd_in = STDIN_FILENO;
	(*command)->fd_out = STDOUT_FILENO;
	(*lst_cmd) = NULL;
	(*token_prev) = NULL;
}

int	parse_token(t_list **lst_token, t_token **token_previous, t_command **command, t_list **lst_command)
{
	t_token *token;

	token = (*lst_token)->content;
	if (token->type == TOKEN_PIPE)
	{
		*command = malloc(sizeof(t_command));
		if (command == NULL)
			return (-1);
		(*command)->word = NULL;
		(*command)->redir = NULL;
		(*command)->fd_in = STDIN_FILENO;
		(*command)->fd_out = STDOUT_FILENO;
		lst_add_command(lst_command, *command);
	}
	else if (token->type == TOKEN_REDIRECT_IN || \
	token->type == TOKEN_REDIRECT_OUT || \
	token->type == TOKEN_REDIRECT_APPEND || \
	token->type == TOKEN_HEREDOC)
	{
		if (add_str_to_map(token->text, (*command)->redir, \
		&(*command)->redir) == -1)
			return (-1);
	}
	else if ((*token_previous) != NULL && \
			((*token_previous)->type == TOKEN_REDIRECT_IN || \
			(*token_previous)->type == TOKEN_REDIRECT_OUT || \
			(*token_previous)->type == TOKEN_REDIRECT_APPEND))
	{
		if (add_str_to_map(token->text, (*command)->redir, \
		&(*command)->redir) == -1)
			return (-1);
	}
	else if (token->type == TOKEN_WORD)
	{
		if (add_str_to_map(token->text, (*command)->word, \
		&(*command)->word) == -1)
			return (-1);
	}
	(*token_previous) = (*lst_token)->content;
	(*lst_token) = (*lst_token)->next;
	return (1);
}


int	parser(t_list	*lst_token, t_list **lst_result)
{
	t_list		*lst_command;
	t_command	*command;	
	//t_token		*token;
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
	{
		parse_token(&lst_token, &token_previous, &command, &lst_command);
		/*
		token = lst_token->content;
		if (token->type == TOKEN_PIPE)
		{
			command = malloc(sizeof(t_command));
			if (command == NULL)
				return (-1);
			command->word = NULL;
			command->redir = NULL;
			command->fd_in = STDIN_FILENO;
			command->fd_out = STDOUT_FILENO;
			lst_add_command(&lst_command, command);
		}
		else if (token->type == TOKEN_REDIRECT_IN || \
		token->type == TOKEN_REDIRECT_OUT || \
		token->type == TOKEN_REDIRECT_APPEND || \
		token->type == TOKEN_HEREDOC)
		{
			if (add_str_to_map(token->text, command->redir, \
			&command->redir) == -1)
				return (-1);
		}
		else if (token_previous != NULL && \
				(token_previous->type == TOKEN_REDIRECT_IN || \
				token_previous->type == TOKEN_REDIRECT_OUT || \
				token_previous->type == TOKEN_REDIRECT_APPEND))
		{
			if (add_str_to_map(token->text, command->redir, \
			&command->redir) == -1)
				return (-1);
		}
		else if (token->type == TOKEN_WORD)
		{
			if (add_str_to_map(token->text, command->word, \
			&command->word) == -1)
				return (-1);
		}
		token_previous = lst_token->content;
		lst_token = lst_token->next;
		*/
	}
	*lst_result = lst_command;
	return (1);
}
