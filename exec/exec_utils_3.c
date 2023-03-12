/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:33:21 by lmery             #+#    #+#             */
/*   Updated: 2023/03/12 02:56:00 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	close_open_fd(t_command *command)
{
	if (command->fd_out != STDOUT_FILENO)
		close(command->fd_out);
	if (command->fd_in != STDIN_FILENO)
		close(command->fd_in);
}

void	close_fd_and_free(t_command *command, char ***env, \
		t_list *lst_command_head)
{
	close_open_fd(command);
	ft_free_map(*env);
	ft_lstclear(&lst_command_head, del_command);
}

int	execute_command(t_command *command, char ***env, t_list *lst_command_head)
{
	int	exit_status;

	exit_status = 0;
	if (command->word == NULL)
	{
		close_fd_and_free(command, env, lst_command_head);
		exit(0);
	}
	else if (is_builtin(command->word) == true)
	{
		exit_status = execute_builtin(command->word, env, command->fd_out, \
					lst_command_head);
		if (exit_status == -1)
			return (-1);
		close_fd_and_free(command, env, lst_command_head);
		exit(exit_status);
	}
	else
	{
		execve (command->word[0], command->word, *env);
		close_open_fd(command);
	}
	return (exit_status);
}

void	redir_child_pipe(t_command *command, int *prevpipe, int *pipefd)
{
	redirection(command);
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
}

int	ft_pipe(t_command *command, char ***env, int *prevpipe, \
		t_list *lst_command_head)
{
	int	pipefd[2];
	int	cpid;

	pipe(pipefd);
	cpid = fork();
	if (cpid == 0)
	{
		redir_child_pipe(command, prevpipe, pipefd);
		if (execute_command(command, env, lst_command_head) == -1)
			return (-1);
	}
	else
	{
		ignore_sigint();
		close(pipefd[1]);
		close(*prevpipe);
		*prevpipe = pipefd[0];
	}
	ignore_signal_for_shell();
	return (1);
}
