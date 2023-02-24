/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:42:16 by lmery             #+#    #+#             */
/*   Updated: 2023/02/24 23:08:05 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static int	until_equal_sign(char *str, char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=' && env[i])
		i++;
	// printf("i = %d\n", i);
	// printf("env i = %s\n", env);
	// printf("cmd i = %s\n", str);
	if (ft_strncmp(str, env, i) == 0 && i == (int)ft_strlen_secure(str))
	{
		// printf("is_equal\n");
		return (1);
	}
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

void	builtin_unset(char **cmd, char ***env)
{
	char	**new_env;
	char	**str_env;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (cmd[j])
	{
		str_env = *env;
		i = 0;
		new_env = malloc(sizeof(char *)*(ft_maplen_secure(str_env) + 1));
		if (!new_env)
			return ;
		else 
		{
			while (i < (int)(ft_maplen_secure(str_env) - 1))
			{
				if (ft_strncmp(cmd[j], str_env[i], \
				ft_strlen_secure(str_env[i])) != 0 \
				&& until_equal_sign(cmd[j], str_env[i]) == 0) 
					new_env[i] = ft_strdup(str_env[i]);
				i++;
			}
			new_env[i] = NULL;
		}
		free_map(*env);
		*env = new_env; 
		j++;
	}
}
