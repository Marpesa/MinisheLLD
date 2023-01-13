/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:04:24 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/13 03:52:44 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static t_token_type	return_token_type(t_list *lst_token)
{
	t_token	*token;

	token = lst_token->content;
	return (token->type);
}

t_bool	start_or_finish_pipe(t_list *lst_token)
{
	if (return_token_type(lst_token) == TOKEN_PIPE \
	&& return_token_type(ft_lstlast(lst_token)) == TOKEN_PIPE)
	{
		printf("MinisheLLD:\tsyntax error near unexpected token `|'\n");
		return (true);
	}
	return (false);
}

t_bool	redirect(t_list *lst_token)
{
	t_list	*lst_current;

	lst_current = lst_token;
	while (lst_current)
	{
		if (return_token_type(lst_current) == TOKEN_REDIRECT_IN || \
			return_token_type(lst_current) == TOKEN_REDIRECT_OUT || \
			return_token_type(lst_current) == TOKEN_REDIRECT_APPEND)
		{
			if (lst_current->next == NULL || \
			return_token_type(lst_current->next) != TOKEN_WORD)
			{
				printf("MinisheLLD:\tsyntax error near unexpected token\n");
				return (true);
			}
		}
		lst_current = lst_current->next;
	}
	return (false);
}

void	syntaxe_error(t_list *lst_token)
{
	if (start_or_finish_pipe(lst_token))
	{
		return ;
	}
	if (redirect(lst_token))
	{
		return ;
	}
}
