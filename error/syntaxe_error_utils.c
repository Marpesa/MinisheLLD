/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:21:26 by lmery             #+#    #+#             */
/*   Updated: 2023/02/11 19:34:50 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

t_token_type	return_token_type(t_list *lst_token)
{
	t_token	*token;

	token = lst_token->content;
	return (token->type);
}

char	*return_token_text(t_list *lst_token)
{
	t_token	*token;

	token = lst_token->content;
	return (token->text);
}

t_bool	start_or_finish_pipe(t_list *lst_token)
{
	t_list	*lst_current;

	lst_current = lst_token;
	if (return_token_type(lst_token) == TOKEN_PIPE \
	|| return_token_type(ft_lstlast(lst_token)) == TOKEN_PIPE)
	{
		printf(_ORANGE2 "MinisheLLD:\tsyntax error near unexpected token `|'\n");
		return (true);
	}
	while (lst_current)
	{
		if (return_token_type(lst_current) == TOKEN_PIPE \
		&& lst_current->next && \
		return_token_type(lst_current->next) == TOKEN_PIPE)
		{
			printf(_ORANGE2 \
			"MinisheLLD:\tsyntax error near unexpected token `|'\n");
			return (true);
		}
		lst_current = lst_current->next;
	}
	return (false);
}
