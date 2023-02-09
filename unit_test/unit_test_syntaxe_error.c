#include "minisheLLD.h"

t_bool syntaxe_error_compare(int value_expected)
{
	int	value_tested;

	value_expected = syntaxe_error(heredoc(ft_expand(lexer("test |"))));
	if (value_expected == value_tested)
	{
		printf(_BOLD _BLUE_LLD "OK\n" _END);
		return (true);
	}
	printf(_BOLD _ORANGE "KO\n" _END);
	return (false);

	printf("___________________________________________\n\n");

}


void	test_syntaxe_error()
{
	printf("----------------_SYNTAXE_ERROR---------------\n");
	syntaxe_error_compare("test |", 0);
}
