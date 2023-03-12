/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:51:49 by gle-mini          #+#    #+#             */
/*   Updated: 2023/03/12 03:28:25 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	check_input(char *input)
{
	if (input == NULL)
		return (1);
	return (0);
}

int	manage_heredoc(char *input, char *lim, int fd)
{
	input = readline("> ");
	if (check_input(input))
		return (1);
	if ((ft_strncmp(input, lim, ft_strlen(lim)) == 0))
	{
		free(input);
		input = NULL;
		return (1);
	}
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
	free(input);
	return (0);
}

void	heredoc_open(char *lim, t_list *lst_token_head, \
		char **secret_env)
{
	char	*input;
	int		pid;
	int		status;
	int		fd;

	input = NULL;
	g_status = 0;
	pid = fork();
	if (pid == 0)
	{
		set_heredoc_signal();
		fd = create_temporary_file();
		while (true)
		{
			if (manage_heredoc(input, lim, fd))
				break ;
		}
		close(fd);
		ft_lstclear(&lst_token_head, del_token);
		ft_free_map(secret_env);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}

void	heredoc(t_list *lst_token_head, char **secret_env)
{
	t_token	*token;
	t_list	*lst_token;

	lst_token = lst_token_head;
	while (lst_token)
	{
		if (is_heredoc(lst_token))
		{
			token = lst_token->next->content;
			heredoc_open(token->text, lst_token_head, secret_env);
		}
		lst_token = lst_token->next;
	}
}
