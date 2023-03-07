/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:11:42 by gle-mini          #+#    #+#             */
/*   Updated: 2023/03/07 17:05:27 by gle-mini         ###   ########.fr       */
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
static void	get_absolute_path(char **cmd, int *error_status, char **env)
{
	char	*path;
	char	*bin;


	path = NULL;
	bin = NULL;
	if (cmd[0][0] == '\0')
	{
		*error_status = -1;
		return ;
	}
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		if (is_in_env("PATH", env))
			path = ft_strdup(getenv("PATH"));
		else if (path == NULL && env[0] == NULL)
			path = ft_strdup("/bin:/usr/local/bin:/usr/bin:\
					/bin:/usr/local/sbin");
		else 
		{
			*error_status = 2;
			return ;
		}
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
			// free(cmd[0]);
			// cmd[0] = NULL;
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

void	redirection(t_command *command)
{
	int	i;
	int	new_out;
	int	new_in;
	char	**redirection;

	redirection = command->redir;
	i = 0;
	//print_map(redirection, 2);
	while (redirection != NULL && redirection[i] != NULL)
	{
		if (ft_strncmp(redirection[i], "<\0", 2) == 0)
		{
			//ft_putstr_fd("< OK\n", 2);
			new_in = open(redirection[i + 1], O_RDONLY, 0644);
			command->fd_in = new_in;
			//dup2(new_in, fd_in);
			i += 2;
		}
		else if (ft_strncmp(redirection[i], ">\0", 2) == 0)
		{
			//ft_putstr_fd("> OK\n", 2);
			new_out = open(redirection[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			command->fd_out = new_out;
			//dup2(new_out, fd_out);
			i += 2;
        }
		else if (ft_strncmp(redirection[i], ">>\0", 3) == 0)
		{
			//ft_putstr_fd(">> OK\n", 2);
			new_out = open(redirection[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
			command->fd_out = new_out;
			//dup2(new_out, fd_out);
			i += 2;
		}
		else if (ft_strncmp(redirection[i], "<<\0", 3) == 0)
		{
			ft_putstr_fd("<<\n", 2);
			new_in = open(HEREDOC_FILE, O_RDONLY, 0644);
			ft_putnbr_fd(new_in, 2);
			ft_putstr_fd("\n", 2);
			if (new_in == -1)
				perror("open heredoc");
			command->fd_in = new_in;
			i += 1;
		}
	}
}


int	ft_pipe(char **cmd, char ***env, int *prevpipe,	t_list *lst_command, t_list *lst_command_head)
{
	int		pipefd[2];
	int	cpid;
	int	res;
	t_command *command;

	//print_command(lst_command->content, 2);
	command = lst_command->content;
	res = 1;
	pipe(pipefd);
	cpid = fork ();
	if (cpid == 0)
	{
		redirection(lst_command->content);
		close(pipefd[0]);
		if (command->fd_out == STDOUT_FILENO)
			command->fd_out = pipefd[1];
		dup2(command->fd_out, STDOUT_FILENO);
		close(pipefd[1]);
		if (command->fd_in == STDIN_FILENO)
			command->fd_in = *prevpipe;
		dup2(command->fd_in, STDIN_FILENO);
		close(*prevpipe);
		if (is_builtin(*cmd) == true)
		{
			int	exit_status = execute_builtin(cmd, env, command->fd_out, lst_command_head);
			ft_lstclear(&lst_command_head, del_command);
			ft_free_map(*env);
			exit(exit_status);

		}
		else
		{
			execve(cmd[0], cmd, *env);
		}
		exit(0);
	}
	else
	{
		ignore_sigint();
		close(pipefd[1]);
		close(*prevpipe);
		*prevpipe = pipefd[0];
	}
	ignore_signal_for_shell();
	if (is_builtin(*cmd) == true)
		res = 4;
	return (res);
}

int	ft_last(char **cmd, char ***env, int prevpipe, t_list *lst_command, t_list *lst_command_head)
{
	pid_t	cpid;
	int		error;
	t_command	*command;
	int		status;
	error = 1;
	//print_command(lst_command->content, 2);
	command = lst_command->content;
	cpid = fork();
	if (cpid == 0)
	{
		redirection(lst_command->content);
		if (command->fd_out != STDOUT_FILENO)
			dup2(command->fd_out, STDOUT_FILENO);
		if (command->fd_in == STDIN_FILENO)
			command->fd_in = prevpipe;
		dup2(command->fd_in, STDIN_FILENO);
		close (prevpipe);
		//ft_putnbr_fd(command->fd_out, 2);
		if (is_builtin(*cmd) == true)		
		{
			int	exit_status = execute_builtin(cmd, env, command->fd_out, lst_command_head);
			ft_lstclear(&lst_command_head, del_command);
			ft_free_map(*env);
			exit(exit_status);
		}
		else
			execve (cmd[0], cmd, *env);
	}
	else
	{
		ignore_sigint();
		if (prevpipe != STDOUT_FILENO)
			close (prevpipe);
		while (waitpid(-1, &status, 0) != -1)
			;
		if (WIFEXITED(status))
		{
			g_status = WEXITSTATUS(status);
		}
	}
	ignore_signal_for_shell();
	if (is_builtin(*cmd) == true)
		error = 3;
	return (error);
}

int	exec(t_list	*lst_command, char ***env)
{
	t_list		*lst_current;
	t_command	*command;
	int			prevpipe;
	int			error_status;

	lst_current = NULL;
	lst_current = lst_command;
	error_status = 0;
	prevpipe = dup(STDIN_FILENO);
	//print_lst_command(lst_command, 2);
	while (lst_current != NULL)
	{
		command = lst_current->content;
		if (!is_builtin(*command->word))
			get_absolute_path(command->word, &error_status, *env);
		if (error_status == 2)
		{
			ft_putstr_fd(_ORANGE2 "MinisheLLD : ", 2);
			ft_putstr_fd((command->word)[0], 2);
			ft_putstr_fd(" : no such file or directory\n" _END, 2);
			return (127);
		}
		if (lst_current != NULL && ((ft_lstsize(lst_command) == 1 && is_builtin(command->word[0])) || is_cd(command->word)))
		{
			g_status = execute_builtin(command->word, env, command->fd_out, lst_current);
			lst_current = lst_current->next;
		}
		/*
		if (g_status >= 0)
		{
			if (lst_current->next)
				lst_current = lst_current->next;
			else
				break;
		}
		*/
		if (lst_current != NULL && lst_current->next == NULL)
		{
			if ((ft_last(command->word, env, prevpipe, lst_current, lst_command)) == 3)
			{
				// ft_lstclear(&lst_command, del_command);
				// ft_free_map(*env);
				// exit (0);
			}
		}
		else if (lst_current != NULL)
		{
			if ((ft_pipe(command->word, env, &prevpipe, lst_current, lst_command)) == 4)
			{
				// ft_lstclear(&lst_command, del_command);
				// ft_free_map(*env);
				// if (is_exit(command->word))
				// 	break;
			}
		}
		if (is_exit(command->word) && !lst_current->next)
		{
			if(lst_command != NULL)
				ft_lstclear(&lst_command, del_command);
			ft_free_map(*env);
			// printf ("error = %d\n", g_status);
			exit (g_status);
		}
		if (lst_current != NULL)
			lst_current = lst_current->next;
	}	
	//if (g_status == -1)
		//g_status = 0;
	return (g_status);
}
