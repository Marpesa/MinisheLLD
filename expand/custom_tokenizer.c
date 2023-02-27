/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:45:21 by gle-mini          #+#    #+#             */
/*   Updated: 2023/02/27 20:08:22 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"


#include "minisheLLD.h"

static void	skip_s_quote(char *str, int *i, t_bool *in_d_quote)
{
	if (str[*i] == '\'' && *i == 0 && *in_d_quote == false)
	{
		*i += 1;
		while (str[*i] != '\0' && str[*i] != '\'')
			*i += 1;
		if (str[*i] != '\0')
			*i += 1;
	}
}

static int	return_token(char *str, int *i, char **end, t_bool *in_d_quote)
{
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
	if (str[*i] == ' ' || str[*i] == '+' || str[*i] == '%' || str[*i] == '-' || str[*i] == '/')
	{
		*end = &str[*i];
		return (1);
	}
	return (0);
}

int	custom_tokenizer(char *str, char **start, char **end, t_bool *in_d_quote)
{
	int	i;

	i = 0;
	*start = str;
	if (str[i] == '\"' && *in_d_quote == false)
		*in_d_quote = !*in_d_quote;
	if (str[i] == '$' || str[i] == ' ' || str[i] == '\"' || str[i] == '+' || str[i] == '%' || str[i] == '/' || str[i] == '-')
		i++;
	skip_s_quote(str, &i, in_d_quote);
	while (str[i] != '\0')
	{
		if (return_token(str, &i, end, in_d_quote))
			return (1);
		i++;
	}
	*end = &str[i];
	return (0);
}



/*

static void	skip_s_quote(char *str, int *i, t_bool *in_d_quote)
{
	if (str[*i] == '\'' && *i == 0 && *in_d_quote == false)
	{
		*i += 1;
		while (str[*i] != '\0' && str[*i] != '\'')
			*i += 1;
		if (str[*i] != '\0')
			*i += 1;
	}
}

static int	return_token(char *str, int *i, char **end, t_bool *in_d_quote)
{
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
	if (str[*i] == ' ' || str[*i] == '+' || 
			str[*i] == '/' || str[*i] == '-' || 
			str[*i] == '%')
	{
		*end = &str[*i];
		return (1);
	}
	return (0);
}

int	custom_tokenizer(char *str, char **start, char **end, t_bool *in_d_quote)
{
	int	i;

	i = 0;
	*start = str;
	if (str[i] == '\"' && *in_d_quote == false)
		*in_d_quote = !*in_d_quote;
	// Ajouter le - / %
	if (str[i] == '$' || str[i] == ' ' || str[i] == '\"' || str[i] == '+')
		i++;
	skip_s_quote(str, &i, in_d_quote);
	while (str[i] != '\0')
	{
		ft_putstr_fd(str, 1);
		if (return_token(str, &i, end, in_d_quote))
			return (1);
		i++;
	}
	*end = &str[i];
	return (0);
}
*/
