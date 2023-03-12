/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 01:27:56 by lmery             #+#    #+#             */
/*   Updated: 2023/03/12 01:28:37 by lmery            ###   ########.fr       */
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

int	first_command(t_command **command, t_list **lst_command)
{
	*command = malloc(sizeof(t_command));
	if (command == NULL)
		return (-1);
	(*command)->word = NULL;
	(*command)->redir = NULL;
	(*command)->fd_in = STDIN_FILENO;
	(*command)->fd_out = STDOUT_FILENO;
	lst_add_command(lst_command, *command);
	return (1);
}

t_bool	is_add_token(t_token *token)
{
	if (token->type == TOKEN_REDIRECT_IN || \
	token->type == TOKEN_REDIRECT_OUT || \
	token->type == TOKEN_REDIRECT_APPEND || \
	token->type == TOKEN_HEREDOC)
		return (true);
	return (false);
}

t_bool	is_add_prev_token(t_token *token)
{
	if (token != NULL && \
			(token->type == TOKEN_REDIRECT_IN || \
			token->type == TOKEN_REDIRECT_OUT || \
			token->type == TOKEN_REDIRECT_APPEND))
		return (true);
	return (false);
}
