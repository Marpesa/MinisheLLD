/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:04:29 by lmery             #+#    #+#             */
/*   Updated: 2023/02/26 19:20:38 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	double_point(char **str, char **str2, int *path)
{
	*str = ft_strdup(getenv("PWD"));
	*str2 = ft_root_one(*str);
	free(*str);
	*path = chdir(*str2);
	free(*str2);
	*str2 = NULL;
}

char	*ft_root_one(char *back)
{
	int		i;
	char	*res;

	res = NULL;
	i = ft_strlen_secure(back) - 1;
	while (back[i])
	{
		if (back[i] == '/')
			break ;
		i--;
	}
	if (i == 0)
		return (NULL);
	else
	{
		res = malloc(sizeof(char) * (i + 1));
		res = ft_strldup_secure(res, back, i + 1);
	}
	return (res);
}

int	is_cd(char **cmd)
{
	int	len;

	if (!cmd)
		return (false);
	len = ft_strlen_secure(cmd[0]);
	if ((ft_strncmp(cmd[0], "cd", len) == 0))
		return (1);
	return (0);
}
