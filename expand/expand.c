/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:14:45 by lmery             #+#    #+#             */
/*   Updated: 2023/03/11 23:14:19 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static int	replace_env_var_in_new_str(char *start, char *end, char **new_str)
{
	char	*append_str;

	append_str = NULL;
	append_str = malloc(ft_strlen_secure(*new_str) + (end - start) + 1);
	if (append_str == NULL)
	{
		ft_print_error(_ORANGE2 \
		"Malloc error in replace_env_var_in_new_str\n" _END, NULL, NULL);
		return (-1);
	}
	ft_bzero(append_str, ft_strlen_secure(*new_str) + (end - start) + 1);
	ft_strlcpy_secure(append_str, *new_str, ft_strlen_secure(*new_str) + 1);
	ft_strlcat(append_str, start, \
			ft_strlen_secure(append_str) + (end - start) + 1);
	free(*new_str);
	*new_str = append_str;
	return (1);
}

static t_quotes	*tquotes_init(t_quotes *quotes)
{
	quotes = malloc(sizeof(t_quotes));
	if (quotes == NULL)
		return (NULL);
	quotes->in_d = false;
	quotes->in_s = false;
	return (quotes);
}

int	loop_expand(char *start, char *end, char **new_str, char **env)
{
	int			result;
	t_quotes	*q;

	q = NULL;
	q = tquotes_init(q);
	if (q == NULL)
		return (-1);
	while (1)
	{
		result = custom_tokenizer(end, &start, &end, q);
		if ((*start == '$' && (end - start) > 1) || ((*start == '$' && \
		(end - start) == 1) && (q->in_d == false && q->in_s == false)))
		{
			*new_str = m_s(*new_str, var_find(start + 1, end, env, q->s_in_d));
			if (*new_str == NULL)
				result = -1;
		}
		else if (replace_env_var_in_new_str(start, end, new_str) == -1)
			result = -1;
		if (result == 0 || result == -1)
			break ;
	}
	free(q);
	q = NULL;
	return (result);
}

static int	expand_token(t_token *token, char **env)
{
	int		result;
	char	*start;
	char	*end;
	char	*new_str;

	new_str = NULL;
	start = NULL;
	end = token->text;
	result = loop_expand(start, end, &new_str, env);
	if (result == -1)
		return (-1);
	free(token->text);
	token->text = new_str;
	return (1);
}

int	ft_expand(t_list *lst_token, char **env)
{
	t_token	*token;
	t_token	*token_next;

	token = NULL;
	token_next = NULL;
	while (lst_token != NULL)
	{
		token = lst_token->content;
		if (lst_token->next != NULL)
			token_next = lst_token->next->content;
		if (token_next != NULL && token->type == TOKEN_HEREDOC)
		{
			if (lst_token->next != NULL && token_next->type == TOKEN_WORD)
				token_next->type = TOKEN_LIM;
		}
		if (token->type == TOKEN_WORD)
		{			
			if (expand_token(token, env) == -1)
				return (-1);
			trim(&token->text);
		}
		lst_token = lst_token->next;
	}
	return (1);
}
