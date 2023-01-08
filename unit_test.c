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

void free_token(void *content)
{
	t_token *token;

	token = content;
	free(token->text);
	token->text = NULL;
	free(token);
	token = NULL;
}

void	test(t_list *lst_expected, t_list *lst_result)
{

	if (lst_compare(lst_expected, lst_result))
		printf(_BOLD _BLUE_LLD "OK\n" _END);
	else
		printf(_BOLD _ORANGE "KO\n" _END);
	ft_lstclear(&lst_expected, free_token);
	ft_lstclear(&lst_result, free_token);
}

void static lexer_test_d_quote()
{
	test(create_lst_token(2, "hello", TOKEN_WORD, "$USER", TOKEN_S_QUOTE), 
		lexer("hello'$USER'"));
	test(create_lst_token(2, "hello", TOKEN_WORD, "$USER", TOKEN_S_QUOTE), 
		lexer("hello '$USER'"));
	test(create_lst_token(4, "hello", TOKEN_WORD, "'$USER'", TOKEN_D_QUOTE, "$USER", TOKEN_WORD, "$USER", TOKEN_D_QUOTE), 
		lexer("hello\"'$USER'\"$USER\"$USER\""));
	test(create_lst_token(4, "hello", TOKEN_WORD, "'$USER'", TOKEN_D_QUOTE, "$USER", TOKEN_WORD, "$USER", TOKEN_D_QUOTE), 
		lexer("hello \"'$USER'\"$USER\"$USER\""));
	test(create_lst_token(1, "'$USER'", TOKEN_D_QUOTE), 
		lexer("\"'$USER'\""));
}

void static lexer_test_s_quote()
{
	test(create_lst_token(2, "hello", TOKEN_WORD, "$USER", TOKEN_D_QUOTE), 
		lexer("hello \"$USER\""));
	test(create_lst_token(4, "hello", TOKEN_WORD, "$USER", TOKEN_S_QUOTE, "<<", TOKEN_HEREDOC, "Louise", TOKEN_EOF), 
		lexer("hello'$USER' << Louise"));
	test(create_lst_token(4, "hello", TOKEN_WORD, "$USER", TOKEN_S_QUOTE, "$USER", TOKEN_D_QUOTE, "$USER", TOKEN_WORD), 
		lexer("hello'$USER'\"$USER\"$USER"));
	test(create_lst_token(1, "\"$USER\"", TOKEN_S_QUOTE), 
		lexer("'\"$USER\"'"));
}

void static lexer_test_heredoc()
{
	test(create_lst_token(4, "hello", TOKEN_WORD, "$USER", TOKEN_S_QUOTE, "<<", TOKEN_HEREDOC, "Louise", TOKEN_EOF), 
		lexer("hello'$USER' <<Louise"));
	test(create_lst_token(4, "hello", TOKEN_WORD, "$USER", TOKEN_S_QUOTE, "<<", TOKEN_HEREDOC, "|", TOKEN_PIPE), 
		lexer("hello'$USER' << |"));
}

void static lexer_test_word()
{
	test(create_lst_token(4, "HELLO", TOKEN_WORD, "JE", TOKEN_WORD, "SUIS", TOKEN_WORD, "BEAU", TOKEN_WORD), 
		lexer("HELLO JE SUIS BEAU"));
}

void static lexer_test_pipe()
{
	test(create_lst_token(5, "|", TOKEN_PIPE, "|", TOKEN_PIPE, "|", TOKEN_PIPE, "|", TOKEN_PIPE, "|", TOKEN_PIPE), 
		lexer("|||||"));

}

void static	expand_test_pipe(char **env)
{
	t_list *lst;

	lst = create_lst_token(5, "|", TOKEN_PIPE, "|", TOKEN_PIPE, "|", TOKEN_PIPE, "|", TOKEN_PIPE, "|", TOKEN_PIPE);
	ft_expand(lst, env);
	test(create_lst_token(5, "|", TOKEN_PIPE, "|", TOKEN_PIPE, "|", TOKEN_PIPE, "|", TOKEN_PIPE, "|", TOKEN_PIPE), lst);
}

void static expand_test_word(char **env)
{
	t_list *lst;

	lst = create_lst_token(1, "hello", TOKEN_WORD);
	ft_expand(lst, env);
	test(create_lst_token(1, "hello", TOKEN_WORD), lst);

	lst = create_lst_token(2, "hello", TOKEN_WORD, "hello", TOKEN_WORD);
	ft_expand(lst, env);
	test(create_lst_token(2, "hello", TOKEN_WORD, "hello", TOKEN_WORD), lst);
}

void static	expand_test_env_var(char **env)
{	
	t_list *lst;

	lst = create_lst_token(1, "$USER", TOKEN_WORD);
	ft_expand(lst, env);
	test(create_lst_token(1, "gle-mini", TOKEN_WORD), lst);

	lst = create_lst_token(1, "hello$USER", TOKEN_WORD);
	ft_expand(lst, env);
	test(create_lst_token(1, "hellogle-mini", TOKEN_WORD), lst);

	lst = create_lst_token(1, "$USERRR", TOKEN_WORD);
	ft_expand(lst, env);
	test(create_lst_token(1, "", TOKEN_WORD), lst);

	lst = create_lst_token(1, "$$USER", TOKEN_WORD);
	ft_expand(lst, env);
	test(create_lst_token(1, "gle-mini", TOKEN_WORD), lst);
}

//void static expand_test_word()

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	lexer_test_s_quote();
	lexer_test_d_quote();
	lexer_test_heredoc();
	lexer_test_word();
	lexer_test_pipe();
	//Pense a ajouter un cas pour NULL et pour '\0'
	printf("-----------------------------EXPAND---------------------\n");
	expand_test_word(env);
	expand_test_pipe(env);
	printf("--------------------------------------------------------\n");
	expand_test_env_var(env);
	return (0);
}
