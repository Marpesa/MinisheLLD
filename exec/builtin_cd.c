/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:18:18 by lmery             #+#    #+#             */
/*   Updated: 2023/03/14 19:10:32 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static int	adding_slash(char **str, char **str2, char ***cmd, int len)
{
	int		path;
	char	cwd[PATH_MAX];

	*str = ft_strdup(getcwd(cwd, sizeof(cwd)));
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

static int	init_values_cd(char **str, char **str2, int *path, char **cmd)
{
	*str = NULL;
	*str2 = NULL;
	*path = 2;
	return (ft_maplen_secure(cmd));
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

int	cd_home(char **cmd, int	*path)
{
	if (ft_maplen_secure(cmd) == 1 || cmd[1][0] == '~')
	{
		if (getenv("HOME") == NULL)
			return (1);
		*path = chdir(getenv("HOME"));
		return (0);
	}
	return (-1);
}

int	builtin_cd(char **cmd, char ***env)
{
	int		path;
	char	*str;
	char	*str2;

	if (init_values_cd(&str, &str2, &path, cmd) > 2 && \
	!ft_print_error("cd : Too many arguments\n" _END, "", ""))
		return (1);
	g_status = change_old_pwd(env);
	if (cd_home(cmd, &path) == 1)
		return (1);
	else if ((cd_home(cmd, &path) == 0))
		return (g_status);
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
	if (print_error_path(cmd, path, env))
		return (1);
	return (g_status);
}
