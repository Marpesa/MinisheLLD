/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 04:12:43 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/07 15:07:35 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

char *ft_get_token_type(enum e_token_type type)
{
	if (type == TOKEN_EOF)
		return ("TOKEN_EOF");
	else if (type == TOKEN_WORD)
		return ("TOKEN_WORD");
	else if (type == TOKEN_REDIRECT_IN)
		return ("TOKEN_REDIRECT_IN");
	else if (type == TOKEN_REDIRECT_OUT)
		return ("TOKEN_REDIRECT_OUT");
	else if (type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	else if (type == TOKEN_AND)
		return ("TOKEN_AND");
	else if (type == TOKEN_S_QUOTE)
		return ("TOKEN_S_QUOTE");	
	else if (type == TOKEN_D_QUOTE)
		return ("TOKEN_D_QUOTE");
	else if (type == TOKEN_IGNORE)
		return ("TOKEN_IGNORE");
	else if (type == TOKEN_HEREDOC)
		return ("TOKEN_HEREDOC");
	else if (type == TOKEN_REDIRECT_APPEND)
		return ("TOKEN_REDICRECT_APPEND");
//	else if (type == TOKEN_ENV)
//		return ("TOKEN_ENV");
	return (NULL);
}


void	lst_print_token(t_list *head)
{
	while (head)
	{
		t_token *token = head->content;
		printf("token type: %s\ntoken text: %s\n", ft_get_token_type(token->type), token->text);
		head = head->next;
	}
}
void	ft_lstadd_back_test(t_list **alst, t_list *new)
{
	t_list	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_lstlast(*alst);
			last->next = new;
		}
		else
			*alst = new;
	}
}

t_list	*lst_add_token(t_list *lst_token, void *content)
{
	t_list *new;
	// Don't forget to manage the malloc fail
	new = ft_lstnew(content);
	if (new == NULL)
		return (NULL);
	ft_lstadd_back(&lst_token, new);
	return (lst_token);
}

int	is_special(char c)
{
	if (c == '<')
		return(TOKEN_REDIRECT_IN);
	if (c == '>')
		return(TOKEN_REDIRECT_OUT);
	if (c == '|')
		return(TOKEN_PIPE);
	if (c == '&')
		return(TOKEN_AND);
	if (c == '\'')
		return(TOKEN_S_QUOTE);
	if (c == '\"')
		return(TOKEN_D_QUOTE);
	if (c == '\\' || c == ';' || c == '{' || c == '}')
		return(TOKEN_IGNORE);
	return (0);
}

static void	super_token(char *input, int *i, t_lexer *data) 
{
	t_token *token;

	data->in_word = false;
	token = NULL;
	token = malloc(sizeof(t_token) * 1);
	token->text = malloc(sizeof(char) * 2);
	ft_strlcpy(token->text, &input[*i], 2);
	token->type = is_special(input[*i]);
	data->token_count++;
	data->lst_token = lst_add_token(data->lst_token, token);
	*i += 1;
}

static void token_heredoc(char *input, int *i, t_lexer *data)
{
	t_token *token;
	data->in_word = false;
	token = malloc(sizeof(t_token) * 1);
	token->text = malloc(sizeof(char) * 3);
	ft_strlcpy(token->text, &input[*i], 3);
	token->type = TOKEN_HEREDOC;
	data->token_count++;
	data->lst_token = lst_add_token(data->lst_token, token);
	*i += 2;
}

static void token_redirect_append(char *input, int *i, t_lexer *data)
{
	t_token *token;
	data->in_word = false;
	token = malloc(sizeof(t_token) * 1);
	token->text = malloc(sizeof(char) * 3);
	ft_strlcpy(token->text, &input[*i], 3);
	token->type = TOKEN_REDIRECT_APPEND;
	data->token_count++;
	data->lst_token = lst_add_token(data->lst_token, token);
	*i += 2;
}

void	lexer_data_init(t_lexer *data)
{
	data->token_count = 0;
	data->token_start = 0;
	//data->in_quote = false;
	data->in_word = false;
	data->token = NULL;
	data->lst_token = NULL;
}

static void	token_s_quotes(char *input, int *i, t_lexer *data)
{
	t_token *token;
	int		j;

	token = NULL;
	j = *i + 1;
	while (input[j] != '\'' && input[j])
			j++;
	token = malloc(sizeof(t_token) * 1);
	token->text = malloc(sizeof(char) * (j - *i));
	ft_strlcpy(token->text, &input[*i + 1], (j - *i));
	token->type = TOKEN_S_QUOTE;
	data->token_count++;
	data->lst_token = lst_add_token(data->lst_token, token);
	*i = j + 1;
}

static void	token_d_quotes(char *input, int *i, t_lexer *data)
{
	t_token *token;
	int		j;

	token = NULL;
	j = *i + 1;
	while (input[j] != '"' && input[j])
		j++;
	token = malloc(sizeof(t_token) * 1);
	token->text = malloc(sizeof(char) * (j - *i));
	ft_strlcpy(token->text, &input[*i + 1], (j - *i));
	token->type = TOKEN_D_QUOTE;
	data->token_count++;
	data->lst_token = lst_add_token(data->lst_token, token);
	*i = j + 1;
}

static void	token_word(char *input, int *i, t_lexer *data)
{
	t_token *token;
	int	word_len;
	int	j;
	t_token *previous;
	t_list *lst_previous;

	j = 0;
	word_len = 0;
	token = NULL;
	if (data->in_word == false)
	    data->token_count++;
	data->in_word = true;
    data->token_start = *i;
	j = *i;
	while (input[j] != '\0' && input[j] != ' ' && !is_special(input[j]) && input[j] != '\'' && input[j] != '\"')
		j++;
	word_len = j - *i;
	token = malloc(sizeof(t_token) * 1);
	token->type = TOKEN_WORD;
	lst_previous = ft_lstlast(data->lst_token);
	if (lst_previous != NULL)
	{
		previous = lst_previous->content;
		if (previous->type == TOKEN_HEREDOC)
			token->type = TOKEN_EOF;
	}
	token->text = malloc(sizeof(char) * (word_len + 1));
	ft_strlcpy(token->text, &input[*i], word_len + 1);
	data->lst_token = lst_add_token(data->lst_token, token);
	*i += word_len;
}


t_list	*lexer(char *input)
{
	t_lexer data;
	int i;

	i = 0;
	lexer_data_init(&data);
    while (input[i] != '\0')
	{
        if (input[i] == ' ')
		{
            data.in_word = false; 
			while (input[i] == ' ')
      			i++;
        }
		else if (input[i] == '<' && input[i + 1] == '<')
			token_heredoc(input, &i, &data);
		else if (input[i] == '>' && input[i + 1] == '>')
			token_redirect_append(input, &i, &data);
        else if (input[i] == '"')
			token_d_quotes(input, &i, &data);
		else if (input[i] == '\'')
			token_s_quotes(input, &i, &data);
		else if (input[i] != '\0' && input[i] != ' ' && !is_special(input[i]))
			token_word(input, &i, &data);
        else if ((is_special(input[i])))
			super_token(input, &i, &data);
    }
	return (data.lst_token);
}
