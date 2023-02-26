/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:51:49 by gle-mini          #+#    #+#             */
/*   Updated: 2023/02/27 00:01:31 by lmery            ###   ########.fr       */
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
/*
static void	heredoc_quit(int signum, siginfo_t *si, void *context)
{
	(void)signum;
	(void)si;
	(void)context;
	if (g_status == 1)
		kill(getpid(), SIGTERM);
//		exit (EXIT_SUCCESS);
	g_status = 1;
	//printf("number = %d\n", *readline_exit);
	//printf("number = %d\n", *readline_exit);
	//printf("SIIIIIIIIIIIIGGGGGGGGGGGINNNNNNNNNTTTTTT\n");
}
*/


/*
void	heredoc_signal()
{
	struct sigaction	action_heredoc_quit;
	union sigval		value;

	ft_memset(&action_heredoc_quit, 0, sizeof(heredoc_quit));
	action_heredoc_quit.sa_sigaction = heredoc_quit;
	sigemptyset(&action_heredoc_quit.sa_mask);
	action_heredoc_quit.sa_flags = SA_SIGINFO;
	//sigaction(SIGINT, &action_heredoc_quit, &value);
	sigaction(SIGINT, &action_heredoc_quit, NULL);
	sigqueue(getpid(), SIGINT, value);
	


	struct sigaction sa_default;
	sa_default.sa_handler = SIG_DFL;
	sigemptyset(&sa_default.sa_mask);
	sa_default.sa_flags = 0;
	sigaction(SIGINT, &sa_default, NULL);
}
*/

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

void	heredoc_prompt(char *lim)
{
	char	*input;
	int		pid;
	(void) lim;
	input = NULL;
	g_status = 0;
	pid = fork();
	if (pid == 0)
	{
		struct sigaction sa;
        sa.sa_handler = sigint_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);


		while (true)
		{
			if (check_sigint_heredoc() == 0)
			{
				printf("quit by sigint\n");
				break;
			}
			input = readline("> ");
			
			if (input == NULL)
			{
				if (check_sigint_heredoc() == 0)
				{
					printf("quit by sigint\n");
					break;
				}
				//Entre dedans quand il y a un ctrl + D
				printf("OUBLIE PAS DE GERER LERREUR GUGU\n");
				//close(fd);
				break ;
			}
			
			if ((ft_strncmp(input, lim, ft_strlen(lim)) == 0))
			{
				if (check_sigint_heredoc() == 0)
				{
					printf("quit by sigint\n");
					break;
				}
				//close(fd);
				//readline_exit = true;
				printf("exit normal\n");
				free(input);
				input = NULL;
				break ;
			}
			if (g_status == 128 + SIGINT)
			{

				printf("quit by sigint\n");
				break;
			}
			
		}
	}
	else
	{
		int status;

		 waitpid(pid, &status, 0);
		 //kill(pid, SIGTERM);

        // check if the child process terminated successfully
		/*
        if (WIFEXITED(status)) {
            printf("Child process with PID %d terminated with status %d\n", pid, WEXITSTATUS(status));
        } else {
            printf("Child process with PID %d terminated abnormally\n", pid);
        }
		*/
	}
	if (input)
		free(input);
	//close (pipefd[0]);
	//close (pipefd[1]);
	ignore_signal_for_shell();
}

void	heredoc_open(char *lim)
{
	int	fd;

	printf("eof: %s\n", lim);
	fd = create_temporary_file();
	heredoc_prompt(lim);
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
