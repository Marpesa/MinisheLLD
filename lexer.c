/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 04:12:43 by gle-mini          #+#    #+#             */
/*   Updated: 2022/12/18 05:49:32 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <stdio.h>
#include <ctype.h>

typedef enum {
	false,
	true
} bool;

enum TokenType {
  TOKEN_EOF,          // End of file
  TOKEN_WORD,         // A word
  TOKEN_REDIRECT_IN,  // < redirection
  TOKEN_REDIRECT_OUT, // > redirection
  TOKEN_PIPE,         // | symbol
  TOKEN_AND,   // & symbol
  TOKEN_QUOTE		  // " symbol
};

struct Token {
  enum TokenType type;
  char *text;
};

typedef struct s_lexer {
    int token_count;
	int	token_start;
    bool in_quote;
	bool in_word;
	int i;
	t_list lst_token;
} t_lexer;

static int is_special(char c)
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

static void super_token(char *input, int *i, t_lexer *data) 
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

void lexer_data_init(t_lexer *data)
{
	data->token_count = 0;
	data->token_start = 0;
	data->in_quote = false;
	data->in_word = false;

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
	int	word_len;
	int	j;

	word_len = 0;
	if (data->in_word == false)
	    data->token_count++;
	data->in_word = true;
    data->token_start = *i;
	j = *i;
	while (input[j] != '\0' && input[j] != ' ' && !is_special(input[j]) && input[j] != '"' && input[j] != '\'')
		j++;
	word_len = j - 1;
	printf("len = %d\n", word_len); 
	*i += 1;
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
      		i++;	
        }
		else if (input[i] != '\0' && input[i] != ' ' && !is_special(input[i]) && input[i] != '"' && input[i] != '\'' && data.in_quote == false)
			token_word(input, &i, &data);
	    
        else if (input[i] == '"' || input[i] == '\'') 
			token_quotes(&i, &data);
        
        else if ((input[i] == '<' || input[i] == '>' || input[i] == '|' || input[i] == '&') && data.in_quote == false)
			super_token(input, &i, &data);
        else 
            i++;
    }
	return (data.token_count);
}

int main(int argc, char **argv)
{
	if (argc <= 1)
		return (1);
	printf("nb tokens: %d\n", lexer(argv[1]));
	return (0);
}
