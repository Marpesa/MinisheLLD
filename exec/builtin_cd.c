/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:18:18 by lmery             #+#    #+#             */
/*   Updated: 2023/03/12 02:43:09 by gle-mini         ###   ########.fr       */
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
	if (*str == NULL)
		return (-2);
	free(*str2);
	if ((*cmd)[1][len - 1] != '/')
	{
		*str2 = ft_strjoin(*str, "/");
		if (*str2 == NULL)
			return (-2);
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

static void	init_values_cd(char **str, char **str2)
{
	*str = NULL;
	*str2 = NULL;
}

int	builtin_cd2(char **cmd, char **str, char **str2, int *path)
{
	if (cmd[1][0] != '/')
	{
		*path = adding_slash(str, str2, &cmd, ft_strlen_secure(cmd[1]));
		if (*path == -2)
			return (-1);
	}
	else
		*path = chdir(cmd[1]);
	return (1);
}

int	print_error_path(char **cmd, int path)
{
	if (path == -1)
	{
		ft_print_error(_ORANGE2 "cd : \'", cmd[1], \
		"\' No such file or directory\n"_END);
		return (1);
	}
	else
		end_builtin();
	g_status = 0;
	return (0);
}

int	builtin_cd(char **cmd)
{
	int		path;
	char	*str;
	char	*str2;

	init_values_cd(&str, &str2);
	path = 2;
	if (ft_maplen_secure(cmd) > 2 && !ft_print_error(_ORANGE2 \
	"cd : Too many arguments\n" _END, NULL, NULL))
		return (1);
	else if (ft_maplen_secure(cmd) == 1 || cmd[1][0] == '~')
		path = chdir(getenv("HOME"));
	else if (ft_strncmp(cmd[1], "..", 3) == 0)
	{
		if (double_point(&str, &str2, &path) == -1)
			return (-1);
	}
	else if (ft_strncmp(cmd[1], ".", 2) == 0)
		return (0);
	else
		if (!builtin_cd2(cmd, &str, &str2, &path))
			return (-1);
	if (print_error_path(cmd, path))
		return (1);
	return (g_status);
}
