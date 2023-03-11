/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:59:13 by lmery             #+#    #+#             */
/*   Updated: 2023/03/11 21:37:25 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	len_token_word(char *input, int *i, t_lexer *data)
{
	int	j;

	j = 0;
	if (data->in_word == false)
		data->token_count++;
	data->in_word = true;
	data->token_start = *i;
	j = *i;
	while (input[j] != '\0' && !ft_isspace(input[j]) && !is_special(input[j]))
		j++;
	return (j);
}

int	token_word(char *input, int *i, t_lexer *data)
{
	t_token	*token;
	int		word_len;
	int		j;

	j = 0;
	word_len = 0;
	token = NULL;
	j = len_token_word(input, i, data);
	word_len = j - *i;
	if ((input[*i] == '\"' && input[*i + 1] != '\"') \
	|| (input[*i] == '\'' && input[*i + 1] != '\''))
		word_len = ft_word_in_quote(input, *i, word_len, input[*i]);
	token = malloc(sizeof(t_token) * 1);
	if (token == NULL)
		return (-1);
	token->type = TOKEN_WORD;
	token->text = malloc(sizeof(char) * (word_len + 1));
	if (token->text == NULL)
		return (-1);
	ft_strlcpy(token->text, &input[*i], word_len + 1);
	if (lst_add_token(&data->lst_token, token) == -1)
		return (-1);
	*i += word_len;
	return (1);
}

int	super_token(char *input, int *i, t_lexer *data)
{
	t_token	*token;

	data->in_word = false;
	token = NULL;
	token = malloc(sizeof(t_token) * 1);
	if (token == NULL)
		return (-1);
	token->text = malloc(sizeof(char) * 2);
	if (token->text == NULL)
		return (-1);
	ft_strlcpy(token->text, &input[*i], 2);
	token->type = is_special(input[*i]);
	data->token_count++;
	if (lst_add_token(&data->lst_token, token) == -1)
		return (-1);
	*i += 1;
	return (1);
}
