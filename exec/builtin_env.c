/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:35:44 by lmery             #+#    #+#             */
/*   Updated: 2023/02/24 17:48:16 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	builtin_env(char **cmd, int fd, char ***env, t_list *lst_command)
{
	int i;

	i = 0;
	if (!*env)
	{
		printf(_ORANGE "MinisheLLD : Environnement corrupted\n" _END);
		return ;
	}
	if(ft_maplen_secure(cmd) != 1)
	{
		printf(_ORANGE "MinisheLLD : env : Options not available\n" _END);
		return ;
	}
	else 
	{
		while (*env[i])
		{
			ft_putstr_fd(*env[i], fd);
			i++;
		}
	}
	ft_free_map(*env);
	ft_lstclear(&lst_command, del_command);
	exit (0);
}