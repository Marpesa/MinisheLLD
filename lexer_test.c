#include "minisheLLD.h"
#include <stdarg.h>

t_token *ft_tokencpy(char *str, t_token_type token_type)
{
	t_token *token;

	token = NULL;
	token = malloc(sizeof(t_token) * 1);
	token->text = NULL;
	token->text = malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_strlcpy(token->text, str, ft_strlen(str) + 1);
	token->type = token_type;
	return (token);
}

t_list *create_lst_token(int size, ...)
{
	t_list *lst_test;
	int		i;
	va_list args;

	i = 0;	
	lst_test = NULL;
	va_start(args, size);
	while (i < size)
	{
		lst_test = lst_add_token(lst_test, ft_tokencpy(va_arg(args, char *), va_arg(args, t_token_type)));
		i++;
	}
	va_end(args);
	return (lst_test);
}

int ft_lst_size(t_list *lst)
{
	int i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	lst_compare(t_list	*lst_expected, t_list *lst_result)
{
	t_token *tkn_expected;
	t_token *tkn_result;

	if (ft_lst_size(lst_expected) != ft_lst_size(lst_result))
	{
		printf("lst size expected: %d | lst size result %d\n", ft_lst_size(lst_expected), ft_lst_size(lst_result));
		return (false);
	}
	while (lst_expected != NULL)
	{
		tkn_expected = lst_expected->content;
		tkn_result = lst_result->content;
		if (ft_strncmp(tkn_expected->text, tkn_result->text, ft_strlen(tkn_expected->text)))
		{
			printf("expected: %s | result: %s\n", tkn_expected->text, tkn_result->text);
			return (false);
		}
		if (tkn_expected->type != tkn_result->type)
		{
			printf("tokentype expected: %s | tokentype result: %s\n", ft_get_token_type(tkn_expected->type), ft_get_token_type(tkn_result->type));
			return (false);
		}
		lst_expected = lst_expected->next;
		lst_result = lst_result->next;
	}
	return (true);
}

void	lexer_test(t_list *lst_expected, t_list *lst_result)
{

	if (lst_compare(lst_expected, lst_result))
		printf(_BOLD _BLUE_LLD "OK\n" _END);
	else
		printf(_BOLD _ORANGE "KO\n" _END);
}

int main(void)
{
	lexer_test(create_lst_token(2, "hello", TOKEN_WORD, "$USER", TOKEN_S_QUOTE), 
			lexer("hello'$USER'"));
	lexer_test(create_lst_token(2, "hello", TOKEN_WORD, "$USER", TOKEN_S_QUOTE), 
			lexer("hello '$USER'"));
	lexer_test(create_lst_token(2, "hello", TOKEN_WORD, "$USER", TOKEN_D_QUOTE), 
			lexer("hello \"$USER\""));
	lexer_test(create_lst_token(4, "hello", TOKEN_WORD, "$USER", TOKEN_S_QUOTE, "<<", TOKEN_HEREDOC, "Louise", TOKEN_EOF), 
			lexer("hello'$USER' << Louise"));
	lexer_test(create_lst_token(4, "hello", TOKEN_WORD, "$USER", TOKEN_S_QUOTE, "<<", TOKEN_HEREDOC, "Louise", TOKEN_EOF), 
			lexer("hello '$USER' << Louise"));
	lexer_test(create_lst_token(4, "HELLO", TOKEN_WORD, "JE", TOKEN_WORD, "SUIS", TOKEN_WORD, "BEAU", TOKEN_WORD), 
			lexer("HELLO JE SUIS BEAU"));
	lexer_test(create_lst_token(4, "hello", TOKEN_WORD, "$USER", TOKEN_S_QUOTE, "$USER", TOKEN_D_QUOTE, "$USER", TOKEN_WORD), 
			lexer("hello'$USER'\"$USER\"$USER"));
	lexer_test(create_lst_token(4, "hello", TOKEN_WORD, "'$USER'", TOKEN_D_QUOTE, "$USER", TOKEN_WORD, "$USER", TOKEN_D_QUOTE), 
			lexer("hello\"'$USER'\"$USER\"$USER\""));
	lexer_test(create_lst_token(4, "hello", TOKEN_WORD, "'$USER'", TOKEN_D_QUOTE, "$USER", TOKEN_WORD, "$USER", TOKEN_D_QUOTE), 
			lexer("hello \"'$USER'\"$USER\"$USER\""));
	lexer_test(create_lst_token(5, "|", TOKEN_PIPE, "|", TOKEN_PIPE, "|", TOKEN_PIPE, "|", TOKEN_PIPE, "|", TOKEN_PIPE), 
			lexer("|||||"));

	return (0);
}
