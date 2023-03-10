/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:16:13 by lmery             #+#    #+#             */
/*   Updated: 2023/03/10 19:19:12 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	g_status = 0;


// void set_status_to_130()
// {
// 	g_status = 130;
// }

void	ft_new_line()
{
	// (void)(sig);
	// (void)(info);
	// (void)(context);
	// printf("gstat = %d\n", g_status);
	write(STDERR_FILENO, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
	// set_status_to_130();
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

void ignore_sigint()
{
	struct sigaction lazy_action;
	ft_memset(&lazy_action, 0, sizeof(lazy_action));
	lazy_action.sa_handler = SIG_IGN;
	
	// new action "Ctrl+C"
	sigaction(SIGINT, &lazy_action, NULL);

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

char	*gstat_in_env(char *env)
{
	char	*str;
	char	*gstat;
	
	gstat = ft_itoa(g_status);
	str = ft_strjoin("?=", gstat);
	env = ft_strdup(str);
	free(str);
	free(gstat);
	return (env);
}

char	**save_env(char **env)
{
	char	**envp;
	int		i;
	int		envc;

	i = 0;
	envc = 0;
	envp = NULL;
	while (env[i]) 
	{
		envc++;
		i++;
	}
	envp = (char **)malloc((envc + 2) * sizeof(char *));
	if (!envp)
	{
		ft_print_error(_ORANGE2 "Malloc error while creating secret env\n" _END, NULL, NULL);
		exit (1);
	}
	envp[0] = gstat_in_env(envp[0]);
	if (env[0] == NULL)
	{
		envp[1] = NULL;
		return (envp);
	}
	i = 1;
	while(env[i]) 
	{
		size_t len = ft_strlen(env[i]) + 1;
		envp[i] = (char *)malloc(len);
		if (!envp[i]) 
		{
			while (--i >= 0) 
				free(envp[i]);
			free(envp);
			ft_print_error(_ORANGE2 "Malloc error while creating secret env\n" _END, NULL, NULL);
			exit (1);
		}
		ft_strncpy(envp[i], env[i], len);
		envp[i][len-1] = '\0';
		i++;
	}
	envp[envc] = NULL;
	return envp;
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_list	*lst_token;
	t_list	*lst_command;
	char	*linebuffer;
	char 	**secret_env;
	int		prev_gstat;

	rl_outstream = stderr;
	linebuffer = NULL;
	lst_token = NULL;
	lst_command = NULL;
	ignore_signal_for_shell();
	secret_env = save_env(env);
	rl_outstream = stderr;
	while (true)
	{
		prev_gstat = g_status;
		free(secret_env[0]);
		secret_env[0] = gstat_in_env(secret_env[0]);
		linebuffer = rl_gets();
		if (linebuffer == NULL)
		{
			ft_putstr_fd(_ORANGE "GOODBYE !\n" _END, 2);
			free_and_exit(lst_token, lst_command, &linebuffer, secret_env);
		}
		g_status = check_error_input(linebuffer);
		if (g_status == 0)
		{
			g_status = 1;
			if (lexer(linebuffer, &lst_token) == -1)
				free_and_exit(lst_token, lst_command, &linebuffer, secret_env);
			if (ft_expand(lst_token, secret_env) == -1)
				free_and_exit(lst_token, lst_command, &linebuffer, secret_env);
			//print_lst_token(lst_token);

			heredoc(lst_token, linebuffer, secret_env);


			if (syntaxe_error(lst_token) != 0)
			{
				if (parser(lst_token, &lst_command) == -1)
					free_and_exit(lst_token, lst_command, &linebuffer, secret_env);
				ft_lstclear(&lst_token, del_token);
				if (linebuffer != NULL)
					free(linebuffer);
				linebuffer = NULL;
				g_status = 0;
				g_status = exec(lst_command, &secret_env, prev_gstat);
			}
		}
		free_all(&lst_token, &lst_command, &linebuffer);
	}
	rl_clear_history();
	return (g_status);
}
