/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:11:42 by gle-mini          #+#    #+#             */
/*   Updated: 2023/02/17 05:06:38 by lmery            ###   ########.fr       */
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

/*
void	create_pipe(int	*old_pipe_in, t_list *lst_current)
{
	int	new_pipe[2];

	dup2(*old_pipe_in, STDIN_FILENO);
	if (*old_pipe_in != STDIN_FILENO)
		close(*old_pipe_in);
	if (ft_lstsize(lst_current) <= 1)
		return ;
	pipe(new_pipe);
	dup2(new_pipe[1], STDOUT_FILENO);
	if (new_pipe[1] != STDIN_FILENO || new_pipe[1] != STDOUT_FILENO)
		close(new_pipe[1]);
	*old_pipe_in = dup(new_pipe[0]);
	if (new_pipe[0] != STDIN_FILENO || new_pipe[0] != STDOUT_FILENO)
		close(new_pipe[0]);
}
*/

int	ft_pipe(char **cmd, char ***env, int *prevpipe)
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
		//cmd[len] = NULL;
		if (is_builtin(*cmd) == true)
		{
			res = 2;
			execute_builtin(cmd, env, pipefd[1]);
		}
		else
			execve (cmd[0], cmd, *env);
	}
	else
	{
		close (pipefd[1]);
		close (*prevpipe);
		*prevpipe = pipefd[0];
	}
	return (res);
}

int	ft_last(char **cmd, char ***env, int prevpipe, int *error)
{
	pid_t	cpid;
	// int		res;

	*error = 1;
	cpid = fork();
	if (cpid == 0)
	{
		dup2 (prevpipe, STDIN_FILENO);
		close (prevpipe);
		//cmd[len] = NULL;
		if (is_builtin(*cmd) == true)
		{
			*error = 2;
			execute_builtin(cmd, env, STDOUT_FILENO);
		}
		else
		{
			execve (cmd[0], cmd, *env);
		}
	}
	else
	{
		if (prevpipe != STDOUT_FILENO)
			close (prevpipe);
		while (wait (NULL) != -1)
			;
	}
	return (*error);
}

void	exec(t_list	*lst_command, t_list *lst_token, char **linebuffer, char ***env)
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
		&& ft_strncmp(*command->word, "pwd", 4) && ft_strncmp(*command->word, "exit", 4))
		{
			// printf ("TEST\n");
			get_absolute_path(command->word, &error_status);
		}
		if (error_status == 2)
		{
			printf("command %s not found\n", *command->word);
			return ;
		}
		int result;
		if (lst_current->next == NULL)
		{
			if ((result = ft_last(command->word, env, prevpipe, &error_status)) == 2)
			{
				printf("test0\n");
				free_and_exit(lst_token, lst_command, linebuffer, *env);
				// exit (0);
			}

				printf("result:%d\n", result);
		}
		else
			if ((result = ft_pipe(command->word, env, &prevpipe)) == 2)
			{
				printf("test1\n");
				free_and_exit(lst_token, lst_command, linebuffer, *env);
				// exit (0);
			}
		printf("result2:%d\n", result);

		//if (fork_and_exec(command, env, &command->pid) == -1)
			//return ;
		//restore_fd(save_fd);
		lst_current = lst_current->next;
	}	
}
