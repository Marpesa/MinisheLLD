/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:11:42 by gle-mini          #+#    #+#             */
/*   Updated: 2023/02/26 18:37:18 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	get_valid_bin(char *path, char **cmd, char **bin_result)
{
	char	*path_split;
	char	*bin;

	path_split = strtok(path, ":");
	while (path_split != NULL)
	{	
		bin = ft_calloc(sizeof(char), (ft_strlen(path_split) + 1 \
					+ ft_strlen(cmd[0]) + 1));
		if (bin == NULL)
			return (-1);
		ft_strncat(bin, path_split, ft_strlen_secure(bin) + ft_strlen_secure(path_split));
		ft_strncat(bin, "/", ft_strlen_secure(bin) + 1);
		ft_strncat(bin, cmd[0], ft_strlen_secure(bin) + ft_strlen_secure(cmd[0]));
		if (access(bin, F_OK) == 0)
		{
			*bin_result = bin;
			return (1);
		}
		path_split = strtok(NULL, ":");
		free(bin);
		bin = NULL;
	}
	*bin_result = NULL;
	return (1);
}

/*CHANGER LE GETENV POUR LE SECRET ENV*/
static void	get_absolute_path(char **cmd, int *error_status)
{
	char	*path;
	char	*bin;

	path = NULL;
	bin = NULL;
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		path = ft_strdup(getenv("PATH"));
		if (path == NULL)
			path = ft_strdup("/bin:/usr/local/bin:/usr/bin:\
					/bin:/usr/local/sbin");
		if (get_valid_bin(path, cmd, &bin) == -1)
		{
			*error_status = -1;
			return ;
		}
		if (bin == NULL)
		{
			//printf("command not found\n");
			//perror("command not found\n");
			if (cmd[0] != NULL)
			free(path);
			path = NULL;
			free(cmd[0]);
			cmd[0] = NULL;
			*error_status = 2;
			return ;
		}
		free(path);
		path = NULL;
		free(cmd[0]);
		cmd[0] = NULL;
		cmd[0] = bin;
	}
}

int	ft_pipe(char **cmd, char ***env, int *prevpipe,	t_list *lst_command)
{
	int		pipefd[2];
	int	cpid;
	int	res;

	res = 1;
	pipe (pipefd);
	cpid = fork ();
	if (cpid == 0)
	{
		close (pipefd[0]);
		dup2 (pipefd[1], STDOUT_FILENO);
		close (pipefd[1]);
		dup2 (*prevpipe, STDIN_FILENO);
		close (*prevpipe);
		if (is_builtin(*cmd) == true)
			execute_builtin(cmd, env, pipefd[1], lst_command);
		else
			execve (cmd[0], cmd, *env);
		exit(0);
	}
	else
	{
		close (pipefd[1]);
		close (*prevpipe);
		*prevpipe = pipefd[0];
	}
	if (is_builtin(*cmd) == true)
		res = 4;
	return (res);
}

int	ft_last(char **cmd, char ***env, int prevpipe, t_list *lst_command)
{
	pid_t	cpid;
	int		error;

	error = 1;
	cpid = fork();
	if (cpid == 0)
	{
		dup2 (prevpipe, STDIN_FILENO);
		close (prevpipe);
		if (is_builtin(*cmd) == true)		
			execute_builtin(cmd, env, STDOUT_FILENO, lst_command);
		else
			execve (cmd[0], cmd, *env);
	}
	else
	{
		if (prevpipe != STDOUT_FILENO)
			close (prevpipe);
		while (wait (NULL) != -1)
			;
	}
	if (is_builtin(*cmd) == true)
		error = 3;
	return (error);
}

void	exec(t_list	*lst_command, char ***env)
{
	t_list		*lst_current;
	t_command	*command;
	int			prevpipe;
	int			error_status;

	lst_current = NULL;
	lst_current = lst_command;
	error_status = 0;
	prevpipe = dup(STDIN_FILENO);

	while (lst_current != NULL)
	{
		command = lst_current->content;
		if (ft_strncmp(*command->word, "echo", 5) && ft_strncmp(*command->word, "cd", 3) \
		&& ft_strncmp(*command->word, "pwd", 4) && ft_strncmp(*command->word, "exit", 4) \
		&& ft_strncmp(*command->word, "export", 7) && ft_strncmp(*command->word, "unset", 6) \
		&& ft_strncmp(*command->word, "env", 4))
			get_absolute_path(command->word, &error_status);
		if (error_status == 2)
		{
			printf("command %s not found\n", *command->word);
			return ;
		}
		if (is_cd(command->word))
		{
			builtin_cd(command->word);
			if (lst_current->next)
				lst_current = lst_current->next;
			else
				break;
		}
		if (is_export(command->word))
		{
			builtin_export(command->word, env);
			if (lst_current->next)
				lst_current = lst_current->next;
			else
				break;
		}
		if (is_unset(command->word))
		{
			builtin_unset(command->word, env);
			if (lst_current->next)
				lst_current = lst_current->next;
			else
				break;
		}
		if (lst_current->next == NULL)
		{
			if ((ft_last(command->word, env, prevpipe, lst_command)) == 3)
			{
				// printf("test0\n");
				// ft_lstclear(&lst_command, del_command);
				// ft_free_map(*env);
				// exit (0);
			}
		}
		else
			if ((ft_pipe(command->word, env, &prevpipe, lst_command)) == 4)
			{
				// printf("test1\n");
				// ft_lstclear(&lst_command, del_command);
				// ft_free_map(*env);
				if (is_exit(command->word))
					break;
			}
		if (is_exit(command->word))
		{
			if(lst_command != NULL)
				ft_lstclear(&lst_command, del_command);
			ft_free_map(*env);
			exit (0);
		}
		lst_current = lst_current->next;
	}	
}
