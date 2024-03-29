/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:18:28 by lmery             #+#    #+#             */
/*   Updated: 2023/03/14 20:04:43 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

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
	if (!(ft_strncmp(*cmd, "lld", len)))
		return (true);
	return (false);
}

int	execute_builtin3(char **cmd, char ***env)
{
	int	result;

	result = 0;
	if (!(ft_strncmp(cmd[0], "cd\0", ft_strlen("cd\0"))))
	{
		result = builtin_cd(cmd, env);
		if (result == -1)
			return (-1);
		g_status = result;
	}
	if (!(ft_strncmp(cmd[0], "lld\0", ft_strlen("lld\0"))))
	{
		result = builtin_lld(cmd);
		if (result == -1)
			return (-1);
		g_status = result;
	}
	return (result);
}

int	execute_builtin2(char **cmd, char ***env, int fd)
{
	int	result;

	result = 0;
	if (!(ft_strncmp(cmd[0], "pwd\0", ft_strlen("pwd\0"))))
		result = builtin_pwd(cmd, env, fd);
	else if (!(ft_strncmp(cmd[0], "unset\0", ft_strlen("unset\0"))))
	{
		if (builtin_unset(cmd, env) == -1)
			return (-1);
	}
	else if (!(ft_strncmp(cmd[0], "export\0", ft_strlen("export\0"))))
	{
		result = builtin_export(cmd, env);
		if (result == -1)
			return (-1);
	}
	else
	{
		result = execute_builtin3(cmd, env);
		if (result == -1)
			return (-1);
	}
	return (result);
}

int	execute_builtin(char **cmd, char ***env, int fd, t_list *lst_command)
{
	int	result;

	result = 0;
	if (!(ft_strncmp(cmd[0], "echo\0", ft_strlen("echo\0"))))
	{
		if (builtin_echo(cmd, fd, env, lst_command) == -1)
			return (-1);
	}
	else if (!(ft_strncmp(cmd[0], "exit\0", ft_strlen("exit\0"))))
		builtin_exit(env, lst_command, cmd);
	else if (!(ft_strncmp(cmd[0], "env\0", ft_strlen("env\0"))))
	{
		if (builtin_env(cmd, fd, env, lst_command) == -1)
			return (-1);
	}
	else
	{
		result = execute_builtin2(cmd, env, fd);
		if (result == -1)
			return (-1);
	}
	return (result);
}
