/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:04:24 by gle-mini          #+#    #+#             */
/*   Updated: 2023/02/09 06:07:08 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static t_token_type	return_token_type(t_list *lst_token)
{
	t_token	*token;

	token = lst_token->content;
	return (token->type);
}

static char *return_token_text(t_list *lst_token)
{
	t_token	*token;

	token = lst_token->content;
	return (token->text);
}

t_bool	start_or_finish_pipe(t_list *lst_token)
{
	if (return_token_type(lst_token) == TOKEN_PIPE \
	|| return_token_type(ft_lstlast(lst_token)) == TOKEN_PIPE)
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
		if ((return_token_type(lst_current) == TOKEN_REDIRECT_APPEND || \
		return_token_type(lst_current) == TOKEN_HEREDOC) && \
		!lst_current->next)
			{
				printf("MinisheLLD:\tsyntax error near `newline'\n");
				return (true);
			}
		if (return_token_type(lst_current) == TOKEN_REDIRECT_APPEND || \
		return_token_type(lst_current) == TOKEN_HEREDOC)
		{
			if (return_token_type(lst_current->next) == TOKEN_REDIRECT_IN || \
			return_token_type(lst_current->next) == TOKEN_REDIRECT_OUT || \
			return_token_type(lst_current->next) != TOKEN_WORD)
			{
				printf("MinisheLLD:\tsyntax error near unexpected token `%s'\n", \
				return_token_text(lst_current));
				return (true);
			}
		}
		lst_current = lst_current->next;
	}
	return (false);
}

t_bool new_line(t_list *lst_token)
{
	// t_list	*lst_current;

	// lst_current = lst_token;
	if (return_token_type(ft_lstlast(lst_token)) == TOKEN_REDIRECT_IN\
		|| return_token_type(ft_lstlast(lst_token)) == TOKEN_REDIRECT_OUT\
		|| return_token_type(ft_lstlast(lst_token)) == TOKEN_REDIRECT_APPEND\
		|| return_token_type(ft_lstlast(lst_token)) == TOKEN_HEREDOC)
	{
		printf("MinisheLLD:\tsyntax error near `newline'\n");
		return (true);
	}
	return (false);
}

int	syntaxe_error(t_list *lst_token)
{
	if (redirect(lst_token) || start_or_finish_pipe(lst_token))
		return (0);
	if (lst_token == NULL || new_line(lst_token))
		return (0);

	return (1);
}
