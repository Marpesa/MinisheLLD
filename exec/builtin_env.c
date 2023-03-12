/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:35:44 by lmery             #+#    #+#             */
/*   Updated: 2023/03/12 01:04:02 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	error_env(char ***env, char **str_env, t_list *lst_command, char *msg)
{
	(void)str_env;
	ft_print_error(_ORANGE2 "", msg, "\n" _END);
	ft_free_map(*env);
	ft_lstclear(&lst_command, del_command);
	exit (126);
}

int	builtin_env(char **cmd, int fd, char ***env, t_list *lst_command)
{
	char	**str_env;
	int		i;

	str_env = (*env);
	i = 1;
	if (!*env)
		error_env(env, str_env, lst_command, \
		"Environnement corrupted");
	if (ft_maplen_secure(cmd) != 1)
		error_env(env, str_env, lst_command, \
		"env : Options not available");
	else
	{
		while (str_env && str_env[i])
		{
			ft_putstr_fd(str_env[i], fd);
			ft_putstr_fd("\n", fd);
			i++;
		}
	}
	return (0);
}
