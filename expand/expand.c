/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:14:45 by lmery             #+#    #+#             */
/*   Updated: 2023/01/13 18:30:03 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

/*
char	*merge_strings(char *str1, char *str2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(ft_strlen_secure(str1) + ft_strlen_secure(str2) + 1);
	if (result == NULL)
		return (NULL);
	if (str1 != NULL)
	{
		while (str1[i] != '\0')
		{
			result[i] = str1[i];
			i++;
		}
		free(str1);
	}
	if (str2 != NULL)
	{
		while (str2[j] != '\0')
		{
			result[i + j] = str2[j];
			j++;
		}
		//free(str2);
	}
	result[i + j] = '\0';
	return (result);
}
*/

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

static void	replace_env_var_in_new_str(char *start, char *end, char **new_str)
{
	char	*append_str;

	append_str = NULL;
	append_str = malloc(ft_strlen_secure(*new_str) + (end - start) + 1);
	ft_bzero(append_str, ft_strlen_secure(*new_str) + (end - start) + 1);
	ft_strlcpy_secure(append_str, *new_str, ft_strlen_secure(*new_str) + 1);
	ft_strlcat(append_str, start, \
			ft_strlen_secure(append_str) + (end - start) + 1);
	free(*new_str);
	*new_str = append_str;
}

static void	expand_token(t_token *token, char **env)
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
			if (new_str == NULL)
				printf("new_str = NULL\n");
			else
				printf("new_str = %s\n", new_str);
			new_str = merge_strings(new_str, env_var_find(start + 1, end, env));
		}
		else
			replace_env_var_in_new_str(start, end, &new_str);
		if (result == 0)
			break ;
	}
	free(token->text);
	token->text = new_str;
}

void	ft_expand(t_list *lst_token, char **env)
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
			expand_token(token, env);
			trim(&token->text);
		}
		lst_token = lst_token->next;
	}
}
