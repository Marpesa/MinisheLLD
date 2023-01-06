/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:24:59 by lmery             #+#    #+#             */
/*   Updated: 2023/01/06 21:31:43 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static int	closed_quotes(char *input, int *i)
{
	char quote;

	quote = input[*i];
	*i += 1;
	while (input [*i])
	{
		if (input[*i] == quote)
		{
			*i += 1;
			return (1);
		}
		*i += 1;
	}
	printf( _ORANGE "Quote not closed dumbass\n" _END);
	return (0);
}

int	check_error_input(char *input)
{
	int	i;
	int	res;

	res = 1;
	i = 0;
	while (input[i])
	{
		if (input[i] == '(' || input[i] == ')' || input[i] == ';' || input[i] == '{' || input[i] == '}')
		{
			printf( _ORANGE "Unauthorized charcacter in prompt: '%c'\n"_END, input[i]);
			return (0);
		}
		i++;
	}
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			res = closed_quotes(input, &i);
		i++;
	}
	return (res);
}
