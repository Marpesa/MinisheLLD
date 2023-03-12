/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:29:14 by lmery             #+#    #+#             */
/*   Updated: 2023/03/12 00:36:20 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

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
	int	new_in;

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
