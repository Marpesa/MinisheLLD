/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:24:59 by lmery             #+#    #+#             */
/*   Updated: 2023/02/26 23:21:47 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static int	closed_quotes(char *input, int *i)
{
	char	quote;
	int		res;

	res = 0;
	quote = input[*i];
	*i += 1;
	while (input [*i])
	{
		if (input[*i] == quote)
		{
			res = 1;
			break ;
		}
		*i += 1;
	}
	return (res);
}

static int	check_closed_quotes(char *input)
{
	int	i;
	int	res;

	res = 1;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			res = closed_quotes(input, &i);
		if (res == 0)
		{
			printf(_ORANGE2 "Quote not closed dumbass\n" _END);
			break ;
		}
		i++;
	}
	return (res);
}

static int	point_and_slash(char *input)
{
	int	i;

	i = 0;
	if (ft_strlen_secure(input) < 3)
		return (0);
	while (input[i] && (input[i] == '.' || input[i] == '/'))
		i++;
	if  (input[i] == '\0')
		return (0);
	return (1);
}

int	check_error_input(char *input)
{
	int	i;
	int	res;
	int	check;

	res = 1;
	check = 1;
	i = 0;
	if (input[0] == '.' || input[0] == '/')
		res = point_and_slash(input);
	if (res == 0)
		return (res);
	while (input[i])
	{
		if (input[i] == '(' || input[i] == ')' || input[i] == ';' \
		|| input[i] == '{' || input[i] == '}' || input[i] == '&')
		{
			printf(_ORANGE2 "Unauthorized charcacter in prompt: '%c'\n"\
			_END, input[i]);
			return (0);
		}
		i++;
	}
	check = check_closed_quotes(input);
		res = check;
	return (res);
}
