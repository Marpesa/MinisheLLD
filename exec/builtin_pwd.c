/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 02:52:44 by lmery             #+#    #+#             */
/*   Updated: 2023/02/26 18:55:36 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	builtin_pwd(char ***env, t_list *lst_command)
{
	char cwd[PATH_MAX];
	char	*str;

	str = NULL;
	str = ft_strdup(getenv("PWD"));
	if (chdir(str) == -1 && printf("ERROR\n"))
	{
		free(str);
		ft_free_map(*env);
		ft_lstclear(&lst_command, del_command);
		exit (0);
		// return ;
	}
    printf("str = %s\n", str);
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
	free(str);
	ft_free_map(*env);
	ft_lstclear(&lst_command, del_command);
	exit (0);
}