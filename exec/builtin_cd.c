/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:18:18 by lmery             #+#    #+#             */
/*   Updated: 2023/02/27 21:31:11 by lmery            ###   ########.fr       */
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

static int	adding_slash(char **str, char **str2, char ***cmd, int len)
{
	int	path;

	*str = ft_strdup(getenv("PWD"));
	*str2 = ft_strjoin(*str, "/");
	free(*str);
	*str = ft_strjoin(*str2, (*cmd)[1]);
	free(*str2);
	if ((*cmd)[1][len - 1] != '/')
	{
		*str2 = ft_strjoin(*str, "/");
		free(*str);
		path = chdir(*str2);
		free(*str2);
	}
	else
	{
		path = chdir(*str);
		free(*str);
	}
	return (path);
}

static void	end_builtin(void)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", cwd, 1);
}	

static void	init_values_cd(char *cmd, int *len, char **str, char **str2)
{
	*len = 0;
	if (cmd)
		*len = ft_strlen_secure(cmd);
	*str = NULL;
	*str2 = NULL;
}

void	builtin_cd(char **cmd)
{
	int		path;
	char	*str;
	char	*str2;
	int		len;

	init_values_cd(cmd[1], &len, &str, &str2);
	path = 2;

	if (ft_maplen_secure(cmd) > 2 && printf(_ORANGE2 \
	"MinisheLLD	: cd : Too many arguments\n" _END))
		return ;
	else if (ft_maplen_secure(cmd) == 1 || cmd[1][0] == '~')
		path = chdir(getenv("HOME"));
	else if (ft_strncmp(cmd[1], "..", 3) == 0)
		double_point(&str, &str2, &path);
	else if (ft_strncmp(cmd[1], ".", 2) == 0)
		return ;
	else if (cmd[1][0] != '/')
		path = adding_slash(&str, &str2, &cmd, len);
	else
		path = chdir(cmd[1]);
	if (path == -1)
		printf(_ORANGE2 "MinisheLLD : cd : %s : \
		No such file or directory\n"_END, cmd[1]);
	else
		end_builtin();
}
