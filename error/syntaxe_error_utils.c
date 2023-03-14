/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:21:26 by lmery             #+#    #+#             */
/*   Updated: 2023/03/14 18:08:13 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	closed_quotes(char *input, int *i)
{
	char	quote;
	int		res;

	res = 2;
	quote = input[*i];
	*i += 1;
	while (input [*i])
	{
		if (input[*i] == quote)
		{
			res = 0;
			break ;
		}
		*i += 1;
	}
	return (res);
}

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
		ft_print_error(_ORANGE2 "syntax error near unexpected token `|'", \
		NULL, "\n");
		return (true);
	}
	while (lst_current)
	{
		if (return_token_type(lst_current) == TOKEN_PIPE \
		&& lst_current->next && \
		return_token_type(lst_current->next) == TOKEN_PIPE)
		{
			ft_print_error(_ORANGE2 "syntax error near unexpected token `|'", \
			NULL, "\n");
			return (true);
		}
		lst_current = lst_current->next;
	}
	return (false);
}

int	ft_print_error(char *msg, char *data, char *end)
{
	if (msg)
	{
		ft_putstr_fd(_ORANGE2 "   MinisheLLD : ", 2);
		ft_putstr_fd(msg, 2);
	}
	if (data)
		ft_putstr_fd(data, 2);
	if (end)
		ft_putstr_fd(end, 2);
	return (0);
}
