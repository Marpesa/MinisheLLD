/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 04:12:43 by gle-mini          #+#    #+#             */
/*   Updated: 2022/12/20 07:42:34 by gle-mini         ###   ########.fr       */
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
	return (0);
}

static void	super_token(char *input, int *i, t_lexer *data) 
{
	data->in_word = false; 
	// Mark the end of the previous token
	if (*i > data->token_start || *i == 0)
		data->token_count++;
	else {
	
		// Create a new token for the special character
		if (input[*i] == '<') {
			//tokens[token_count].text = "<";
			//tokens[token_count].type = TOKEN_REDIRECT_IN;
		}
		else if (input[*i] == '>') {
			//tokens[token_count].text = ">";
			//tokens[token_count].type = TOKEN_REDIRECT_OUT;
		}
		else if (input[*i] == '|') {
			//tokens[token_count].text = "|";
			//tokens[token_count].type = TOKEN_PIPE;
		}
		else if (input[*i] == '&') {
			//tokens[token_count].text = "&";
			//tokens[token_count].type = TOKEN_BACKGROUND;
		}
		data->token_count++;
	}
	*i += 1; 
	// Start the next token after the special character
	data->token_start = *i;
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

static void	token_quotes(int *i, t_lexer *data)
{
    data->in_word = false; 
	if (data->in_quote == false)
	{
            data->token_count++;
          	data->token_start = *i;
	}
    data->in_quote = !data->in_quote;

	*i += 1;
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

	ft_strlcpy(token->text, &input[*i], word_len + 1);
	token->type = TOKEN_WORD;
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
			token_quotes(&i, &data);
        
        else if ((input[i] == '<' || input[i] == '>' || input[i] == '|' || input[i] == '&') && data.in_quote == false)
			super_token(input, &i, &data);
    }
	printf("final print\n");
	lst_print_token(data.lst_token);
	return (data.token_count);
}

