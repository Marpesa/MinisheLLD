#include "minisheLLD.h"

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
		char *str = va_arg(args, char *);
		lst_test = lst_add_token(lst_test, ft_tokencpy(str, va_arg(args, t_token_type)));
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

t_bool	lst_compare(t_list	*lst_expected, t_list *lst_result)
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

void	test(t_list *lst_expected_lexer, t_list *lst_expected_expand, char *test_command, char **env)
{
	t_list *lst_test;
	printf("Command tested: %s\n", test_command);	
	printf("-------------LEXER---------------\n");
	lst_test = lexer(test_command);
	if (lst_compare(lst_expected_lexer, lst_test))
		printf(_BOLD _BLUE_LLD "OK\n" _END);
	else
	{
		lst_print_token(lst_test);
		printf(_BOLD _ORANGE "KO\n" _END);
	}
	ft_expand(lst_test, env);
	printf("-------------EXPAND---------------\n");
	if (lst_compare(lst_expected_expand, lst_test))
		printf(_BOLD _BLUE_LLD "OK\n" _END);
	else
	{
		lst_print_token(lst_test);
		printf(_BOLD _ORANGE "KO\n" _END);
	}
	ft_lstclear(&lst_expected_lexer, free_token);
	ft_lstclear(&lst_expected_expand, free_token);
	ft_lstclear(&lst_test, free_token);
	printf("_____________________________________________________\n\n");
}

static void test_d_quote(char **env)
{
	printf("=======================TEST_D_QUOTE=============================\n\n");
	test(create_lst_token(1, "hello'$USER'", TOKEN_WORD), 
		create_lst_token(1, "hello$USER", TOKEN_WORD),
		"hello'$USER'", env);
	test(create_lst_token(2, "cat", TOKEN_WORD, "hello'$USER'", TOKEN_WORD), 
		create_lst_token(2, "cat", TOKEN_WORD, "hello$USER", TOKEN_WORD),
		"cat hello'$USER'", env);
	test(create_lst_token(2, "hello", TOKEN_WORD, "'$USER'", TOKEN_WORD), 
		create_lst_token(2, "hello", TOKEN_WORD, "$USER", TOKEN_WORD),
		"hello '$USER'", env);
	test(create_lst_token(3, "cat", TOKEN_WORD, "hello", TOKEN_WORD, "'$USER'", TOKEN_WORD), 
		create_lst_token(3, "cat", TOKEN_WORD, "hello", TOKEN_WORD, "$USER", TOKEN_WORD), 
		"cat hello '$USER'", env);
	test(create_lst_token(3, "cat", TOKEN_WORD, "hello", TOKEN_WORD, "'$USER'", TOKEN_WORD), 
		create_lst_token(3, "cat", TOKEN_WORD, "hello", TOKEN_WORD, "$USER", TOKEN_WORD), 
		"cat     \thello             '$USER'", env);
	test(create_lst_token(1, "hello\"'$USER'\"$USER\"$USER\"", TOKEN_WORD),
		create_lst_token(1, "hello'gle-mini'gle-minigle-mini", TOKEN_WORD),
		"hello\"'$USER'\"$USER\"$USER\"", env);
		//create_lst_token(1, "hello$USERgle-minigle-mini", TOKEN_WORD),
	test(create_lst_token(2, "hello", TOKEN_WORD, "\"'$USER'\"$USER\"$USER\"", TOKEN_WORD),
		create_lst_token(2, "hello", TOKEN_WORD, "'gle-mini'gle-minigle-mini", TOKEN_WORD),
		"hello \"'$USER'\"$USER\"$USER\"", env);
	test(create_lst_token(3, "cat", TOKEN_WORD, "hello", TOKEN_WORD, "\"'$USER'\"$USER\"$USER\"", TOKEN_WORD),
		create_lst_token(3, "cat", TOKEN_WORD, "hello", TOKEN_WORD, "'gle-mini'gle-minigle-mini", TOKEN_WORD),
		"cat hello \"'$USER'\"$USER\"$USER\"", env);
	test(create_lst_token(1, "\"'$USER'\"", TOKEN_WORD),
		create_lst_token(1, "'gle-mini'", TOKEN_WORD),
		"\"'$USER'\"", env);
	test(create_lst_token(1, "$\"USER\"", TOKEN_WORD),
		create_lst_token(1, "$USER", TOKEN_WORD),
		"$\"USER\"", env);
	test(create_lst_token(2, "echo", TOKEN_WORD, "hello'hello'", TOKEN_WORD),
		create_lst_token(2, "echo", TOKEN_WORD, "hellohello", TOKEN_WORD),
		"echo hello'hello'", env);

	test(create_lst_token(2, "echo", TOKEN_WORD, "hello\"LOUISE'$USER'\"$USER\"$USER\"", TOKEN_WORD),
		create_lst_token(2, "echo", TOKEN_WORD, "helloLOUISE'gle-mini'gle-minigle-mini", TOKEN_WORD),
		"echo hello\"LOUISE'$USER'\"$USER\"$USER\"", env);

	test(create_lst_token(2, "echo", TOKEN_WORD, "\"\"hello", TOKEN_WORD),
		create_lst_token(2, "echo", TOKEN_WORD, "hello", TOKEN_WORD),
		"echo \"\"hello", env);
}

