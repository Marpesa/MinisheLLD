/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:45:21 by gle-mini          #+#    #+#             */
/*   Updated: 2023/03/11 18:58:52 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static void	skip_s_quote(char *str, int *i, t_bool *in_d_quote)
{
	(void)in_d_quote;
	if (str[*i] == '\'' && *i == 0 && *in_d_quote == false)
	{
		*i += 1;
		while (str[*i] != '\0' && str[*i] != '\'')
			*i += 1;
		if (str[*i] != '\0')
			*i += 1;
	}
}

static int	return_token(char *str, int *i, char **end, t_bool *in_d_quote, t_bool *in_s_quote)
{
	if (str[*i] == '\'')
		*in_d_quote = !*in_s_quote;

	if ((str[*i] == '\'' && *in_d_quote == false) || \
			(str[*i] == '\'' && *in_d_quote == true && *i != 0))
	{
		*end = &str[*i];
		return (1);
	}
	if (str[*i] == '$')
	{
		*end = &str[*i];
		return (1);
	}
	if (str[*i] == '\"')
	{
		*in_d_quote = !*in_d_quote;
		*end = &str[*i];
		return (1);
	}
	if (str[*i] == ' ' || str[*i] == '+' || str[*i] == '%' \
	|| str[*i] == '-' || str[*i] == '/')
	{
		*end = &str[*i];
		return (1);
	}
	return (0);
}

// static void	nested_quotes(t_quotes *quotes, int i, char *str)
// {
// 	if (str[i] == '\'' && quotes->in_s == true && quotes->in_d == true)
// 		quotes->s_in_d = true;
// }


int	custom_tokenizer(char *str, char **start, char **end, t_quotes *quotes)
{
	int	i;

	i = 0;
	*start = str;
	if (str[i] == '\"')
		quotes->in_d = !quotes->in_d;
	if (str[i] == '\'')
		quotes->in_s = !quotes->in_s;
	if (str[i] == '$' || str[i] == ' ' || str[i] == '\"' || str[i] == '+' \
	|| str[i] == '%' || str[i] == '/' || str[i] == '-')
		i++;
	skip_s_quote(str, &i, &quotes->in_d);
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			quotes->in_d = !quotes->in_d;
		if (str[i] == '\'')
			quotes->in_s = !quotes->in_s;
		// nested_quotes(quotes, i, str);
		if (return_token(str, &i, end, &quotes->in_d, &quotes->in_s))
			return (1);
		i++;
	}
	// if (quotes->s_in_d == true)
	// {
	// 	(*start) += 2;
	// 	*end = &str[i - 2];
	// }
	// else
		*end = &str[i];
	return (0);
}
