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

t_bool	is_heredoc(t_list *lst_token)
{
	t_token	*token;
	t_token	*token_next;

	if (lst_token == NULL || lst_token->next == NULL)
		return (false);
	token = lst_token->content;
	token_next = lst_token->next->content;
	if (token->type == TOKEN_HEREDOC && token_next->type == TOKEN_LIM)
		return (true);
	return (false);
}

static int	create_temporary_file(void)
{
	int	fd;

	fd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror("open");
	return (fd);
}

void	sigint_handler(int signum)
{
	(void) signum;
	exit(0);
}

void	set_heredoc_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

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
