/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:08:07 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/13 03:08:21 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static int	trim_len(char *str)
{
	int		i;
	int		len;
	t_bool	in_d_quote;
	t_bool	in_s_quote;

	i = 0;
	len = 0;
	in_d_quote = false;
	in_s_quote = false;
	while (str[i])
	{
		if (str[i] == '\"' && in_s_quote == false)
		{
			in_d_quote = !in_d_quote;
			len++;
		}
		if (str[i] == '\'' && in_d_quote == false)
		{
			in_s_quote = !in_s_quote;
			len++;
		}
		i++;
	}
	return (len);
}

static void	skip_quote(char *str, int *i, \
		t_bool *in_d_quote, t_bool *in_s_quote)
{
	while ((str[*i] == '\'' && *in_d_quote == false) || \
			(str[*i] == '\"' && *in_s_quote == false))
	{
		if (str[*i] == '\'')
			*in_s_quote = !(*in_s_quote);
		if (str[*i] == '\"')
			*in_d_quote = !(*in_d_quote);
		*i += 1;
	}
}

static char	*trim_quote(char *str)
{
	int		i;
	int		j;
	char	*new_str;
	t_bool	in_d_quote;
	t_bool	in_s_quote;

	i = 0;
	j = 0;
	in_d_quote = false;
	in_s_quote = false;
	if (str == NULL)
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(str) - trim_len(str) + 1));
	while (str[i])
	{
		skip_quote(str, &i, &in_d_quote, &in_s_quote);
		new_str[j] = str[i];
		if (str[i])
		{
			j++;
			i++;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}

void	trim(char **str)
{
	int		nb_quotes;
	char	*new_str;

	new_str = NULL;
	nb_quotes = trim_len(*str);
	if (nb_quotes > 0)
	{
		new_str = trim_quote(*str);
		free(*str);
		*str = new_str;
	}
}
