/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 04:30:01 by gle-mini          #+#    #+#             */
/*   Updated: 2021/12/06 18:44:38 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *str, char sep)
{
	int	i;
	int	count;

	if (str == 0 || str[0] == 0)
		return (0);
	i = 1;
	count = 0;
	if (str[0] != sep)
		count++;
	while (str[i] != '\0')
	{
		if (str[i] != sep && str[i - 1] == sep)
			count++;
		i++;
	}
	return (count);
}

static int	ft_next_word_count(char const *str, char sep, int i)
{
	int	count;

	count = 0;
	while (str[i] == sep && str[i] != '\0')
	{
		i++;
	}
	while (str[i] != '\0' && str[i] != sep)
	{
		count++;
		i++;
	}
	return (count);
}

static char	**ft_free(char **str_tab, int i)
{
	int	j;

	j = 0;
	while (j < i && str_tab[j] != 0)
	{
		free(str_tab[j]);
		j++;
	}
	free(str_tab);
	return (0);
}

static char	**ft_split2(char **tab_str, char const *s, char c)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	while (i < ft_wordcount(s, c))
	{
		j = 0;
		tab_str[i] = (char *)malloc(ft_next_word_count(s, c, k) + 1);
		if (!tab_str[i])
			return (ft_free(tab_str, i));
		while (s[k] != '\0' && s[k] == c)
			k++;
		while (s[k] != '\0' && s[k] != c)
			tab_str[i][j++] = s[k++];
		tab_str[i][j] = '\0';
		i++;
	}
	tab_str[i] = NULL;
	return (tab_str);
}

char	**ft_split(char const *s, char c)
{
	char	**tab_str;

	if (!s)
		return (0);
	tab_str = (char **)malloc(sizeof(*tab_str) * \
			(ft_wordcount(s, c) + 1));
	if (!tab_str)
		return (0);
	tab_str = ft_split2(tab_str, s, c);
	return (tab_str);
}
