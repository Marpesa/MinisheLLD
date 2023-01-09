/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:51:49 by gle-mini          #+#    #+#             */
/*   Updated: 2023/01/09 17:56:07 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

#define HEREDOC_FILE	"/tmp/.miniheLLD_heredoc"

t_bool	is_heredoc(t_list *lst_token)
{
	t_token *token;
	t_token *token_next;

	if (lst_token == NULL || lst_token->next == NULL)
		return (false);
	token = lst_token->content;
	token_next = lst_token->next->content;
	if (token->type == TOKEN_HEREDOC && token_next->type == TOKEN_EOF)
		return (true);
	return (false);
}


//t_bool is_already_heredoc_file -> append_heredoc : create_heredoc

//CHANGE LE NOM DE LA FONCTION
static int	create_temporary_file(void)
{
	int	fd;

	fd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		printf("fd error IL FAUT AJOUTER UN EXIT\n");
	return (fd);
}

static void	heredoc_quit(int signum, siginfo_t *si, void *context)
{
	(void)signum;
	(void)si;
	(void)context;

	//rl_done = 1;
	t_bool *readline_exit = si->si_ptr;
	*readline_exit = false;
	printf("rl_done is set to 1\n");
}


void	heredoc_signal(t_bool *readline_exit)
{
	struct sigaction action_heredoc_quit;
	
	ft_memset(&action_heredoc_quit, 0, sizeof(heredoc_quit));
	action_heredoc_quit.sa_sigaction = heredoc_quit;

	sigemptyset(&action_heredoc_quit.sa_mask);
  	action_heredoc_quit.sa_flags = SA_SIGINFO;


	union sigval value;
	value.sival_ptr = readline_exit;
	sigaction(SIGINT, &action_heredoc_quit, NULL);
	//sigaction(SIGINT, &action_heredoc_quit, &value);
	//sigqueue(getpid(), SIGINT, value);
}

void	heredoc_prompt(char *eof)
{
	char *input;
	t_bool readline_exit;

	readline_exit = false;
	input = NULL;
	write(1, "test\n", 5);
	heredoc_signal(&readline_exit);
	write(1, "test\n", 5);
	while (readline_exit == false)
	{
		input = readline("> ");
		if (input == NULL)
		{
			//Entre dedans quand il y a un ctrl + D
			printf("OUBLIE PAS DE GERER LERREUR GUGU\n");
			//close(fd);
			break;
		}
		if (ft_strncmp(input, eof, ft_strlen(eof)))
		{
		}
		else 
		{
			//close(fd);
			readline_exit = true;
			printf("exit normal\n");
			free(input);
			break;
		}
	}
	ignore_signal_for_shell();
}

void	heredoc_open(char *eof)
{
	int	fd;

	printf("eof: %s\n", eof);
	fd = create_temporary_file();
	heredoc_prompt(eof);
	close(fd);
}

void	heredoc(t_list *lst_token)
{
	t_token *token;

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
