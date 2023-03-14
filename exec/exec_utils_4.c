/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:36:58 by lmery             #+#    #+#             */
/*   Updated: 2023/03/14 07:05:13 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

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

int	execute_child_last(t_command *command, int prevpipe, char ***env, \
		t_list *lst_command_head)
{
	redirection(command);
	if (command->fd_out != STDOUT_FILENO)
		if (dup2(command->fd_out, STDOUT_FILENO) == -1)
			perror("dup2");
	if (command->fd_in == STDIN_FILENO)
		command->fd_in = prevpipe;
	if (dup2(command->fd_in, STDIN_FILENO))
		perror("dup2");
	close (prevpipe);
	if (execute_command(command, env, lst_command_head) == -1)
		return (-1);
	return (1);
}

void	restore_default_signal_behavior()
{
    struct sigaction sa;

    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        perror("Error restoring default behavior of SIGINT");
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
        perror("Error restoring default behavior of SIGKILL");
    if (sigaction(SIGSTOP, &sa, NULL) == -1)
        perror("Error restoring default behavior of SIGSTOP");
}

int	ft_last(t_command *command, char ***env, int prevpipe, \
		t_list *lst_command_head)
{
	pid_t	cpid;
	int		status;

	cpid = fork();
	if (cpid == -1)
		perror("fork");
	else if (cpid == 0)
	{
		restore_default_signal_behavior();
		if (execute_child_last(command, prevpipe, env, lst_command_head) == -1)
			return (-1);
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

int	get_command_path(t_command *command, int *error_status, char **env)
{
	if (is_builtin(command->word) == 0)
	{
		if (get_absolute_path(command->word, error_status, env) == -1)
			return (-1);
	}
	return (1);
}

int	check_valid_path(t_command *command, int error_status, int prevpipe)
{
	if (error_status == 2)
	{
		ft_putstr_fd(_ORANGE2 "MinisheLLD : ", 2);
		ft_putstr_fd((command->word)[0], 2);
		ft_putstr_fd(" : no such file or directory\n" _END, 2);
		close(prevpipe);
		return (127);
	}
	return (1);
}
