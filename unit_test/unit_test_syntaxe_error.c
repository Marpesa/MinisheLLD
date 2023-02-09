#include "minisheLLD.h"

t_bool syntaxe_error_compare(char *str, int value_expected, char **env)
{
	t_list	*lst_token;
	int	value_tested;

	printf("Command tested: %s\n", str);
	lst_token = lexer(str);
	ft_expand(lst_token, env);
	value_tested = syntaxe_error(lst_token);
	if (value_expected == value_tested)
	{
		printf(_BOLD _BLUE_LLD "OK\n" _END);
		return (true);
	}
	printf(_BOLD _ORANGE "KO\n" _END);
	return (false);

	printf("___________________________________________\n\n");

}

void	test_syntaxe_error_redir(char **env)
{
	syntaxe_error_compare("<", 0, env);
	syntaxe_error_compare(">", 0, env);
	syntaxe_error_compare(">>", 0, env);
	syntaxe_error_compare("<<", 0, env);
	syntaxe_error_compare("<<<<", 0, env);
	syntaxe_error_compare("<<<< <<", 0, env);
	syntaxe_error_compare(">>>>", 0, env);
	syntaxe_error_compare(">>>>>>>>>>>>>>>>>>>", 0, env);
	syntaxe_error_compare(">>>>>>>>>>>>>>>>>>>>", 0, env);
	syntaxe_error_compare("<<<<<<<<<<<<", 0, env);
	syntaxe_error_compare("<<<<<<<<<<<<<", 0, env);
	syntaxe_error_compare(" > > > > >", 0, env);
	syntaxe_error_compare(" <  < < <", 0, env);
	syntaxe_error_compare(">>>> >> > >>> <", 0, env);
	syntaxe_error_compare(">echo>", 0, env);
	syntaxe_error_compare("<echo<", 0, env);
	syntaxe_error_compare(">>echo>>", 0, env);
	syntaxe_error_compare("echo > <", 0, env);
	syntaxe_error_compare("echo hola > > bonjour", 0, env);
	syntaxe_error_compare("echo hola < < bonjour", 0, env);
	syntaxe_error_compare("echo hola >> >> bonjour", 0, env);
	syntaxe_error_compare("echo hola >>> bonjour", 0, env);
	syntaxe_error_compare("echo hola << << bonjour", 0, env);
	syntaxe_error_compare("cat >>", 0, env);
	syntaxe_error_compare("cat <<", 0, env);
	syntaxe_error_compare("cat >>>", 0, env);
	syntaxe_error_compare("cat >> <<", 0, env);
	syntaxe_error_compare("cat >> > >> << >>", 0, env);
	syntaxe_error_compare("echo hola <<< bonjour", 1, env);
	syntaxe_error_compare("echo hola <<<< bonjour", 0, env);
	syntaxe_error_compare("echo hola <<<<< bonjour", 0, env);
	syntaxe_error_compare("echo hola <<<<<< bonjour", 0, env);
	
}

void	test_syntaxe_error_pipe(char **env)
{
	syntaxe_error_compare("|", 0, env);
	syntaxe_error_compare("test |", 0, env);
	syntaxe_error_compare("| hola", 0, env);
	syntaxe_error_compare("| |", 0, env);
	syntaxe_error_compare("|    | |", 0, env);
	syntaxe_error_compare("||", 0, env);
	syntaxe_error_compare("|||||||", 0, env);
	syntaxe_error_compare("||||||||", 0, env);
	syntaxe_error_compare(">>|<<", 0, env);
	syntaxe_error_compare(">> | >>", 0, env);
	syntaxe_error_compare("|echo|", 0, env);
	syntaxe_error_compare("|echo -n hola", 0, env);
	syntaxe_error_compare("echo | | ", 0, env);
	syntaxe_error_compare("ech|o hola ||| cat ", 0, env);
	syntaxe_error_compare("ls || <", 0, env);
}




void	test_syntaxe_error(char **env)
{
	printf("----------------_SYNTAXE_ERROR---------------\n");
	test_syntaxe_error_redir(env);
	test_syntaxe_error_pipe(env);

	
	syntaxe_error_compare("test |", 0, env);
	syntaxe_error_compare("test |", 0, env);
}
