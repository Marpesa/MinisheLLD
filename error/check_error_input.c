/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:24:59 by lmery             #+#    #+#             */
/*   Updated: 2023/03/11 21:29:48 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static int	check_closed_quotes(char *input)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			res = closed_quotes(input, &i);
		if (res == 2)
		{
			ft_print_error(_ORANGE2 "Error input : Quote not closed\n" _END, \
			NULL, NULL);
			g_status = 2;
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
	if (input[i] == '\0')
		return (2);
	return (0);
}

int	not_in_quote(char *input, int i)
{
	int	j;
	int	res;

	res = 1;
	j = 0;
	while (input[j] && input[j] != '\"')
		j++;
	if (input[j] == '\"')
	{
		res = 0;
		j++;
	}
	if (res == 0 && j <= i)
	{
		while (input[j])
		{
			if (input[j] == '\"' && j > i)
				return (res);
			j++;
		}
	}
	return (1);
}

static int	error_input_loop(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if ((input[i] == '(' || input[i] == ')' || input[i] == ';' \
		|| input[i] == '{' || input[i] == '}' || input[i] == '&') \
		&& not_in_quote(input, i) != 0)
		{
			ft_print_error(_ORANGE2 \
			"Error input : Unauthorized charcacter in prompt: \"", NULL, NULL);
			write(2, &input[i], 1);
			write(2, "\"\n" _END, 2);
			g_status = 2;
			return (2);
		}
		i++;
	}
	return (0);
}

int	check_error_input(char *input)
{
	int	res;
	int	check;

	res = 0;
	check = 0;
	if (input[0] == '.' || input[0] == '/')
		res = point_and_slash(input);
	if (res != 0)
		return (res);
	if (error_input_loop(input) == 2)
		return (2);
	check = check_closed_quotes(input);
		res = check;
	return (res);
}
