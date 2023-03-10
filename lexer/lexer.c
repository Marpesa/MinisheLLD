/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 04:12:43 by gle-mini          #+#    #+#             */
/*   Updated: 2023/03/09 18:09:14 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static int	token_heredoc(char *input, int *i, t_lexer *data)
{
	t_token	*token;

	data->in_word = false;
	token = malloc(sizeof(t_token) * 1);
	if (token == NULL)
		return (-1);
	token->text = malloc(sizeof(char) * 3);
	if (token->text == NULL)
		return (-1);
	ft_strlcpy(token->text, &input[*i], 3);
	token->type = TOKEN_HEREDOC;
	data->token_count++;
	if (lst_add_token(&data->lst_token, token) == -1)
		return (-1);
	*i += 2;
	return (1);
}

static int	token_redirect_append(char *input, int *i, t_lexer *data)
{
	t_token	*token;

	data->in_word = false;
	token = malloc(sizeof(t_token) * 1);
	if (token == NULL)
		return (-1);
	token->text = malloc(sizeof(char) * 3);
	if (token->text == NULL)
		return (-1);
	ft_strlcpy(token->text, &input[*i], 3);
	token->type = TOKEN_REDIRECT_APPEND;
	data->token_count++;
	if (lst_add_token(&data->lst_token, token) == -1)
		return (-1);
	*i += 2;
	return (1);
}

int	ft_word_in_quote(char *input, int i, int len)
{
	int	start;

	start = i;
	if (input[i] == '\"')
		i++;
	while (input[i] && input[i] != '\"')
		i++;
	if (i - start >= len)
		len = i - start + 1;
	return (len);
}

static void	skip_spaces(char *input, int *i, t_lexer *data)
{
	if (ft_isspace(input[*i]))
	{
		data->in_word = false;
		while (ft_isspace(input[*i]))
			(*i)++;
	}
}

int	lexer(char *input, t_list **lst_token)
{
	t_lexer	data;
	int		i;

	i = 0;
	lexer_data_init(&data);
	while (input[i] != '\0')
	{
		skip_spaces(input, &i, &data);
		if (input[i] == '<' && input[i + 1] == '<')
			if (token_heredoc(input, &i, &data) == -1)
				return (-1);
		if (input[i] == '>' && input[i + 1] == '>')
			if (token_redirect_append(input, &i, &data) == -1)
				return (-1);
		if (input[i] != '\0' && !ft_isspace(input[i]) && !is_special(input[i]))
		{
			if (token_word(input, &i, &data) == -1)
				return (-1);
		}
		if ((is_special(input[i])))
			if (super_token(input, &i, &data) == -1)
				return (-1);
	}
	*lst_token = data.lst_token;
	return (1);
}
