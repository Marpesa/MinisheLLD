/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 04:20:53 by lmery             #+#    #+#             */
/*   Updated: 2023/02/23 17:34:26 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"


int	is_exit(char **cmd)
{
	int	len;

	if (!cmd)
		return (false);
	len = ft_strlen_secure(cmd[0]);
	if ((ft_strncmp(cmd[0], "exit", len) == 0)) 
		return (1);
	return (0);
}

void	builtin_exit(char ***env, t_list *lst_command)
{
	printf( _ORANGE "exit\n" _END);
	ft_free_map(*env);
	ft_lstclear(&lst_command, del_command);
	exit(0);
}