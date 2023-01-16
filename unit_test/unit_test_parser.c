/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:07:12 by lmery             #+#    #+#             */
/*   Updated: 2023/01/16 20:20:16 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

command *create_command_test(int s)


int	str_compare(t_list	*str_expected, t_list *str_result)
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

void	test_parser(t_list *lst_expected_parser, t_list *lst_expected_expand, char *test_command, char **env)
{
	t_list *lst_test;
	printf("Command tested: %s\n", test_command);	
	printf("-------------LEXER---------------\n");
	lst_test = lexer(test_command);
	if (lst_compare(lst_expected_parser, lst_test))
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
	ft_lstclear(&lst_expected_parser, free_token);
	ft_lstclear(&lst_expected_expand, free_token);
	ft_lstclear(&lst_test, free_token);
	printf("_____________________________________________________\n\n");
}