/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:45:21 by gle-mini          #+#    #+#             */
/*   Updated: 2023/03/11 23:14:20 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

char	*var_find(char *start, char *end, char **env, t_bool s_in_d)
{
	int		i;

	(void)s_in_d;
	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(start, env[i], end - start) == 0 && \
		env[i][end - start] == '='))
			return (&env[i][end - start + 1]);
		i++;
	}
	return (NULL);
}

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

static int	return_token(char *str, int *i, char **end, t_quotes *quotes)
{
	if (str[*i] == '\'')
		quotes->in_s = !quotes->in_s;
	if ((str[*i] == '\'' && quotes->in_d == false) || \
			(str[*i] == '\'' && quotes->in_d == true && *i != 0) || \
			(str[*i] == '$'))
	{
		*end = &str[*i];
		return (1);
	}
	if (str[*i] == '\"')
	{
		quotes->in_d = !quotes->in_d;
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
		if (return_token(str, &i, end, quotes))
			return (1);
		i++;
	}
		*end = &str[i];
	return (0);
}
