/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:16:13 by lmery             #+#    #+#             */
/*   Updated: 2023/02/08 20:37:21 by lmery            ###   ########.fr       */
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
	t_list *lst_token;

	// ignore Ctrl-\ Ctrl-C Ctrl-Z signals
	ignore_signal_for_shell();

	char* linebuffer;

	linebuffer = NULL;
	while (true)
	{

		linebuffer = rl_gets();
		//printf("You enter :%s\n", linebuffer);

		// linebuffer is NULL if you press "Ctrl+D"
		if (linebuffer == NULL)
		{
			printf(_ORANGE "GOODBYE !\n");
			//OUBLIE PAS DE GRERER LEXIT GUGU
			exit(1);
		}
		if (check_error_input(linebuffer))
		{
			lst_token = lexer(linebuffer);
			//lst_print_token(lst_token);
		}
		//printf("---------------------------------------------------------\n");
		ft_expand(lst_token, env);
		//lst_print_token(lst_token);
		heredoc(lst_token);
		syntaxe_error(lst_token);
		//printf("============PRINT_LST_COMMAND_TEST============\n");
		t_list *lst_command = parser(lst_token);
		exec(lst_command, env);
		
		//print_lst_command(lst_command);
		//lst_print_command(parser(lst_token));
		// usleep (800);
	}
	rl_clear_history();
	free(linebuffer);
	return (0);
}
