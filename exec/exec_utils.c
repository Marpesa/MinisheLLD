/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:16:50 by lmery             #+#    #+#             */
/*   Updated: 2023/03/14 20:18:30 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	cat_to_bin(char *bin, char *path_split, char *cmd)
{
	ft_strncat(bin, path_split, ft_strlen_secure(bin) \
			+ ft_strlen_secure(path_split));
	ft_strncat(bin, "/", ft_strlen_secure(bin) + 1);
	ft_strncat(bin, cmd, ft_strlen_secure(bin) \
			+ ft_strlen_secure(cmd));
}

int	get_valid_bin(char *path, char **cmd, char **bin_result)
{
	char	*path_split;
	char	*bin;
	char	*rest;

	if (path == NULL)
		return (127);
	path_split = ft_strtok_r(path, ":", &rest);
	while (path_split != NULL)
	{	
		bin = ft_calloc(sizeof(char), (ft_strlen(path_split) + 1 \
					+ ft_strlen(cmd[0]) + 1));
		if (bin == NULL)
			return (-1);
		cat_to_bin(bin, path_split, cmd[0]);
		if (access(bin, F_OK) == 0)
		{
			*bin_result = bin;
			return (1);
		}
		path_split = ft_strtok_r(NULL, ":", &rest);
		free(bin);
		bin = NULL;
	}
	*bin_result = NULL;
	return (1);
}

int	dup_path(char ***env, char **path, int *error_status)
{
	if (is_in_env("PATH", *env))
	{
		if (getenv("PATH") == NULL)
			return (1);
		*path = ft_strdup(getenv("PATH"));
		if (*path == NULL)
			return (-1);
	}
	else if (path == NULL && env[0] == NULL)
	{
		*path = ft_strdup("/bin:/usr/local/bin:/usr/bin:\
				/bin:/usr/local/sbin");
		if (*path == NULL)
			return (-1);
	}
	else
	{
		*error_status = 2;
		return (2);
	}
	return (1);
}

void	free_path_and_cmd(char *path, char *bin, char **cmd)
{
	free(path);
	path = NULL;
	free(cmd[0]);
	cmd[0] = NULL;
	cmd[0] = bin;
}

int	free_path_and_return_error(char *bin, char *path, int *error_status)
{
	if (bin == NULL)
	{
		free(path);
		path = NULL;
		*error_status = 2;
		return (2);
	}
	return (1);
}
