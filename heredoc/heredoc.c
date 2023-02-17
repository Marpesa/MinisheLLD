/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:51:49 by gle-mini          #+#    #+#             */
/*   Updated: 2023/02/17 00:03:50 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

#define HEREDOC_FILE	"/tmp/.miniheLLD_heredoc"

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

	fd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		printf("fd error IL FAUT AJOUTER UN EXIT\n");
	return (fd);
}

static void	new_line()
{
	// write(STDERR_FILENO, "\n", 1);
    // rl_replace_line("", 0);
    // rl_on_new_line();
    // rl_redisplay();
	printf("^C\n");
	exit (0) ;
}
// 	int	*readline_exit;

// 	(void)signum;
// 	(void)si;
// 	(void)context;
// 	readline_exit = si->si_ptr;
// 	//*readline_exit = !(*readline_exit);
// 	//printf("number = %d\n", *readline_exit);
// 	//printf("number = %d\n", *readline_exit);
// 	//printf("SIIIIIIIIIIIIGGGGGGGGGGGINNNNNNNNNTTTTTT\n");
// }

// void	heredoc_signal()
// {
// 	struct sigaction	heredoc_quit;
// 	// union sigval		value;
// 	// struct sigaction new_sigint;
// 	// ft_memset(&new_sigint, 0, sizeof(new_sigint));
// 	// new_sigint.sa_sigaction = exit_heredoc;

// 	// ft_memset(&action_heredoc_quit, 0, sizeof(heredoc_quit));
// 	// action_heredoc_quit.sa_sigaction = heredoc_quit;
// 	// sigemptyset(&action_heredoc_quit.sa_mask);
// 	// action_heredoc_quit.sa_flags = SA_SIGINFO;
// 	// value.sival_ptr = readline_exit;
// 	// //sigaction(SIGINT, &action_heredoc_quit, &value);
// 	sigaction(SIGINT, &heredoc_quit, NULL);
// 	// sigqueue(getpid(), SIGINT, value);
// }

void	heredoc_prompt(char *eof)
{
	char	*input;
	int		pipefd[2];
	int	cpid;

	pipe (pipefd);
	cpid = fork ();
	struct sigaction	heredoc_quit;
	input = NULL;
	heredoc_quit.sa_sigaction = new_line;
	sigaction(SIGINT, &heredoc_quit, NULL);
	if (cpid == 0)
	{
		while (true)
		{
			input = readline("> ");
			// if (input == NULL)
			// {
			// 	printf ("tessst\n");
			// 	exit (0);
			// }
			if (ft_strncmp(input, eof, ft_strlen(eof)))
			{
			}
			else
			{
				printf("exit normal\n");
				free(input);
				exit (0);
			}	
		}	
	}
	if (input)
		free(input);
	close (pipefd[0]);
	close (pipefd[1]);
	ignore_signal_for_shell();
}

void	heredoc_open(char *eof)
{
	int	fd;

	// printf("eof: %s\n", eof);
	fd = create_temporary_file();
	heredoc_prompt(eof);
	close(fd);
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
