/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:38:23 by lmery             #+#    #+#             */
/*   Updated: 2023/01/13 03:46:02 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

char	*ft_get_token_type(enum e_token_type type)
{
	if (type == TOKEN_LIM)
		return ("TOKEN_LIM");
	else if (type == TOKEN_WORD)
		return ("TOKEN_WORD");
	else if (type == TOKEN_REDIRECT_IN)
		return ("TOKEN_REDIRECT_IN");
	else if (type == TOKEN_REDIRECT_OUT)
		return ("TOKEN_REDIRECT_OUT");
	else if (type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	else if (type == TOKEN_AND)
		return ("TOKEN_AND");
	else if (type == TOKEN_IGNORE)
		return ("TOKEN_IGNORE");
	else if (type == TOKEN_HEREDOC)
		return ("TOKEN_HEREDOC");
	else if (type == TOKEN_REDIRECT_APPEND)
		return ("TOKEN_REDICRECT_APPEND");
	return (NULL);
}

void	lexer_data_init(t_lexer *data)
{
	data->token_count = 0;
	data->token_start = 0;
	data->in_word = false;
	data->token = NULL;
	data->lst_token = NULL;
}

t_list	*lst_add_token(t_list *lst_token, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (new == NULL)
		return (NULL);
	ft_lstadd_back(&lst_token, new);
	return (lst_token);
}

int	is_special(char c)
{
	if (c == '<')
		return (TOKEN_REDIRECT_IN);
	if (c == '>')
		return (TOKEN_REDIRECT_OUT);
	if (c == '|')
		return (TOKEN_PIPE);
	if (c == '&')
		return (TOKEN_AND);
	if (c == '\\' || c == ';' || c == '{' || c == '}')
		return (TOKEN_IGNORE);
	return (0);
}

void	lst_print_token(t_list *head)
{
	t_token	*token;

	while (head)
	{
		token = head->content;
		printf("token type: %s\ntoken text: %s\n", \
		ft_get_token_type(token->type), token->text);
		head = head->next;
	}
}
