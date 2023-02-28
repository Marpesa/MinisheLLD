/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:16:13 by lmery             #+#    #+#             */
/*   Updated: 2023/02/28 21:28:10 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	g_status = 0;


void	ft_new_line()
{
	// (void)(sig);
	// (void)(info);
	// (void)(context);
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
	new_sigint.sa_sigaction = ft_new_line;

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


char **save_env(char **env)
{
    char **envp;
    int i;
	int	envc;

	i = 0;
	envc = 0;
	envp = NULL;
    // Count the number of environment variables
    while (env[i]) {
        envc++;
		i++;
    }

    // Allocate space for the array of pointers to environment variables
    envp = (char **)malloc((envc + 1) * sizeof(char *));
    if (!envp) {
        return NULL;
    }

    // Copy the environment variables to the array
    for (i = 0; env[i]; i++) {
        size_t len = ft_strlen(env[i]) + 1;
        envp[i] = (char *)malloc(len);
        if (!envp[i]) {
            // Free memory and return NULL on error
            while (--i >= 0) {
                free(envp[i]);
            }
            free(envp);
            return (NULL);
        }
        ft_strncpy(envp[i], env[i], len);
        envp[i][len-1] = '\0';  // Ensure null-termination
    }
    envp[envc] = NULL;
    return envp;
}

int main(int argc, char **argv, char **env)
{
	g_status = 0;
	(void)argc;
	(void)argv;
	t_list	*lst_token;
	t_list	*lst_command;
	char	*linebuffer;
	char 	**secret_env;

	rl_outstream = stderr;
	// ignore Ctrl-\ Ctrl-C Ctrl-Z signals
	linebuffer = NULL;
	lst_token = NULL;
	lst_command = NULL;
	// secret_env = NULL;
	ignore_signal_for_shell();
	secret_env = save_env(env);
	rl_outstream = stderr;
	while (true)
	{
		linebuffer = rl_gets();
		if (linebuffer == NULL)
		{
			ft_putstr_fd(_ORANGE "GOODBYE !\n" _END, 2);
			free_and_exit(lst_token, lst_command, &linebuffer, secret_env);
		}
		g_status = check_error_input(linebuffer);
		if (g_status == 0)
		{
			if (lexer(linebuffer, &lst_token) == -1)
				free_and_exit(lst_token, lst_command, &linebuffer, secret_env);
			if (ft_expand(lst_token, secret_env) == -1)
				free_and_exit(lst_token, lst_command, &linebuffer, secret_env);
			heredoc(lst_token);


			if (syntaxe_error(lst_token) != 0)
			{
				if (parser(lst_token, &lst_command) == -1)
					free_and_exit(lst_token, lst_command, &linebuffer, secret_env);
				ft_lstclear(&lst_token, del_token);
				if (linebuffer != NULL)
					free(linebuffer);
				linebuffer = NULL;
				exec(lst_command, &secret_env);
			}
		}
		free_all(&lst_token, &lst_command, &linebuffer);
	}
	rl_clear_history();
	return (1);
}
