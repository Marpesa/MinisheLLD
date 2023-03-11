/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:52:19 by lmery             #+#    #+#             */
/*   Updated: 2023/03/11 20:18:10 by lmery            ###   ########.fr       */
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
		if (cmd[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	allready_in_env(char ***cmd, char ***env, int *j, int i)
{
	char	*key;

	key = NULL;
	key = until_equal((*cmd)[*j]);
	if (is_in_env(key, *env))
	{
		i = index_in_env(key, *env);
		free((*env)[i]);
		(*env)[i] = ft_strdup((*cmd)[*j]);
		if ((*env)[i] == NULL)
			return (-1);
		i = 0;
		(*j)++;
		free(key);
		return (1);
	}
	free(key);
	return (0);
}

int	end_export(char ***new_env, char ***str_env, char ***env, char *cmd)
{
	int	i;

	i = 0;
	*str_env = *env;
	*new_env = malloc(sizeof(char *) * (ft_maplen_secure(*str_env) + 2));
	if (*new_env == NULL)
		return (-1);
	ft_bzero(*new_env, (sizeof(char *) * (ft_maplen_secure(*str_env) + 2)));
	while (i < (int)(ft_maplen_secure(*str_env)))
	{
		(*new_env)[i] = ft_strdup((*str_env)[i]);
		i++;
	}
	(*new_env)[i] = ft_strdup(cmd);
	if ((*new_env)[i] == NULL)
		return (-1);
	(*new_env)[i + 1] = NULL;
	free_map(*env);
	*env = *new_env;
	return (i);
}

int	builtin_export(char **cmd, char ***env)
{
	char	**new_env;
	char	**str_env;
	int		i;
	int		j;
	int		tmp_error;

	i = 0;
	j = 1;
		
	while (cmd[j])
	{
		if ((!valid_export(cmd[j])))
		{
			ft_print_error(_ORANGE2 \
			"export : unvalid entry\n"_END, NULL, NULL);
			g_status = 2;
			return(2);
		}
		j++;
	}
	j = 1;
	while (cmd[j])
	{
		tmp_error = allready_in_env(&cmd, env, &j, i);
		if (tmp_error == 1)
			continue ;
		else if (tmp_error == -1)
			return (-1);	
		i = end_export(&new_env, &str_env, env, cmd[j]);
		if (i == -1)
			return (-1);
		j++;
	}
	if (ft_maplen_secure(cmd) < 2)
		g_status = 1;
	return (1);
}
