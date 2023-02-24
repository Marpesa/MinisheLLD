/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:52:19 by lmery             #+#    #+#             */
/*   Updated: 2023/02/24 19:20:23 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minisheLLD.h"

char	**builtin_export(char **cmd, char ***env, t_list *lst_command)
{
	char	**new_env;
	char	**str_env;
	int		i;
	int		first_occur;

	first_occur = 0;
	str_env = *env;
	i = 0;
	new_env = malloc(sizeof(char *)*(ft_maplen_secure(str_env) + 1));
	// if (!new_env)
	// 	return (NULL);
	if(ft_maplen_secure(cmd) > 2)
	{
		printf(_ORANGE "MinisheLLD : export : Too many arguments\n" _END);
		return (NULL);
	}
	else 
	{
		while (i < (int)(ft_maplen_secure(str_env)))
		{
			if (ft_strncmp(str_env[i], cmd[1], ft_strlen_secure(str_env[i])) > 0)
			{
				// printf("YO1\n");
				new_env[i] = ft_strdup(str_env[i]);
			}
			else if (ft_strncmp(str_env[i], cmd[1], \
			ft_strlen_secure(str_env[i])) <= 0 && first_occur == 0)
			{
				// printf("YO2\n");
				new_env[i] = ft_strdup(cmd[1]);
				first_occur = 1;
			}
			else
			{
				// printf("YO3\n");
				new_env[i] = ft_strdup(str_env[i]);
			}
			i++;
		}
	}
	// printf("YO\n");

	i = 0;
	while (new_env[i])
	{
		printf("%s\n", new_env[i]);
		i++;
	}
	ft_free_map(*env);
	ft_lstclear(&lst_command, del_command);
	return (new_env);
}
