/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 02:50:36 by lmery             #+#    #+#             */
/*   Updated: 2023/03/14 00:40:00 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static void	end_builtin(void)
{
	char	cwd[PATH_MAX];

	if (getenv("PWD") == NULL)
		return ;
	getcwd(cwd, sizeof(cwd));
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", cwd, 1);
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
