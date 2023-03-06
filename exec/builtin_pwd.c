/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 02:52:44 by lmery             #+#    #+#             */
/*   Updated: 2023/03/05 19:33:02 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	is_pwd(char **cmd)
{
	// int	len;
	if (!cmd)
		return (false);
	// len = ft_strlen_secure(cmd[0]);
	if ((ft_strncmp(cmd[0], "pwd", 3) == 0))
		return (1);
	return (0);
}

void	builtin_pwd(char **cmd, char ***env, t_list *lst_command)
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
		ft_print_error(_ORANGE2 "Pwd : Options not available\n" _END, NULL, NULL);
		free(str);
		g_status = 126;
		return ;
	}
	str = ft_strdup(getenv("PWD"));
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	free(str);
}
