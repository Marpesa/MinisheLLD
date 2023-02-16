#include "minisheLLD.h"

t_bool	is_builtin(char *value)
{
	if (!value)
		return (false);
	if (!(ft_strncmp(value, "echo\0", ft_strlen("echo\0")))) 
		return (true);
		//|| !(ft_strcmp(value, "cd\0")))
	/*
	if (!(ft_strcmp(value, "pwd")) || !(ft_strcmp(value, "export")))
		return (true);
	if (!(ft_strcmp(value, "unset")) || !(ft_strcmp(value, "env")))
		return (true);
	if (!(ft_strcmp(value, "exit")))
		return (true);
		*/
	return (false);
}

void	execute_builtin(char **cmd, int fd)
{
	if (!(ft_strncmp(cmd[0], "echo\0", ft_strlen("echo\0"))))
		builtin_echo(cmd, fd);
	/*	
	else if (!(ft_strcmp(cmd[0], "cd\0")))
		builtin_cd(cmd[1]);
	else if (!(ft_strcmp(cmd[0], "pwd")))
		builtin_pwd();
	else if (!(ft_strcmp(cmd[0], "export")))
		builtin_export(cmd);
	else if (!(ft_strcmp(cmd[0], "unset")))
		builtin_unset(cmd);
	//else if (!(ft_strcmp(cmd[0], "env")))
		//builtin_print_environment(g_minishell.env, STDOUT_FILENO);
	else if (!(ft_strcmp(cmd[0], "exit")))
		builtin_exit(cmd);
	*/
}

