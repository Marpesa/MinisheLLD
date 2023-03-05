/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 04:20:53 by lmery             #+#    #+#             */
/*   Updated: 2023/03/05 22:32:13 by lmery            ###   ########.fr       */
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

void	builtin_exit(char ***env, t_list *lst_command, char **cmd)
{
	int	res;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	if (cmd[1])
	{

		if ((!ft_isdigit(cmd[1][1]) || (!ft_isdigit(cmd[1][0]) && cmd[1][0] != '-' && cmd[1][0] != '+'))) 
			res = 2;
		else if (ft_atoi(cmd[1]) > 255)
			res = (ft_atoi(cmd[1]) % 256);
		else
			res = (ft_atoi(cmd[1]));
		while (cmd[1][i])
		{
			while (cmd[1][i] == '+' || cmd[1][i] == '-')
				i++;
			j++;
			i++;
		}
		if (j > 11)
			res = 101;
		// printf ("j = %d\n", j);
		g_status = res;
	}
	if ((cmd[1][0] == '0'))
		g_status = 0;
	if (ft_maplen_secure(cmd) > 2 || ((cmd[1][0] == '1' && !cmd[1][1])))
		g_status = 1;
	ft_putstr_fd(_ORANGE2 "exit\n" _END, 2);
	ft_free_map(*env);
	ft_lstclear(&lst_command, del_command);
	// printf ("g = %d\n", g_status);
	exit(g_status);
}
