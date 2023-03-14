/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:04:29 by lmery             #+#    #+#             */
/*   Updated: 2023/03/14 16:55:49 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

char	*ft_strdup_oldpwd(const char *s1)
{
	char	*str;
	size_t	i;
	size_t	j;

	j = 0;
	printf("len = %ld\n", ft_strlen_secure(s1));
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
	printf("str = %s\n", str);
	return (str);
}


int	double_point(char **str, char **str2, int *path, char ***env)
{	
	int	i;

	i = index_in_env("PWD=5", *env);
	printf("i = %d\n", i);

	if (i == -1)
		return (-1);
	printf("i = %d\n", i);
	printf("str = %s\n", (*env)[i]);
	*str = ft_strdup_oldpwd((*env)[i]);
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
