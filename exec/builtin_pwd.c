/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 02:52:44 by lmery             #+#    #+#             */
/*   Updated: 2023/03/12 04:49:29 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	is_pwd(char **cmd)
{
	if (!cmd)
		return (false);
	if ((ft_strncmp(cmd[0], "pwd", 3) == 0))
		return (1);
	return (0);
}

int	builtin_pwd(char **cmd, char ***env, t_list *lst_command, int fd_out)
{
	char	cwd[PATH_MAX];
	char	*str;

	(void)lst_command;
	str = NULL;
	if ((*env)[0] == NULL)
	{
		ft_print_error(_ORANGE2 "Pwd : Error\n" _END, NULL, NULL);
		free(str);
		g_status = 128;
	}
	if (ft_maplen_secure(cmd) != 1)
	{
		ft_print_error(_ORANGE2 "Pwd : Options not available\n"_END, "", "");
		free(str);
		g_status = 126;
		return (g_status);
	}
	str = ft_strdup(getenv("PWD"));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	ft_putstr_fd(cwd, fd_out);
	ft_putstr_fd("\n", fd_out);
	free(str);
	return (g_status);
}
