/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 02:52:44 by lmery             #+#    #+#             */
/*   Updated: 2023/02/18 18:41:24 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	builtin_pwd(char ***env, t_list *lst_command)
{
	char cwd[PATH_MAX];
	
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
	ft_free_map(*env);
	ft_lstclear(&lst_command, del_command);
	exit (0);
}