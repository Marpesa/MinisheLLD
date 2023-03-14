/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 02:38:34 by lmery             #+#    #+#             */
/*   Updated: 2023/03/14 07:03:02 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	ft_new_line(int signum, siginfo_t *info, void *context)
{
	(void)(info);
	(void)(context);

	g_status = 128 + signum;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ignore_signal_for_shell(void)
{
	struct sigaction	lazy_action;
	struct sigaction	new_sigint;

	ft_memset(&lazy_action, 0, sizeof(lazy_action));
	ft_memset(&new_sigint, 0, sizeof(new_sigint));
	lazy_action.sa_handler = SIG_IGN;
	new_sigint.sa_sigaction = ft_new_line;
	sigaction(SIGTSTP, &lazy_action, NULL);
	sigaction(SIGQUIT, &lazy_action, NULL);
	sigaction(SIGINT, &new_sigint, NULL);
}

void	ignore_sigint(void)
{
	struct sigaction	lazy_action;

	ft_memset(&lazy_action, 0, sizeof(lazy_action));
	lazy_action.sa_handler = SIG_IGN;
	sigaction(SIGINT, &lazy_action, NULL);
}

char	*rl_gets(void)
{
	char	*line_read;
	char	*prompt;

	line_read = NULL;
	prompt = _BLUE_LLD _BOLD "Minishe"_ORANGE "LLD"_WHITE "> " _END;
	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}
	line_read = readline(prompt);
	if (line_read && *line_read)
		add_history(line_read);
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
