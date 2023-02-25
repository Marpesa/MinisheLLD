#include "minisheLLD.h"

static char	*check_path_slash(char *cwd)
{
	char	*ncwd;
	int		i;

	ncwd = malloc(sizeof(char ) * (ft_strlen(cwd) + 2));
	if (ncwd == NULL)
		ft_putstr_fd("malloc error\n", 2);
	ncwd[0] = '/';
	i = 1;
	while (*cwd)
	{
		ncwd[i] = *cwd;
		cwd++;
		i++;
	}
	ncwd[i] = '\0';
	return (ncwd);
}

static char	*check_path(char *cwd, char *path)
{
	int		nb_slash;
	int		is_path;

	nb_slash = 0;
	is_path = 1;
	while (path[nb_slash] == '/')
		nb_slash++;
	if (path[nb_slash] == '\0')
		is_path = 0;
	if (nb_slash == 2)
		return (check_path_slash(cwd));
	else if (nb_slash > 2 && !is_path)
		return ("/");
	return (cwd);
}

static int	change_directory(char *path, char ***envp)
{
	char	*cwd;
	char	buff[4097];

	cwd = get_env("PWD", envp);
	if (path[0] == '.' && path[1] == '\0')
		path = ft_strjoin(cwd, "/.");
	else if (path[0] == '.' && path[1] == '.' && path[2] == '\0')
		path = ft_strjoin(cwd, "/..");
	if (!chdir(path))
	{
		//create set env
		//set_env("OLDPWD", cwd, envp);
		getcwd(buff, 4096);
		cwd = check_path(buff, path);
		//set_env("PWD", cwd, envp);
		return (0);
	}
	else
		return (print_dirpath_err(path));
}

static int	cd_to_many_args(void)
{
	ft_putendl_fd("minishell: cd: too many arguments", 2);
	return (1);
}

int	builtin_cd(char **exec_args, char **envp[])
{
	char	*path;
	int		ret;

	ret = 0;
	if (exec_args[0] && exec_args[1])
		return (cd_to_many_args());
	else if (!exec_args[0])
	{
		path = get_env("HOME", envp);
		if (!path[0])
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (1);
		}
	}
	else
		path = exec_args[0];
	if (path == NULL)
		ft_putstr_fd("cd: Allocation error\n", 2);
	ret = change_directory(path, envp);
	return (ret);
}