static void test_s_quote(char **env)
{
	printf("=======================TEST_S_QUOTE=============================\n\n");
	test(create_lst_token(2, "hello", TOKEN_WORD, "\"$USER\"", TOKEN_WORD),
		create_lst_token(2, "hello", TOKEN_WORD, "gle-mini", TOKEN_WORD),
		"hello \"$USER\"", env);
	test(create_lst_token(3, "cat", TOKEN_WORD, "hello", TOKEN_WORD, "\"$USER\"", TOKEN_WORD),
		create_lst_token(3, "cat", TOKEN_WORD, "hello", TOKEN_WORD, "gle-mini", TOKEN_WORD),
		"cat hello \"$USER\"", env);
	test(create_lst_token(3, "hello'$USER'", TOKEN_WORD, "<<", TOKEN_HEREDOC, "Louise", TOKEN_WORD),
		create_lst_token(3, "hello$USER", TOKEN_WORD, "<<", TOKEN_HEREDOC, "Louise", TOKEN_LIM),
		"hello'$USER' << Louise", env);
	test(create_lst_token(1, "hello'$USER'\"$USER\"$USER", TOKEN_WORD),
		create_lst_token(1, "hello$USERgle-minigle-mini", TOKEN_WORD),
		"hello'$USER'\"$USER\"$USER", env);
	test(create_lst_token(1, "'\"$USER\"'", TOKEN_WORD),
		create_lst_token(1, "\"$USER\"", TOKEN_WORD),
		"'\"$USER\"'", env);
	test(create_lst_token(2, "cat", TOKEN_WORD, "\"$USER\"", TOKEN_WORD),
		create_lst_token(2, "cat", TOKEN_WORD, "gle-mini", TOKEN_WORD),
		"cat \"$USER\"", env);
	test(create_lst_token(1, "$'USER'", TOKEN_WORD),
		create_lst_token(1, "USER", TOKEN_WORD),
		"$'USER'", env);
	test(create_lst_token(2, "echo", TOKEN_WORD, "hello'hello'", TOKEN_WORD),
		create_lst_token(2, "echo", TOKEN_WORD, "hellohello", TOKEN_WORD),
		"echo hello'hello'", env);
}


static void test_heredoc(char **env)
{
	test(create_lst_token(3, "hello'$USER'", TOKEN_WORD, "<<", TOKEN_HEREDOC, "Louise", TOKEN_WORD),
		create_lst_token(3, "hello$USER", TOKEN_WORD, "<<", TOKEN_HEREDOC, "Louise", TOKEN_LIM),
		"hello'$USER' <<Louise", env);
	test(create_lst_token(4, "cat", TOKEN_WORD, "hello'$USER'", TOKEN_WORD, "<<", TOKEN_HEREDOC, "Louise", TOKEN_WORD),
		create_lst_token(4, "cat", TOKEN_WORD, "hello$USER", TOKEN_WORD, "<<", TOKEN_HEREDOC, "Louise", TOKEN_LIM),
		"cat hello'$USER' <<Louise", env);
	test(create_lst_token(3, "hello'$USER'", TOKEN_WORD, "<<", TOKEN_HEREDOC, "|", TOKEN_PIPE),
		create_lst_token(3, "hello$USER", TOKEN_WORD, "<<", TOKEN_HEREDOC, "|", TOKEN_PIPE),
		"hello'$USER' << |", env);
	test(create_lst_token(3, "hello'$USER'", TOKEN_WORD, "<<", TOKEN_HEREDOC, "|", TOKEN_PIPE),
		create_lst_token(3, "hello$USER", TOKEN_WORD, "<<", TOKEN_HEREDOC, "|", TOKEN_PIPE),
		"hello'$USER' <<|", env);
	test(create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "|", TOKEN_PIPE),
		create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "|", TOKEN_PIPE),
		"cat << |", env);
	test(create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "EOF", TOKEN_WORD),
		create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "EOF", TOKEN_LIM),
		"cat << EOF", env);
	test(create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "\"\"EOF", TOKEN_WORD),
		create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "\"\"EOF", TOKEN_LIM),
		"cat << \"\"EOF", env);
	test(create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "E\"\"OF", TOKEN_WORD),
		create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "E\"\"OF", TOKEN_LIM),
		"cat << E\"\"OF", env);
	test(create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "\"EOF\"", TOKEN_WORD),
		create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "\"EOF\"", TOKEN_LIM),
		"cat << \"EOF\"", env);
	test(create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "\"EOF\"\"EOF\"", TOKEN_WORD),
		create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "\"EOF\"\"EOF\"", TOKEN_LIM),
		"cat << \"EOF\"\"EOF\"", env);
	test(create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "EOF''", TOKEN_WORD),
		create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "EOF''", TOKEN_LIM),
		"cat << EOF''", env);
	test(create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "''EOF", TOKEN_WORD),
		create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "''EOF", TOKEN_LIM),
		"cat << ''EOF", env);
	test(create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "E''OF", TOKEN_WORD),
		create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "E''OF", TOKEN_LIM),
		"cat << E''OF", env);
	test(create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "'EOF''EOF'", TOKEN_WORD),
		create_lst_token(3, "cat", TOKEN_WORD, "<<", TOKEN_HEREDOC, "'EOF''EOF'", TOKEN_LIM),
		"cat << 'EOF''EOF'", env);
}

