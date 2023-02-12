/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:38:23 by lmery             #+#    #+#             */
/*   Updated: 2023/02/12 16:35:53 by gle-mini         ###   ########.fr       */
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

int	lst_add_token(t_list **lst_token, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (new == NULL)
		return (-1);
	ft_lstadd_back(lst_token, new);
	//print_lst_token(*lst_token);
	return (1);
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
