/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:22:03 by lmery             #+#    #+#             */
/*   Updated: 2023/02/26 19:22:52 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static int	is_nflag(char *arg)
{
	if (*arg != '-' || *arg == '\0')
		return (0);
	arg++;
	if (*arg != 'n')
		return (0);
	while (*arg && *arg == 'n')
		arg++;
	if (*arg == '\0')
		return (1);
	return (0);
}

int	builtin_echo(char **command, int fd, char ***env, t_list *lst_command)
{
	int	nflag;

	nflag = 0;
	command++;
	while (*command && is_nflag(*command))
	{
		nflag = 1;
		command++;
	}
	while (*command && *(command + 1))
	{
		ft_putstr_fd(*command, fd);
		if (*(command + 1))
			ft_putstr_fd(" ", fd);
		command++;
	}
	if (*command)
		ft_putstr_fd(*command, fd);
	if (!nflag)
		ft_putendl_fd("", fd);
	ft_free_map(*env);
	ft_lstclear(&lst_command, del_command);
	exit (0);
	return (0);
}
