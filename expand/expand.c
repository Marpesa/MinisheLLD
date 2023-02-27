/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:14:45 by lmery             #+#    #+#             */
/*   Updated: 2023/02/27 19:51:31 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static char	*env_var_find(char *start, char *end, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(start, env[i], end - start) == 0 && \
				env[i][end - start] == '=')
		{
			return (&env[i][end - start + 1]);
		}
		i++;
	}
	return (NULL);
}

static int	replace_env_var_in_new_str(char *start, char *end, char **new_str)
{
	char	*append_str;

	append_str = NULL;
	append_str = malloc(ft_strlen_secure(*new_str) + (end - start) + 1);
	if (append_str == NULL)
		return (-1);
	ft_bzero(append_str, ft_strlen_secure(*new_str) + (end - start) + 1);
	ft_strlcpy_secure(append_str, *new_str, ft_strlen_secure(*new_str) + 1);
	ft_strlcat(append_str, start, \
			ft_strlen_secure(append_str) + (end - start) + 1);
	free(*new_str);
	*new_str = append_str;
	return (1);
}

static int	expand_token(t_token *token, char **env)
{
	int		result;
	t_bool	in_d_quote;
	char	*start;
	char	*end;
	char	*new_str;

	in_d_quote = false;
	new_str = NULL;
	end = token->text;
	while (1)
	{
		result = custom_tokenizer(end, &start, &end, &in_d_quote);
		if ((*start == '$' && (end - start) > 1) || \
			(*start == '$' && (end - start) == 1 && \
			*(start + 1) == '\'' && in_d_quote == false))
		{
			new_str = merge_strings(new_str, env_var_find(start + 1, end, env));
			if (new_str == NULL)
				return (-1);
		}
		else
		{
			if (replace_env_var_in_new_str(start, end, &new_str) == -1)
				return (-1);
		}
		if (result == 0)
			break ;
	}
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
