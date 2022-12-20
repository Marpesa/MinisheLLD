/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 04:12:43 by gle-mini          #+#    #+#             */
/*   Updated: 2022/12/20 11:12:53 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"


void	lst_print_token(t_list *head)
{
	printf("TEST\n");
	//if (head == NULL)
	while (head)
	{
		//printf("TEST\n");
		t_token *token = head->content;
		printf("token type: %d\ntoken text: %s\n", token->type, token->text);
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



static int	is_special(char c)
{
	if (c == '<')
		return(TOKEN_REDIRECT_IN);
	if (c == '>')
		return(TOKEN_REDIRECT_OUT);
	if (c == '|')
		return(TOKEN_PIPE);
	if (c == '&')
		return(TOKEN_AND);
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

void	lexer_data_init(t_lexer *data)
{
	data->token_count = 0;
	data->token_start = 0;
	data->in_quote = false;
	data->in_word = false;
	data->token = NULL;
	data->lst_token = NULL;
}

static void	token_quotes(char *input, int *i, t_lexer *data)
{
	t_token *token;
	int		j;
	t_bool	closed;

	closed = false;
	token = NULL;
	j = *i + 1;
	char quote;
	quote = input[*i];
	if (input[*i] == quote)
	{
		while (input[j] != quote && input[j])
		{
			if (input[j] == quote)
				closed = true;
			j++;
		}
	}
	if (input[j] == '\0' && closed == false)
		printf(_ORANGE2 _BOLD"Quote not terminated, learn how to type...\n" _END);
	token = malloc(sizeof(t_token) * 1);
	token->text = malloc(sizeof(char) * (j - *i));
	ft_strlcpy(token->text, &input[*i + 1], (j - *i));
	token->type = TOKEN_QUOTE;
	data->token_count++;
	data->lst_token = lst_add_token(data->lst_token, token);
	*i = j + 1;
}

static void	token_word(char *input, int *i, t_lexer *data)
{
	t_token *token;
	int	word_len;
	int	j;

	j = 0;
	word_len = 0;
	token = NULL;
	if (data->in_word == false)
	    data->token_count++;
	data->in_word = true;
    data->token_start = *i;
	j = *i;
	while (input[j] != '\0' && input[j] != ' ' && !is_special(input[j]) && input[j] != '"' && input[j] != '\'')
		j++;
	word_len = j - *i;
	
	token = malloc(sizeof(t_token) * 1);
	token->text = malloc(sizeof(char) * j + 1);
	if (input[*i] == '$')
		token->type = TOKEN_ENV;
	else
		token->type = TOKEN_WORD;
	ft_strlcpy(token->text, &input[*i], word_len + 1);
	//printf("token = %s, len: %d, input: %c, i: %d\n", token->text, word_len, input[*i], *i);
	data->lst_token = lst_add_token(data->lst_token, token);
	*i += word_len;
}

int	lexer(char *input)
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
		else if (input[i] != '\0' && input[i] != ' ' && !is_special(input[i]) && input[i] != '"' && input[i] != '\'' && data.in_quote == false)
			token_word(input, &i, &data);
	    
        else if (input[i] == '"' || input[i] == '\'')
			token_quotes(input, &i, &data);
        
        else if ((is_special(input[i])) && data.in_quote == false)
			super_token(input, &i, &data);
    }
	printf("final print\n");
	lst_print_token(data.lst_token);
	return (data.token_count);
}

