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
/*
int	lexer(char *input)
{
	//t_list *tokens;
	int i;
	int token_count;

	i = 0;
	token_count = 0;
	while (input[i] != '\0')
	{
		while (input[i] != '\0' && input[i] == ' ')
			i++;
		while (is_special(input[i]))
		{
			token_count++;
			i++;
		}
		if (input[i] != '\0' && !is_special(input[i]) && input[i] != ' ')
		{
			while (input[i] != '\0' && !is_special(input[i]) && input[i] != ' ')
			{
				i++;
			}
			token_count++;
		}
	}
	return (token_count);
}
*/


int	lexer(char *input)
{
    int token_count;
	int	token_start;
    bool in_quote;
	bool in_word;
	int i;

	i = 0;
	token_count = 0;
	token_start = 0;
	in_quote = false;
	in_word = false;
    while (input[i] != '\0')
	{ 
	        // Check for whitespace
        if (input[i] == ' ')
		{
            in_word = false; 
      		i++;	
        }
		else if (input[i] != '\0' && input[i] != ' ' && !is_special(input[i]) && input[i] != '"' && input[i] != '\'' && in_quote == false)
		{
			if (in_word == false)
			    token_count++;
			in_word = true;
            token_start = i;
			i++;
			
		}
		    
        // Check for quotes
        else if (input[i] == '"' || input[i] == '\'') {
            // Toggle the quote flag
            in_word = false; 
			if (in_quote == false)
			{
                token_count++;
            	token_start = i;
			}
            in_quote = !in_quote;
			i++;
        }
        
        // Check for redirections and pipes
        else if ((input[i] == '<' || input[i] == '>' || input[i] == '|' || input[i] == '&') && in_quote == false)
		{
            in_word = false; 
            // Mark the end of the previous token
            if (i > token_start || i == 0) {

				printf("char3: %c\n", input[i]);
                token_count++;
            }
			else {
            
				// Create a new token for the special character
				if (input[i] == '<') {
					//tokens[token_count].text = "<";
					//tokens[token_count].type = TOKEN_REDIRECT_IN;
				}
				else if (input[i] == '>') {
					//tokens[token_count].text = ">";
					//tokens[token_count].type = TOKEN_REDIRECT_OUT;
				}
				else if (input[i] == '|') {
					//tokens[token_count].text = "|";
					//tokens[token_count].type = TOKEN_PIPE;
				}
				else if (input[i] == '&') {
					//tokens[token_count].text = "&";
					//tokens[token_count].type = TOKEN_BACKGROUND;
				}
				token_count++;
			}
            i++; 
            // Start the next token after the special character
            token_start = i;
        }   
        // Otherwise, add the character to the current token
        else {
            i++;
        }
    }
	return (token_count);
}

/*
int lexer(char *input, struct Token *tokens) {
    int token_count = 0;
    char *token_start = input;
    bool in_quote = false;
    
    while (*input != '\0') {
        // Check for whitespace
        if (*input == ' ' || *input == '\t' || *input == '\n') {
            // If we're in a quoted string, add the whitespace to the token
            if (in_quote) {
                input++;
                continue;
            }
            
            // Otherwise, mark the end of the token and move on to the next one
            if (input > token_start) {
                tokens[token_count].text = token_start;
                tokens[token_count].type = TOKEN_WORD;
                token_count++;
            }
            token_start = input + 1;
			input++;	
			printf("input: %d\n", *input);
			printf("input: %d\n", *(input + 1));
        }
        
        // Check for quotes
        else if (*input == '"' || *input == '\'') {
            // Toggle the quote flag
            in_quote = !in_quote;
            
            // If we're starting a quoted string, set the token start
            if (in_quote) {
                token_start = input + 1;
                tokens[token_count].type = TOKEN_QUOTE;
            }
            // Otherwise, mark the end of the quoted string
            else {
                tokens[token_count].text = token_start;
                token_count++;
            }
        }
        
        // Check for redirections and pipes
        else if (*input == '<' || *input == '>' || *input == '|' || *input == '&')
		{
            // Mark the end of the previous token
            if (input > token_start) {
                tokens[token_count].text = token_start;
                tokens[token_count].type = TOKEN_WORD;
                token_count++;
            }
            
            // Create a new token for the special character
            if (*input == '<') {
                tokens[token_count].text = "<";
                tokens[token_count].type = TOKEN_REDIRECT_IN;
            }
            else if (*input == '>') {
                tokens[token_count].text = ">";
                tokens[token_count].type = TOKEN_REDIRECT_OUT;
            }
            else if (*input == '|') {
                tokens[token_count].text = "|";
                tokens[token_count].type = TOKEN_PIPE;
            }
            else if (*input == '&') {
                tokens[token_count].text = "&";
                tokens[token_count].type = TOKEN_BACKGROUND;
            }
            token_count++;
            
            // Start the next token after the special character
            token_start = input + 1;
        }
        
        // Otherwise, add the character to the current token
        else {
            input++;
        }
    }
   
	// Mark the end of the final token
    if (input > token_start) {
        tokens[token_count].text = token_start;
        tokens[token_count].type = TOKEN_WORD;
        token_count++;
    }
	return (token_count);
}
*/

int main(int argc, char **argv)
{
	if (argc <= 1)
		return (1);
	printf("nb tokens: %d\n", lexer(argv[1]));
	return (0);
}
