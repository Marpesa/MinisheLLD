/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:35:44 by lmery             #+#    #+#             */
/*   Updated: 2023/02/26 19:34:46 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	error_env(char ***env, char **str_env, t_list *lst_command, char *msg)
{
	(void)str_env;
	printf(_ORANGE "%s\n" _END, msg);
	ft_free_map(*env);
	ft_lstclear(&lst_command, del_command);
	exit (0);
}

void	builtin_env(char **cmd, int fd, char ***env, t_list *lst_command)
{
	char	**str_env;
	int		i;

	(void)fd;
	str_env = (*env);
	i = 0;
	if (!*env)
		error_env(env, str_env, lst_command, "MinisheLLD : \
		Environnement corrupted");
	if (ft_maplen_secure(cmd) != 1)
		error_env(env, str_env, lst_command, "MinisheLLD : env : \
		Options not available");
	else
	{
		while (str_env && str_env[i])
		{
			printf("%s\n", str_env[i]);
			i++;
		}
	}
	ft_free_map(str_env);
	ft_lstclear(&lst_command, del_command);
	exit (0);
}
