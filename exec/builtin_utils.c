/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:18:28 by lmery             #+#    #+#             */
/*   Updated: 2023/03/11 15:18:02 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

t_bool	is_builtin(char **cmd)
{
	int	len;

	if (cmd == NULL)
		return (false);

	if (!*cmd)
		return (false);
	len = ft_strlen_secure(*cmd) + 1;
	if ((ft_strncmp(*cmd, "echo", len) == 0))
		return (true);
	if (!(ft_strncmp(*cmd, "pwd", len)))
		return (true);
	if (!(ft_strncmp(*cmd, "env", len)))
		return (true);
	if (!(ft_strncmp(*cmd, "export", len)))
		return (true);
	if (!(ft_strncmp(*cmd, "unset", len)))
		return (true);
	if (!(ft_strncmp(*cmd, "cd", len)))
		return (true);	
	if (!(ft_strncmp(*cmd, "exit", len)))
		return (true);
	return (false);
}

int	execute_builtin(char **cmd, char ***env, int fd, t_list *lst_command)
{
	int result;
	int	error_tmp;

	result = 1;
	if (!(ft_strncmp(cmd[0], "echo\0", ft_strlen("echo\0"))))
	{
		if (builtin_echo(cmd, fd, env, lst_command) == -1)
			return (-1);
	}
	else if (!(ft_strncmp(cmd[0], "exit\0", ft_strlen("exit\0"))))
	{
		builtin_exit(env, lst_command, cmd);
	}
	else if (!(ft_strncmp(cmd[0], "env\0", ft_strlen("env\0"))))
	{
		if (builtin_env(cmd, fd, env, lst_command) == -1)
			return (-1);
	}
	else if (!(ft_strncmp(cmd[0], "pwd\0", ft_strlen("pwd\0"))))
	{
		builtin_pwd(cmd, env, lst_command, fd);
	}
	else if (!(ft_strncmp(cmd[0], "unset\0", ft_strlen("unset\0"))))
	{
		if (builtin_unset(cmd, env) == -1)
			return (-1);
	}
	else if (!(ft_strncmp(cmd[0], "export\0", ft_strlen("export\0"))))
	{
		if (builtin_export(cmd, env) == -1)
			return (-1);
	}
	else if (!(ft_strncmp(cmd[0], "cd\0", ft_strlen("cd\0"))))
	{
		error_tmp = builtin_cd(cmd);
		if (error_tmp == -1)
			return (-1);
		g_status = error_tmp;
	}
	else
		result = -2;	
	return (result);
}

