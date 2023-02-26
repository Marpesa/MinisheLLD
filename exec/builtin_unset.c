/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:42:16 by lmery             #+#    #+#             */
/*   Updated: 2023/02/26 20:48:22 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	until_equal_sign(char *str, char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=' && env[i])
		i++;
	if (ft_strncmp(str, env, i) == 0 && i == (int)ft_strlen_secure(str))
		return (1);
	return (0);
}

int	is_unset(char **cmd)
{
	int	len;

	if (!cmd)
		return (false);
	len = ft_strlen_secure(cmd[0]);
	if ((ft_strncmp(cmd[0], "unset", len) == 0))
		return (1);
	return (0);
}

void	ft_locate_occur(char ***cmd, int j, int *occur, int *found)
{
	if (ft_is_there((*cmd)[j], (*cmd), j) == 0)
	{
		(*occur)++;
		*found = 1;
	}
}

void	copy_env_unset(char ***str_env, int i, char ***cmd, char ***new_env)
{
	int	j;
	int	occur;
	int	found;

	occur = 0;
	while ((*str_env)[i])
	{
		j = 1;
		found = 0;
		while ((*cmd)[j])
		{
			if ((ft_strncmp((*cmd)[j], (*str_env)[i], \
			ft_strlen_secure((*str_env)[i])) == 0 \
			|| until_equal_sign((*cmd)[j], (*str_env)[i]) == 1))
				ft_locate_occur(cmd, j, &occur, &found);
			j++;
		}
		if (found == 0)
			(*new_env)[i - occur] = ft_strdup((*str_env)[i]);
		i++;
	}
}

void	builtin_unset(char **cmd, char ***env)
{
	char	**new_env;
	char	**str_env;
	int		i;
	int		occur;

	i = 0;
	str_env = *env;
	if (!check_occur(cmd, str_env, &occur))
		return ;
	new_env = malloc(sizeof(char *) * \
	((ft_maplen_secure(str_env) - occur) + 1));
	if (!new_env)
		return ;
	ft_bzero(new_env, (sizeof(char *) * \
	((ft_maplen_secure(str_env) - occur) + 1)));
	copy_env_unset(&str_env, i, &cmd, &new_env);
	ft_free_map(*env);
	*env = new_env;
}
