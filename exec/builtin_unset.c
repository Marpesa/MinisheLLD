/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:42:16 by lmery             #+#    #+#             */
/*   Updated: 2023/02/26 19:46:45 by lmery            ###   ########.fr       */
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

void	builtin_unset(char **cmd, char ***env)
{
	char	**new_env;
	char	**str_env;
	int		i;
	int		j;
	int		occur;
	int		found;

	occur = 0;
	found = 0;
	i = 0;
	j = 1;
	str_env = *env;
	while (cmd[j])
	{
		if (is_in_env(cmd[j], str_env) == 1 && ft_is_there(cmd[j], cmd, j) == 0)
			occur++;
		j++;
	}
	if (occur == 0)
	{
		printf(_ORANGE2 "No occurence for unset\n" _END);
		return ;
	}
	j = 1;
	new_env = malloc(sizeof(char *) * \
	((ft_maplen_secure(str_env) - occur) + 1));
	if (!new_env)
		return ;
	ft_bzero(new_env, (sizeof(char *) * \
	((ft_maplen_secure(str_env) - occur) + 1)));
	occur = 0;
	i = 0;
	while (str_env[i])
	{
		j = 1;
		found = 0;
		while (cmd[j])
		{
			if ((ft_strncmp(cmd[j], str_env[i], \
			ft_strlen_secure(str_env[i])) == 0 \
			|| until_equal_sign(cmd[j], str_env[i]) == 1))
			{
				if (ft_is_there(cmd[j], cmd, j) == 0)
				{
					found = 1;
					occur++;
				}
			}
			j++;
		}
		if (found == 0)
			new_env[i - occur] = ft_strdup(str_env[i]);
		i++;
	}
	ft_free_map(*env);
	*env = new_env;
}
