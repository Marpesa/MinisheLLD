/* ************************************************************************** */
/*                                                                            */

/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:11:42 by gle-mini          #+#    #+#             */
/*   Updated: 2023/03/14 01:57:18 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	exec_builtin_no_fork(t_list **lst_current, \
		char ***env, int tmp, int prevpipe)
{
	t_command	*command;

	command = (*lst_current)->content;
	redirection(command);
	g_status = tmp;
	if (is_exit(command->word))
		close(prevpipe);
	tmp = execute_builtin(command->word, env, command->fd_out, \
			*lst_current);
	close_open_fd(command);
	close(prevpipe);
	if (tmp == -1)
		return (-1);
	*lst_current = (*lst_current)->next;
	if (tmp >= 0)
		g_status = tmp;
	return (1);
}

void	dup_prevpipe(int *prevpipe)
{
	*prevpipe = dup(STDIN_FILENO);
	if (*prevpipe == -1)
		perror("dup");
}

int	execute_in_pipe(t_list **lst_curr, int *prevpipe, t_list *lst_command, \
		char ***env)
{
	t_command	*command;

	if ((*lst_curr) != NULL)
		command = (*lst_curr)->content;
	if ((*lst_curr) != NULL && (*lst_curr)->next == NULL)
	{
		if (ft_last(command, env, *prevpipe, lst_command) == -1)
			return (-1);
	}
	else if ((*lst_curr) != NULL)
		if (ft_pipe(command, env, prevpipe, lst_command) == -1)
			return (-1);
	if ((*lst_curr) != NULL)
		(*lst_curr) = (*lst_curr)->next;
	return (1);
}

int	exec(t_list	*lst_command, char ***env, int tmp)
{
	t_list		*lst_current;
	t_command	*command;
	int			prevpipe;
	int			error_status;

	lst_current = lst_command;
	error_status = 0;
	dup_prevpipe(&prevpipe);
	while (lst_current != NULL)
	{
		command = lst_current->content;
		if (get_command_path(command, &error_status, *env) == -1)
			return (-1);
		if (check_valid_path(command, error_status, prevpipe) == 127)
			return (127);
		if (lst_current != NULL && ((ft_lstsize(lst_command) == 1 && \
					is_builtin(command->word)) || is_cd(command->word)))
			if (exec_builtin_no_fork(&lst_current, env, tmp, prevpipe) == -1)
				return (-1);
		if (execute_in_pipe(&lst_current, &prevpipe, lst_command, env) == -1)
			return (-1);
	}
	close(prevpipe);
	return (g_status);
}
