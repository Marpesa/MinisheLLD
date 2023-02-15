/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:11:42 by gle-mini          #+#    #+#             */
/*   Updated: 2023/02/11 22:12:24 by gle-mini         ###   ########.fr       */
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

/*PENSER A GERER LE CAS SI ON NE TROUVE PAS LE BINAIRE*/
static int	get_absolute_path(char **cmd)
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
			return (-1);
		if (bin == NULL)
			printf("command not found\n");
		free(path);
		path = NULL;
		free(cmd[0]);
		cmd[0] = NULL;
		cmd[0] = bin;
		free(path);
		path = NULL;
	}
	return (1);
}

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
	close(new_pipe[1]);
	*old_pipe_in = dup(new_pipe[0]);
	close(new_pipe[0]);
}

void	restore_fd(int	*save_fd)
{
	dup2(save_fd[0], STDIN_FILENO);
	close(save_fd[0]);
	dup2(save_fd[1], STDOUT_FILENO);
	close(save_fd[1]);
}

int	fork_and_exec(t_command *command, char **env, int *pid_command)
{
	pid_t	pid;

	pid = fork();
	*pid_command = pid;
	if (pid == 0)
	{
		if (get_absolute_path(command->word) == -1)
			return (-1);
		if (execve(command->word[0], command->word, env) == -1)
			return (-1);
	}
	return (1);
}


/*
void	wait_pid(t_list *lst_command)
{
	t_list		*lst_current;
	t_command	*command;
	int			stat_loc;

	lst_current = lst_command;
	while (lst_current != NULL)
	{
		command = lst_current->content;
		waitpid(command->pid, &stat_loc, 0);
		lst_current = lst_current->next;
	}
}
*/


void	wait_pid(void)
{
	int	stat_loc;

	waitpid(-1, &stat_loc, 0);
}

void	exec(t_list	*lst_command, char **env)
{
	t_list		*lst_current;
	t_command	*command;
	int			old_pipe_in;
	int			save_fd[2];

	lst_current = NULL;
	old_pipe_in = 0;
	lst_current = lst_command;
	while (lst_current != NULL)
	{
		if (lst_current->content != NULL)
			command = lst_current->content;
		save_fd[0] = dup(STDIN_FILENO);
		save_fd[1] = dup(STDOUT_FILENO);
		create_pipe(&old_pipe_in, lst_current);
		if (fork_and_exec(command, env, &command->pid) == -1)
			return ;
		lst_current = lst_current->next;
		restore_fd(save_fd);
	}	
	//wait_pid(lst_command);
	wait_pid();
}
