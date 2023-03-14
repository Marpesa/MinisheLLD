/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:04:29 by lmery             #+#    #+#             */
/*   Updated: 2023/03/14 19:05:53 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

char	*ft_strdup_oldpwd(const char *s1)
{
	char	*str;
	size_t	i;
	size_t	j;

	j = 0;
	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) - 3));
	if (!str)
		return (NULL);
	i = 4;
	while (s1[i])
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = 0;
	return (str);
}

int	double_point(char **str, char **str2, int *path)
{	
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_print_error("Current Working Directory lost, " \
		, "", "use cd without argument to go back to HOME directory\n" _END);
		return (-1);
	}
	*str = ft_strdup(cwd);
	if (*str == NULL)
		return (-1);
	*str2 = ft_root_one(*str);
	if (*str2 == NULL)
		return (-1);
	free(*str);
	*path = chdir(*str2);
	free(*str2);
	*str2 = NULL;
	return (1);
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
		if (res == NULL)
			return (NULL);
		res = ft_strldup_secure(res, back, i + 1);
		if (res == NULL)
			return (NULL);
	}
	return (res);
}

char	*until_equal(char *cmd)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
		{
			len = i;
			break ;
		}
		i++;
	}
	if (len != 0)
		return (ft_substr(cmd, 0, len));
	return (NULL);
}

int	index_in_env(char *cmd, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(cmd, env[i], ft_strlen_secure(env[i])) == 0 || \
		equal_sign(cmd, env[i]) == 1)
			return (i);
		i++;
	}
	return (-1);
}
