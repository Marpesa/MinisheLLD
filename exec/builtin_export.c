/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:52:19 by lmery             #+#    #+#             */
/*   Updated: 2023/02/24 23:02:14 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minisheLLD.h"

int	is_export(char **cmd)
{
	int	len;

	if (!cmd)
		return (false);
	len = ft_strlen_secure(cmd[0]);
	if ((ft_strncmp(cmd[0], "export", len) == 0)) 
		return (1);
	return (0);
}

void	builtin_export(char **cmd, char ***env)
{
	char	**new_env;
	char	**str_env;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (cmd[j])
	{
		i = 0;
		str_env = *env;
		new_env = malloc(sizeof(char *)*(ft_maplen_secure(str_env) + 2));
		if (!new_env)
			return ;
		else 
		{
			while (i < (int)(ft_maplen_secure(str_env)))
			{
				new_env[i] = ft_strdup(str_env[i]);
				i++;
			}
			new_env[i] = ft_strdup(cmd[j]);
			new_env[i + 1] = NULL;
		}
		free_map(*env);
		*env = new_env; 
		j++;
	}
}
