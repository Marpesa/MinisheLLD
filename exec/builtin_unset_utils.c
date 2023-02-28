/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:47:07 by lmery             #+#    #+#             */
/*   Updated: 2023/02/28 19:08:53 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	is_in_env(char *cmd, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(cmd, env[i], ft_strlen_secure(env[i])) == 0 || \
		until_equal_sign(cmd, env[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_there(char *str, char **cmd, int index)
{
	int		i;

	i = 0;
	while (cmd[i] && i < index)
	{
		if (ft_strncmp(cmd[i], str, ft_strlen_secure(cmd[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_occur(char **cmd, char **str_env, int *occur)
{
	int		j;

	(*occur) = 0;
	j = 1;
	while (cmd[j])
	{
		if (is_in_env(cmd[j], str_env) == 1 && ft_is_there(cmd[j], cmd, j) == 0)
			(*occur)++;
		j++;
	}
	if ((*occur) == 0)
	{
		ft_print_error(_ORANGE2 "No occurence for unset\n" _END, NULL, NULL);
		return (0);
	}
	return (*occur);
}
