/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:04:24 by gle-mini          #+#    #+#             */
/*   Updated: 2023/03/11 21:34:26 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

t_bool	redirect_utils(t_list *lst_current)
{
	if ((return_token_type(lst_current) == TOKEN_REDIRECT_APPEND || \
	return_token_type(lst_current) == TOKEN_HEREDOC) && \
	!lst_current->next)
	{
		ft_print_error(_ORANGE2 "syntax error near `newline'\n" _END, "", "");
		return (true);
	}
	if (return_token_type(lst_current) == TOKEN_REDIRECT_APPEND || \
	return_token_type(lst_current) == TOKEN_HEREDOC)
	{
		if (return_token_type(lst_current) == TOKEN_HEREDOC && \
		return_token_type(lst_current->next) == TOKEN_REDIRECT_IN)
			if (return_token_type(lst_current->next) != TOKEN_HEREDOC)
				return (false);
		if ((return_token_type(lst_current->next) == TOKEN_REDIRECT_IN || \
		return_token_type(lst_current->next) == TOKEN_REDIRECT_OUT || \
		return_token_type(lst_current->next) != TOKEN_WORD) && \
		return_token_type(lst_current->next) != TOKEN_LIM)
		{
			ft_print_error(_ORANGE2 "syntax error near unexpected token \'", \
			return_token_text(lst_current), "\'\n"_END);
			return (true);
		}
	}
	return (false);
}

t_bool	redirect(t_list *lst_token)
{
	t_list	*lst_current;

	lst_current = lst_token;
	while (lst_current)
	{
		if (redirect_utils(lst_current) == true)
			return (true);
		if ((return_token_type(lst_current) == TOKEN_REDIRECT_IN || \
		return_token_type(lst_current) == TOKEN_REDIRECT_OUT) \
		&& lst_current->next && \
		return_token_type(lst_current->next) != TOKEN_WORD)
		{
			ft_print_error(_ORANGE2 "syntax error near unexpected token \'", \
			return_token_text(lst_current), "\'\n"_END);
			return (true);
		}
		lst_current = lst_current->next;
	}
	return (false);
}

t_bool	new_line(t_list *lst_token)
{
	if (return_token_type(ft_lstlast(lst_token)) == TOKEN_REDIRECT_IN \
	|| return_token_type(ft_lstlast(lst_token)) == TOKEN_REDIRECT_OUT \
	|| return_token_type(ft_lstlast(lst_token)) == TOKEN_REDIRECT_APPEND \
	|| return_token_type(ft_lstlast(lst_token)) == TOKEN_HEREDOC)
	{
		ft_print_error(_ORANGE2 "syntax error near `newline'\n" _END, \
		NULL, NULL);
		return (true);
	}
	return (false);
}

int	syntaxe_error(t_list *lst_token)
{
	if (!lst_token)
		return (1);
	if (redirect(lst_token) || start_or_finish_pipe(lst_token))
		return (0);
	if (lst_token == NULL || new_line(lst_token))
		return (0);
	return (1);
}
