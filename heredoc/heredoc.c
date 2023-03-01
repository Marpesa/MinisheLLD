/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:51:49 by gle-mini          #+#    #+#             */
/*   Updated: 2023/03/01 18:55:48 by gle-mini         ###   ########.fr       */
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

//t_bool is_already_heredoc_file -> append_heredoc : create_heredoc

//CHANGE LE NOM DE LA FONCTION
static int	create_temporary_file(void)
{
	int	fd;

	fd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror("open");
	return (fd);
}

int	check_sigint_heredoc()
{
	if (g_status == 128 + SIGINT)
		exit(0);
	return (1);
}
void sigint_handler() {
    // Perform any necessary cleanup and exit the process
    exit(0);
}

void set_heredoc_signal()
{
	struct sigaction sa;
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	heredoc_prompt(char *lim)
{
	char	*input;
	int		pid;
	int		status;
	int		fd;

	(void) lim;
	input = NULL;
	g_status = 0;
	pid = fork();
	if (pid == 0)
	{
		set_heredoc_signal();
		fd = create_temporary_file();
		while (true)
		{
			input = readline("> ");
			if (input == NULL)
			{
				printf("OUBLIE PAS DE GERER LERREUR GUGU\n");
				break ;
			}
			if ((ft_strncmp(input, lim, ft_strlen(lim)) == 0))
			{
				printf("exit normal\n");
				free(input);
				input = NULL;
				break ;
			}
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
			free(input);
		}
		close(fd);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

void	heredoc_open(char *lim)
{
		heredoc_prompt(lim);
}

void	heredoc(t_list *lst_token)
{
	t_token	*token;

	while (lst_token)
	{
		if (is_heredoc(lst_token))
		{
			token = lst_token->next->content;
			heredoc_open(token->text);
		}
		lst_token = lst_token->next;
	}
}
