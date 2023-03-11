/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:11:42 by gle-mini          #+#    #+#             */
/*   Updated: 2023/03/11 19:53:07 by gle-mini         ###   ########.fr       */
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

	path_split = strtok(path, ":");
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
		path_split = strtok(NULL, ":");
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

static int	get_absolute_path(char **cmd, int *error_status, char **env)
{
	char	*path;
	char	*bin;

	path = NULL;
	bin = NULL;
	if (cmd == NULL || cmd[0][0] == '\0')
	{
		*error_status = -1;
		return (1);
	}
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		if (dup_path(&env, &path, error_status) == -1)
			return (-1);
		if (get_valid_bin(path, cmd, &bin) == -1)
			return (-1);
		if (free_path_and_return_error(bin, path, error_status) == 2)
			return (2);
		free_path_and_cmd(path, bin, cmd);
	}
	return (1);
}

void	redir_in(t_command *command, char **redirection, int *i)
{
	int	new_in;

	new_in = open(redirection[*i + 1], O_RDONLY, 0644);
	if (new_in == -1)
		perror("open");
	if (command->fd_in != STDIN_FILENO)
		close(command->fd_in);
	command->fd_in = new_in;
	*i += 2;
}

void	redir_out(t_command *command, char **redirection, int *i)
{
	int	new_out;

	new_out = open(redirection[*i + 1], \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (new_out == -1)
		perror("open");
	if (command->fd_out != STDOUT_FILENO)
		close(command->fd_out);
	command->fd_out = new_out;
	*i += 2;
}

void	redir_append_out(t_command *command, char **redirection, int *i)
{
	int	new_out;

	new_out = open(redirection[*i + 1], \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (new_out == -1)
		perror("open");
	if (command->fd_out != STDOUT_FILENO)
		close(command->fd_out);
	command->fd_out = new_out;
	*i += 2;
}



void	redir_heredoc(t_command *command, int *i)
{
	int new_in;

	new_in = open(HEREDOC_FILE, O_RDONLY, 0644);
	if (new_in == -1)
		perror("open");
	if (command->fd_in != STDIN_FILENO)
		close(command->fd_in);
	command->fd_in = new_in;
	*i += 1;


}

void	redirection(t_command *command)
{
	int		i;
	char	**redirection;

	redirection = command->redir;
	i = 0;
	while (redirection != NULL && redirection[i] != NULL)
	{
		if (ft_strncmp(redirection[i], "<\0", 2) == 0)
			redir_in(command, redirection, &i);
		else if (ft_strncmp(redirection[i], ">\0", 2) == 0)
			redir_out(command, redirection, &i);
		else if (ft_strncmp(redirection[i], ">>\0", 3) == 0)
			redir_append_out(command, redirection, &i);
		else if (ft_strncmp(redirection[i], "<<\0", 3) == 0)
			redir_heredoc(command, &i);	
	}
}


int	ft_pipe(char **cmd, char ***env, int *prevpipe,	t_list *lst_command, t_list *lst_command_head)
{
	int		pipefd[2];
	int	cpid;
	int	res;
	t_command *command;

	command = lst_command->content;
	res = 1;
	pipe(pipefd);
	cpid = fork();
	if (cpid == 0)
	{
		redirection(lst_command->content);
		close(pipefd[0]);
		if (command->fd_out == STDOUT_FILENO)
			command->fd_out = pipefd[1];
		if (dup2(command->fd_out, STDOUT_FILENO) == -1)
			perror("dup2");
		close(pipefd[1]);
		if (command->fd_in == STDIN_FILENO)
			command->fd_in = *prevpipe;
		if (dup2(command->fd_in, STDIN_FILENO) == -1)
			perror("dup2");
		close(*prevpipe);
		if (is_builtin(cmd) == true)
		{
			int	exit_status = execute_builtin(cmd, env, command->fd_out, lst_command_head);
			if (exit_status == -1)
				return (-1);
			ft_lstclear(&lst_command_head, del_command);
			ft_free_map(*env);
			if (command->fd_out != STDOUT_FILENO)
				close(command->fd_out);
			if (command->fd_in != STDIN_FILENO)
				close(command->fd_in);
			exit(exit_status);

		}
		else
		{
			if (command->fd_out != STDOUT_FILENO)
				close(command->fd_out);
			if (command->fd_in != STDIN_FILENO)
				close(command->fd_in);
			execve(cmd[0], cmd, *env);
		}
	}
	else
	{
		ignore_sigint();
		close(pipefd[1]);
		close(*prevpipe);
		*prevpipe = pipefd[0];
	}
	ignore_signal_for_shell();
	if (is_builtin(cmd) == true)
		res = 4;
	return (res);
}

int	ft_last(char **cmd, char ***env, int prevpipe, t_list *lst_command, t_list *lst_command_head)
{
	pid_t	cpid;
	//int		error;
	t_command	*command;
	int		status;
	//error = 1;
	//print_command(lst_command->content, 2);
	command = lst_command->content;
	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
	}
	else if (cpid == 0)
	{
		redirection(lst_command->content);
		if (command->fd_out != STDOUT_FILENO)
			if (dup2(command->fd_out, STDOUT_FILENO) == -1)
				perror("dup2");
		if (command->fd_in == STDIN_FILENO)
			command->fd_in = prevpipe;
		if (dup2(command->fd_in, STDIN_FILENO))
			perror("dup2");
		close (prevpipe);
		if (cmd == NULL)
		{
			if (command->fd_out != STDOUT_FILENO)
				close(command->fd_out);
			if (command->fd_in != STDIN_FILENO)
				close(command->fd_in);
			ft_lstclear(&lst_command_head, del_command);
			ft_free_map(*env);
			exit(0);
		}
		else if (is_builtin(cmd) == true)		
		{
			int	exit_status = execute_builtin(cmd, env, command->fd_out, lst_command_head);
			if (exit_status == -1)
				return (-1);
			ft_lstclear(&lst_command_head, del_command);
			ft_free_map(*env);
			if (command->fd_out != STDOUT_FILENO)
				close(command->fd_out);
			if (command->fd_in != STDIN_FILENO)
				close(command->fd_in);
			exit(exit_status);
		}
		else
		{
			if (command->fd_out != STDOUT_FILENO)
				close(command->fd_out);
			if (command->fd_in != STDIN_FILENO)
				close(command->fd_in);
			execve (cmd[0], cmd, *env);
		}
	}
	else
	{
		ignore_sigint();
		if (prevpipe != STDOUT_FILENO)
			close (prevpipe);
		while (waitpid(-1, &status, 0) != -1)
			;
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
	ignore_signal_for_shell();
	return (1);
}

int	exec(t_list	*lst_command, char ***env, int tmp)
{
	t_list		*lst_current;
	t_command	*command;
	int			prevpipe;
	int			error_status;

	lst_current = NULL;
	lst_current = lst_command;
	error_status = 0;
	prevpipe = dup(STDIN_FILENO);
	if (prevpipe == -1)
		perror("dup");
	while (lst_current != NULL)
	{
		command = lst_current->content;
		if (is_builtin(command->word) == 0)
		{
			if (get_absolute_path(command->word, &error_status, *env) == -1)
				return (-1);
		}
		if (error_status == 2)
		{
			ft_putstr_fd(_ORANGE2 "MinisheLLD : ", 2);
			ft_putstr_fd((command->word)[0], 2);
			ft_putstr_fd(" : no such file or directory\n" _END, 2);
			return (127);
		}
		if (lst_current != NULL && ((ft_lstsize(lst_command) == 1 && is_builtin(command->word)) || is_cd(command->word)))
		{
			redirection(command);
			g_status = tmp;
			if (is_exit(command->word))
				close(prevpipe);
			tmp = execute_builtin(command->word, env, command->fd_out, lst_current);
			if (tmp == -1)
				return (-1);
			lst_current = lst_current->next;
			if (tmp >= 0)
				g_status = tmp;
			close(prevpipe);
		}
		if (lst_current != NULL && lst_current->next == NULL)
		{
			ft_last(command->word, env, prevpipe, lst_current, lst_command);
		}
		else if (lst_current != NULL)
			ft_pipe(command->word, env, &prevpipe, lst_current, lst_command);
		if (lst_current != NULL)
			lst_current = lst_current->next;
	}
	return (g_status);
}
