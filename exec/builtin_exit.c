/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 04:20:53 by lmery             #+#    #+#             */
/*   Updated: 2023/02/18 18:49:18 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	builtin_exit(char ***env, t_list *lst_command)
{
	printf( _ORANGE "exit\n" _END);
	ft_free_map(*env);
	ft_lstclear(&lst_command, del_command);
	exit(0);
	//trouver le moyen d'appeler free all
}