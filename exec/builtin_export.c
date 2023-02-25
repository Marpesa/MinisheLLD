/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:52:19 by lmery             #+#    #+#             */
/*   Updated: 2023/02/26 00:31:34 by lmery            ###   ########.fr       */
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

int	valid_export(char *cmd)
{
	int	i;

	i = 0;
	if (ft_strlen_secure(cmd) < 3)
		return (0);
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (0);
	i++;
	while (cmd[i])
	{
		if(cmd[i] == '=' && cmd[i + 1])
			return (1);
		i++;
	}
	return (0);
}

static char	*until_equal(char *cmd)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while(cmd[i])
	{
		if (cmd[i] == '=')
		{
			len = i;
			break;
		}
		i++;
	}
	if (len != 0)
		return(ft_substr(cmd, 0, len));
	return (NULL);
}

int	index_in_env(char *cmd, char **env)
{
	int	i;

	i = 0;
		// printf("index = %d\n", index);
	// printf("cmd = %s\n", cmd);
	// printf("env[%d] = %s\n", i, env[i]);
	while (env[i])
	{
		if (ft_strncmp(cmd, env[i], ft_strlen_secure(env[i])) == 0 || \
		until_equal_sign(cmd, env[i]) == 1){
			// printf("I = %d\n", i);
			return (i);}
		i++;
	}
	return (-1);
}

void	builtin_export(char **cmd, char ***env)
{
	char	**new_env;
	char	**str_env;
	char	*key;
	int		i;
	int		j;

	i = 0;
	j = 1;
	key = NULL;
	while (cmd[j])
	{
		printf("J = %d\n", j);
		if (!valid_export(cmd[j]))
		{
			printf(_ORANGE2 "MinisheLLD : export : unvalid format '%s'\n"_END, cmd[j]);
			j++;
			continue;			
		}
		if (cmd[j] && cmd[j][0] == '\0')
		{
			printf(_ORANGE2 "MinisheLLD : export : empty value\n" _END);
			j++;
			continue;
		}
		key = until_equal(cmd[j]);
		if (is_in_env(key, *env))
		{
			if (index_in_env(key, *env) >= 0)
			{	
				// free((*env)[index_in_env(key, *env)]);
				(*env)[index_in_env(key, *env)] = ft_strdup(cmd[j]);	
			}
			// printf("test = %d\n", index_in_env(cmd[j], *env));
			j++;
			free(key);
			continue;
		}
		printf("YO = %d\n", j);
		free(key);
		i = 0;
		str_env = *env;
		new_env = malloc(sizeof(char *)*(ft_maplen_secure(str_env) + 2));
		ft_bzero(new_env, (sizeof(char *)*(ft_maplen_secure(str_env) + 2)));
		if (!new_env)
			return ;
		while (i < (int)(ft_maplen_secure(str_env)))
		{
			new_env[i] = ft_strdup(str_env[i]);
			i++;
		}
		printf("Grr = %d\n", j);
		new_env[i] = ft_strdup(cmd[j]);
		new_env[i + 1] = NULL;

		free_map(*env);
		*env = new_env; 
		j++;
	}
}
