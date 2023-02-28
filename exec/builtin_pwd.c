/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 02:52:44 by lmery             #+#    #+#             */
/*   Updated: 2023/02/28 19:08:17 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	builtin_pwd(char ***env, t_list *lst_command)
{
	char	cwd[PATH_MAX];
	char	*str;

	str = NULL;
	if ((*env)[0] == NULL)
	{
		ft_print_error(_ORANGE2 "Pwd : Error\n" _END, NULL, NULL);
		free(str);
		ft_free_map(*env);
		ft_lstclear(&lst_command, del_command);
		exit (0);
	}
	str = ft_strdup(getenv("PWD"));
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	free(str);
	ft_free_map(*env);
	ft_lstclear(&lst_command, del_command);
	exit (0);
}