static void test_word(char **env)
{
	test(create_lst_token(4, "HELLO", TOKEN_WORD, "JE", TOKEN_WORD, "SUIS", TOKEN_WORD, "BEAU", TOKEN_WORD),
		create_lst_token(4, "HELLO", TOKEN_WORD, "JE", TOKEN_WORD, "SUIS", TOKEN_WORD, "BEAU", TOKEN_WORD),
		"HELLO JE SUIS BEAU", env);
test(create_lst_token(2, "cat", TOKEN_WORD, "\"'$USER'\"", TOKEN_WORD),
	create_lst_token(2, "cat", TOKEN_WORD, "'gle-mini'", TOKEN_WORD),
	"cat \"'$USER'\"", env);
test(create_lst_token(2, "echo", TOKEN_WORD, "'\"$USER\"'", TOKEN_WORD),
	create_lst_token(2, "echo", TOKEN_WORD, "\"$USER\"", TOKEN_WORD),
	"echo '\"$USER\"'", env);
test(create_lst_token(2, "echo", TOKEN_WORD, "'$\"$USER\"'", TOKEN_WORD),
	create_lst_token(2, "echo", TOKEN_WORD, "$\"$USER\"", TOKEN_WORD),
	"echo '$\"$USER\"'", env);
test(create_lst_token(2, "echo", TOKEN_WORD, "\"$'$USER'\"", TOKEN_WORD),
	create_lst_token(2, "echo", TOKEN_WORD, "$'gle-mini'", TOKEN_WORD),
	"echo \"$'$USER'\"", env);
test(create_lst_token(2, "echo", TOKEN_WORD, "$'$USER'", TOKEN_WORD),
	create_lst_token(2, "echo", TOKEN_WORD, "$USER", TOKEN_WORD),
	"echo $'$USER'", env);
test(create_lst_token(2, "echo", TOKEN_WORD, "$", TOKEN_WORD),
	create_lst_token(2, "echo", TOKEN_WORD, "$", TOKEN_WORD),
	"echo $", env);
test(create_lst_token(2, "echo", TOKEN_WORD, "$$", TOKEN_WORD),
	create_lst_token(2, "echo", TOKEN_WORD, "$$", TOKEN_WORD),
	"echo $$", env);
}


/*

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

	lst = create_lst_token(1, "gle-miniwp", TOKEN_WORD);
	ft_expand(lst, env);
	test(create_lst_token(3, "$USER", TOKEN_WORD, "\"w\"", TOKEN_WORD, "p", TOKEN_WORD), lst);
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
*/

//void static expand_test_word()

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	test_d_quote(env);
	test_s_quote(env);
	test_heredoc(env);
	test_word(env);
	test_syntaxe_error(env);
	/*
	lexer_test_pipe();
	//Pense a ajouter un cas pour NULL et pour '\0'
	printf("-----------------------------EXPAND---------------------\n");
	expand_test_word(env);

	printf("--------------------------------------------------------\n");
	expand_test_env_var(env);
	*/




	/*-----------TEST-HEREDOC-------------*/
	//cat << EOF""
	//cat << ""EOF
	//cat << E""OF	
	//cat << "EOF"
	//cat << "EOF""EOF"
	
	//cat << EOF''
	//cat << ''EOF
	//cat << E''OF
	//cat << 'EOF''EOF'
	
	/*
	 gle-mini@e1r2p12:~/MinisheLLD$ cat <<prout
	> je suis $USER
	> prout
	je suis gle-mini
	gle-mini@e1r2p12:~/MinisheLLD$ cat <<"prout"
	> je suis $USER
	> prout
	je suis $USER
	gle-mini@e1r2p12:~/MinisheLLD$
	*/

/*
	t_list		*lst_command_expected;
	t_list		*lst_command_test;
	t_bool		result;

	lst_command_expected = NULL;
	lst_command_test = NULL;
	lst_command_expected = create_lst_command_test(2, create_map(2, "echo", "bonjour"), create_map(2, "<", "LOUISE"), create_map(2, "cat", "main.c"), create_map(2, ">", "test"));

	lst_command_test = parser(ft_expand(lexer("echo bonjour < LOUISE | cat main.c > test"), env));

	result = lst_command_compare(lst_command_expected, lst_command_test);

	printf("result %d", result);
	*/

	/*
	while (lst_command != NULL)
	{
		command = lst_command->content;
		print_command(command);
		lst_command = lst_command->next;
	}
	*/

	return (0);
}
