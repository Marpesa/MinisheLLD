/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:16:13 by lmery             #+#    #+#             */
/*   Updated: 2023/02/13 17:12:22 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minisheLLD.h"

static void	new_line(int sig, siginfo_t *info, void *context)
{
	(void)(sig);
	(void)(info);
	(void)(context);
	write(STDERR_FILENO, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void ignore_signal_for_shell()
{
	// Set up the sigaction structure
	struct sigaction lazy_action;
	struct sigaction new_sigint;
	ft_memset(&lazy_action, 0, sizeof(lazy_action));
	ft_memset(&new_sigint, 0, sizeof(new_sigint));
	lazy_action.sa_handler = SIG_IGN;
	new_sigint.sa_sigaction = new_line;

	// ignore "Ctrl+Z"
	sigaction(SIGTSTP, &lazy_action, NULL);
	
	// ignore "Ctrl+\"
	sigaction(SIGQUIT, &lazy_action, NULL);
	
	// new action "Ctrl+C"
	sigaction(SIGINT, &new_sigint, NULL);
}

/* A static variable for holding the line. */
//static char *line_read = (char *)NULL;

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
char	*rl_gets ()
{
	char *line_read;

	line_read = NULL;
	/* If the buffer has already been allocated, return the memory
     to the free pool. */
	char* prompt = _BLUE_LLD _BOLD"Minishe"_ORANGE"LLD"_WHITE"> " _END;
	if (line_read)
    {
      free (line_read);
      line_read = (char *)NULL;
    }

	/* Get a line from the user. */
	line_read = readline(prompt);

	/* If the line has any text in it, save it on the history. */
	if (line_read && *line_read)
		add_history (line_read);

	return (line_read);
}



int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_list	*lst_token;
	t_list	*lst_command;
	char	*linebuffer;

	// ignore Ctrl-\ Ctrl-C Ctrl-Z signals
	linebuffer = NULL;
	lst_token = NULL;
	lst_command = NULL;
	ignore_signal_for_shell();
	while (true)
	{

		linebuffer = rl_gets();
		if (linebuffer == NULL)
		{
			printf(_ORANGE "GOODBYE !\n" _END);
			free_and_exit(lst_token, lst_command, &linebuffer);
			//OUBLIE PAS DE GRERER LEXIT GUGU
			exit(0);
		}
		if (check_error_input(linebuffer))
		{
			if (lexer(linebuffer, &lst_token) == -1)
				free_and_exit(lst_token, lst_command, &linebuffer);
			if (ft_expand(lst_token, env) == -1)
				free_and_exit(lst_token, lst_command, &linebuffer);
			heredoc(lst_token);
			if (syntaxe_error(lst_token) == -1)
				free_and_exit(lst_token, lst_command, &linebuffer);
			if (parser(lst_token, &lst_command) == -1)
				free_and_exit(lst_token, lst_command, &linebuffer);
			exec(lst_command, env);
		}
		free_all(&lst_token, &lst_command, &linebuffer);
	}
	rl_clear_history();
	return (1);
}
