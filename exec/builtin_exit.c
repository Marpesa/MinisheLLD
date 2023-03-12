/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 04:20:53 by lmery             #+#    #+#             */
/*   Updated: 2023/03/12 00:52:02 by lmery            ###   ########.fr       */
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

void	modulo_status(int *tmp, char **cmd, int *res, int j)
{
	int	i;

	i = 0;
	if (cmd[1])
	{
		if ((!ft_isdigit(cmd[1][0]) && cmd[1][0] != '-' && cmd[1][0] != '+'))
			*res = 2;
		else if (ft_atoi(cmd[1]) > 255)
			*res = (ft_atoi(cmd[1]) % 255);
		else
			*res = (ft_atoi(cmd[1]));
		while (cmd[1][i])
		{
			while (cmd[1][i] == '+' || cmd[1][i] == '-')
				i++;
			j++;
			i++;
		}
		if (j > 11)
			*res = 101;
		g_status = *res;
	}
	else
		g_status = *tmp;
}

void	builtin_exit(char ***env, t_list *lst_command, char **cmd)
{
	int	res;
	int	tmp;
	int	j;

	j = 0;
	tmp = g_status;
	modulo_status(&tmp, cmd, &res, j);
	if (ft_maplen_secure(cmd) > 2 || \
	(cmd[1] && (cmd[1][0] == '1' && !cmd[1][1])))
		g_status = 1;
	if ((cmd[1] && (cmd[1][0] == '0' && !cmd[1][1])))
		g_status = 0;
	ft_putstr_fd(_ORANGE2 "exit\n" _END, 2);
	ft_free_map(*env);
	ft_lstclear(&lst_command, del_command);
	exit(g_status);
}
