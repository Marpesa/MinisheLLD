/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 02:50:36 by lmery             #+#    #+#             */
/*   Updated: 2023/03/14 16:06:56 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	change_old_pwd(char ***env)
{
	char	cwd[PATH_MAX];
	char	**old_str;

	old_str = malloc(sizeof (char *) * 3);
	if (getenv("PWD") == NULL)
		return ;
	getcwd(cwd, sizeof(cwd));
	old_str[0] = ft_strdup("export");
	old_str[1] = ft_strjoin("OLDPWD=", getenv("PWD"));
	old_str[2] = NULL;	
	builtin_export(old_str, env);
	free_map(old_str);
}


static void	end_builtin(char ***env)
{
	char	cwd[PATH_MAX];
	char	**str;
	char	**old_str;

	str = malloc(sizeof (char *) * 3);
	old_str = malloc(sizeof (char *) * 3);
	if (getenv("PWD") == NULL)
		return ;
	getcwd(cwd, sizeof(cwd));
	str[0] = ft_strdup("export");
	str[1] = ft_strjoin("PWD=", cwd);
	str[2] = NULL;	
	old_str[0] = ft_strdup("export");
	old_str[1] = ft_root_one(str[1]);
	old_str[2] = NULL;
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
