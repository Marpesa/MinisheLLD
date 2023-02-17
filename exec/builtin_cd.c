/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:18:18 by lmery             #+#    #+#             */
/*   Updated: 2023/02/17 02:48:28 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

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
			break;
		i--;
	}
	if (i == 0)
		return (NULL);
	else 
	{
		res = malloc(sizeof(char) * i);
		res = ft_strldup_secure(res, back, i);
	}
	return (res);
}
int	builtin_cd(char **cmd, char ***env)
{
	(void)env;
	int		path;
	char	*str;
	int		len;

	printf("builtin CD\n");
	len = 0;
	if (cmd[1])
		len = ft_strlen_secure(cmd[1]);
	str = NULL;
	path = -1;
	if(ft_maplen_secure(cmd) > 2)
	{
		printf(_ORANGE "MinisheLLD : cd : Too many arguments\n" _END);
		return (0);
	}
	else if(ft_maplen_secure(cmd) == 1 || cmd[1][0] == '~')
	{	path = chdir(getenv("HOME"));
		// printf ("path = % i\n", path);
	}
	else if(ft_strncmp(cmd[1], "-", len) == 0 || ft_strncmp(cmd[1], "..", len) == 0)
	{
		str = ft_strdup(getenv("PWD"));
		str = ft_root_one(str);
		path = chdir(str);
	}
	else if (ft_strncmp(cmd[1], ".", len) == 0)
        path = chdir(getenv("PWD"));
    else if(cmd[1][0] != '/')
    {
		str = ft_strdup(getenv("PWD"));
        strcat(str,"/");
        strcat(str,cmd[1]);
		if (cmd[1][len - 1] != '/')
			strcat(str,"/");
		printf("path = %s\n", str);
        path = chdir(str);
		chdir(str);
    }
	else
		path = chdir(cmd[1]);
	printf ("path = % i\n", path);
	if (path == -1)
		printf(_ORANGE "MinisheLLD : cd : %s : No such file or directory\n"_END, cmd[1]);
    else//update the $OLDPWD and $PWD environment variables on success of chdir() system call
    {
        char cwd[PATH_MAX];//maximum path length from linux/limits.h
        getcwd(cwd, sizeof(cwd));//get the current working directory
        setenv("OLDPWD",getenv("PWD"),1);//update $OLDPWD to the value of $PWD
        setenv("PWD",cwd,1);//update $PWD to the current directory 
    }
	return (1);
}