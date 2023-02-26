/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:18:18 by lmery             #+#    #+#             */
/*   Updated: 2023/02/26 17:44:47 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

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

char	*ft_strldup_secure(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	i;

	srcsize = ft_strlen_secure(src);
	i = 0;
	if (srcsize == 0)
		return (0);
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (dst);
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

// static int	addind_slash(char **str, char **str2, char **cmd)
// {
// 	int	path;
	
// 	str = ft_strdup(getenv("PWD"));
// 	str2 = ft_strjoin(str, "/");
// 	free(str);
// 	str = ft_strjoin(str2, cmd[1]);
// 	free(str2);
// 	if (cmd[1][len - 1] != '/')
// 	{
// 		str2 = ft_strjoin(str, "/");
// 		free(str);
// 		path = chdir(str2);
// 		free(str2);
// 	}
// 	else
// 	{
// 		path = chdir(str);
// 		free(str);
// 	}
// 	return (path);
// }

void	builtin_cd(char **cmd)
{
	int		path;
	char	*str;
	char	*str2;
	int		len;
	char	cwd[PATH_MAX];

	len = 0;
	if (cmd[1])
		len = ft_strlen_secure(cmd[1]);
	str = NULL;
	str2 = NULL;
	path = 2;
	if (ft_maplen_secure(cmd) > 2 && printf(_ORANGE "MinisheLLD \
	: cd : Too many arguments\n" _END))
		return ;
	else if (ft_maplen_secure(cmd) == 1 || cmd[1][0] == '~')
		path = chdir(getenv("HOME"));
	else if (ft_strncmp(cmd[1], "-", len) == 0 || \
	ft_strncmp(cmd[1], "..", len) == 0)
	{
		str = ft_strdup(getenv("PWD"));
		str2 = ft_root_one(str);
		free(str);
		path = chdir(str2);
		free(str2);
		str2 = NULL;
	}
	else if (ft_strncmp(cmd[1], ".", len) == 0)
		path = chdir(getenv("PWD"));
	else if (cmd[1][0] != '/')
	{
		str = ft_strdup(getenv("PWD"));
		str2 = ft_strjoin(str, "/");
		free(str);
		str = ft_strjoin(str2, cmd[1]);
		free(str2);
		if (cmd[1][len - 1] != '/')
		{
			str2 = ft_strjoin(str, "/");
			free(str);
			path = chdir(str2);
			free(str2);
		}
		else
		{
			path = chdir(str);
			free(str);
		}
	}
	else
		path = chdir(cmd[1]);
	if (path == 2)
		printf(_ORANGE "MinisheLLD : cd : %s : \
		No such file or directory\n"_END, cmd[1]);
	else
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
}
