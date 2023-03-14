/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 02:50:36 by lmery             #+#    #+#             */
/*   Updated: 2023/03/14 19:03:10 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	change_old_pwd(char ***env)
{
	char	**old_str;
	char	cwd[PATH_MAX];

	ft_bzero(cwd, PATH_MAX);
	getcwd(cwd, sizeof(cwd));
	if (cwd == NULL)
		return (-1);
	old_str = malloc(sizeof (char *) * 3);
	if (cwd == NULL || !old_str)
	{
		free_map(old_str);
		return (-1);
	}
	old_str[0] = ft_strdup("export");
	old_str[1] = ft_strjoin("OLDPWD=", cwd);
	old_str[2] = NULL;
	builtin_export(old_str, env);
	free_map(old_str);
	return (0);
}

static void	end_builtin(char ***env)
{
	char	cwd[PATH_MAX];
	char	**str;

	str = malloc(sizeof (char *) * 3);
	getcwd(cwd, sizeof(cwd));
	if (cwd == NULL)
		return ;
	str[0] = ft_strdup("export");
	str[1] = ft_strjoin("PWD=", cwd);
	str[2] = NULL;
	builtin_export(str, env);
	free_map(str);
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

int	print_error_path(char **cmd, int path, char ***env)
{
	if (path == -1)
	{
		ft_print_error(_ORANGE2 "cd : \'", cmd[1], \
		"\' No such file or directory\n"_END);
		return (1);
	}
	else
		end_builtin(env);
	g_status = 0;
	return (0);
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
