/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:35:44 by lmery             #+#    #+#             */
/*   Updated: 2023/02/24 19:03:55 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	builtin_env(char **cmd, int fd, char ***env, t_list *lst_command)
{
	char	**str_env;
	int 	i;

	(void)fd;
	str_env = (*env);
	i = 0;
	if (!*env)
	{
		printf(_ORANGE "MinisheLLD : Environnement corrupted\n" _END);
		ft_free_map(*env);
		ft_free_map(str_env);
		ft_lstclear(&lst_command, del_command);
		exit (0);
	}
	if(ft_maplen_secure(cmd) != 1)
	{
		printf(_ORANGE "MinisheLLD : env : Options not available\n" _END);
		ft_free_map(*env);
		ft_free_map(str_env);
		ft_lstclear(&lst_command, del_command);
		exit (0);
	}
	else 
	{
		while (str_env[i])
		{
			printf("%s\n", str_env[i]);
			i++;
		}
	}
	ft_free_map(*env);
	ft_free_map(str_env);
	ft_lstclear(&lst_command, del_command);
	exit (0);
}