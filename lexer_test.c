#include "minisheLLD.h"
#include <stdarg.h>

t_token *ft_tokencpy(char *str, t_token_type token_type)
{
	t_token *token;

	token = NULL;
	token = malloc(sizeof(t_token) * 1);
	token->text = NULL;
	token->text = malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_strlcpy(token->text, str, ft_strlen(str));
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

int	lst_compare(t_list	*lst_test, t_list *lst_result)
{
	t_token *tkn_test;
	t_token *tkn_result;
	if (ft_lst_size(lst_test) != ft_lst_size(lst_result))
	{
		printf("lst size expected: %d | lst size result %d\n", ft_lst_size(lst_test), ft_lst_size(lst_result));
		return (false);
	}
	while (lst_test != NULL)
	{
		tkn_test = lst_test->content;
		tkn_result = lst_result->content;
		if (ft_strncmp(tkn_test->text, tkn_result->text, ft_strlen(tkn_test->text)))
		{
			printf("expected: %s | result: %s\n", tkn_test->text, tkn_result->text);
			return (false);
		}
		if (tkn_test->type != tkn_result->type)
		{
			printf("tokentype expected: %d | tokentype result: %d\n", tkn_test->type, tkn_result->type);
			return (false);
		}
		lst_test = lst_test->next;
		lst_result = lst_result->next;
	}
	return (true);
}

int main(void)
{
	t_list *lst_test1;
	t_list *lst_test2;

	lst_test1 = NULL;
	lst_test2 = NULL;
	lst_test1 = create_lst_token(1, "hell'$USER'", TOKEN_WORD);
	//lst_print_token(lst_test);
	if (lst_compare(lst_test1, lexer("hello'$USER'")))
		printf(_BOLD _BLUE_LLD "OK\n" _END);
	else
		printf(_BOLD _ORANGE "KO\n" _END);

return (0);
}
