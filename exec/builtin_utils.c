/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:18:28 by lmery             #+#    #+#             */
/*   Updated: 2023/03/04 18:04:58 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

t_bool	is_builtin(char *value)
{
	int	len;

	if (!value)
		return (false);
	len = ft_strlen_secure(value);
	if ((ft_strncmp(value, "echo", len) == 0))
		return (true);
	if (!(ft_strncmp(value, "pwd", len)))
		return (true);
	if (!(ft_strncmp(value, "env", len)))
		return (true);
	if (!(ft_strncmp(value, "export", len)))
		return (true);
	if (!(ft_strncmp(value, "unset", len)))
		return (true);
	if (!(ft_strncmp(value, "cd", len)))
		return (true);	
	if (!(ft_strncmp(value, "&?", len)))
		return (true);
	if (!(ft_strncmp(value, "exit", len)))
		return (true);
	return (false);
}

void	execute_builtin(char **cmd, char ***env, int fd, t_list *lst_command)
{
	(void) env;
	if (!(ft_strncmp(cmd[0], "echo\0", ft_strlen("echo\0"))))
		builtin_echo(cmd, fd, env, lst_command);
	// else if (!(ft_strncmp(cmd[0], "pwd\0", ft_strlen("pwd\0"))))
	// 	builtin_pwd(env, lst_command);
	else if (!(ft_strncmp(cmd[0], "exit\0", ft_strlen("exit\0"))))
		builtin_exit(env, lst_command);
	else if (!(ft_strncmp(cmd[0], "env\0", ft_strlen("env\0"))))
		builtin_env(cmd, fd, env, lst_command);
}

char	*get_env(char *var, char ***envp)
{
	size_t	size;
	char	*ret;
	int		line;

	line = 0;
	while ((*envp)[line] != NULL)
	{
		size = 0;
		while ((*envp)[line][size] != '\0' && (*envp)[line][size] != '=')
			size++;
		if (size != ft_strlen(var))
			continue ;
		if (ft_strncmp((*envp)[line], var, size) == 0)
		{
			ret = ft_strdup(&(*envp)[line][size + 1]);
			if (!ret)
				ft_putstr_fd("malloc error\n", 2);
			return (ret);
		}
		line++;
	}
	return (NULL);
}
