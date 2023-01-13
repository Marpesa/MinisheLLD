/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 04:12:43 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/13 03:47:53 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static void	super_token(char *input, int *i, t_lexer *data)
{
	t_token	*token;

	data->in_word = false;
	token = NULL;
	token = malloc(sizeof(t_token) * 1);
	token->text = malloc(sizeof(char) * 2);
	ft_strlcpy(token->text, &input[*i], 2);
	token->type = is_special(input[*i]);
	data->token_count++;
	data->lst_token = lst_add_token(data->lst_token, token);
	if (data->lst_token == NULL)
		exit_error("Malloc failed while making special token");
	*i += 1;
}

static void	token_heredoc(char *input, int *i, t_lexer *data)
{
	t_token	*token;

	data->in_word = false;
	token = malloc(sizeof(t_token) * 1);
	token->text = malloc(sizeof(char) * 3);
	ft_strlcpy(token->text, &input[*i], 3);
	token->type = TOKEN_HEREDOC;
	data->token_count++;
	data->lst_token = lst_add_token(data->lst_token, token);
	if (data->lst_token == NULL)
		exit_error("Malloc failed while making heredoc token");
	*i += 2;
}

static void	token_redirect_append(char *input, int *i, t_lexer *data)
{
	t_token	*token;

	data->in_word = false;
	token = malloc(sizeof(t_token) * 1);
	token->text = malloc(sizeof(char) * 3);
	ft_strlcpy(token->text, &input[*i], 3);
	token->type = TOKEN_REDIRECT_APPEND;
	data->token_count++;
	data->lst_token = lst_add_token(data->lst_token, token);
	if (data->lst_token == NULL)
		exit_error("Malloc failed while redirect appending");
	*i += 2;
}

static void	token_word(char *input, int *i, t_lexer *data)
{
	t_token	*token;
	int		word_len;
	int		j;

	j = 0;
	word_len = 0;
	token = NULL;
	if (data->in_word == false)
		data->token_count++;
	data->in_word = true;
	data->token_start = *i;
	j = *i;
	while (input[j] != '\0' && !ft_isspace(input[j]) && !is_special(input[j]))
		j++;
	word_len = j - *i;
	token = malloc(sizeof(t_token) * 1);
	token->type = TOKEN_WORD;
	token->text = malloc(sizeof(char) * (word_len + 1));
	ft_strlcpy(token->text, &input[*i], word_len + 1);
	data->lst_token = lst_add_token(data->lst_token, token);
	if (data->lst_token == NULL)
		exit_error("Malloc failed while tokenizing words");
	*i += word_len;
}

t_list	*lexer(char *input)
{
	t_lexer	data;
	int		i;

	i = 0;
	lexer_data_init(&data);
	while (input[i] != '\0')
	{
		if (ft_isspace(input[i]))
		{
			data.in_word = false;
			while (ft_isspace(input[i]))
				i++;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
			token_heredoc(input, &i, &data);
		else if (input[i] == '>' && input[i + 1] == '>')
			token_redirect_append(input, &i, &data);
		else if (input[i] != '\0' && !ft_isspace(input[i]) \
		&& !is_special(input[i]))
			token_word(input, &i, &data);
		else if ((is_special(input[i])))
			super_token(input, &i, &data);
	}
	return (data.lst_token);
}
