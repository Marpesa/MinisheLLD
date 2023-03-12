/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:16:13 by lmery             #+#    #+#             */
/*   Updated: 2023/03/12 02:46:58 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	g_status = 0;

void	init_secret_env(char **env, char ***envp)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	while (env[i])
	{
		len = ft_strlen(env[i]) + 1;
		(*envp)[i] = (char *)malloc(len);
		if (!(*envp)[i])
		{
			while (--i >= 0)
				free((*envp)[i]);
			free((*envp));
			ft_print_error(_ORANGE2 "Malloc error while creating secret env\n"\
			_END, NULL, NULL);
			exit(1);
		}
		ft_strncpy((*envp)[i], env[i], len);
		(*envp)[i][len - 1] = '\0';
		i++;
	}
}

char	**save_env(char **env)
{
	char	**envp;
	int		envc;

	envc = 0;
	envp = NULL;
	while (env[envc])
		envc++;
	envp = (char **)malloc((envc + 2) * sizeof(char *));
	if (!envp)
	{
		ft_print_error(_ORANGE2 "Malloc error while creating secret env\n"\
		_END, NULL, NULL);
		exit(1);
	}
	envp[0] = gstat_in_env(envp[0]);
	if (env[0] == NULL)
	{
		envp[1] = NULL;
		return (envp);
	}
	init_secret_env(env, &envp);
	envp[envc] = NULL;
	return (envp);
}

// void	lexer_to_exec(t_list *lst_token, t_list *lst_command, char *linebuffer, char **sec_env)
// {
// 	g_status = 1;
// 	if (lexer(linebuffer, &lst_token) == -1)
// 		free_and_exit(lst_token, lst_command, &linebuffer, sec_env);
// 	if (ft_expand(lst_token, sec_env) == -1)
// 		free_and_exit(lst_token, lst_command, &linebuffer, sec_env);
// 	heredoc(lst_token, linebuffer, sec_env);
// 	if (syntaxe_error(lst_token) != 0)
// 	{
// 		if (parser(lst_token, &lst_command) == -1)
// 			free_and_exit(lst_token, lst_command, &linebuffer, sec_env);
// 		ft_lstclear(&lst_token, del_token);
// 		if (linebuffer != NULL)
// 			free(linebuffer);
// 		linebuffer = NULL;
// 		g_status = 0;
// 		g_status = exec(lst_command, &sec_env, prev_gstat);
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	t_list	*lst_token;
	t_list	*lst_command;
	char	*linebuffer;
	char	**sec_env;
	int		prev_gstat;

	(void)argc;
	(void)argv;
	rl_outstream = stderr;
	linebuffer = NULL;
	lst_token = NULL;
	lst_command = NULL;
	ignore_signal_for_shell();
	sec_env = save_env(env);
	rl_outstream = stderr;
	while (true)
	{
		prev_gstat = g_status;
		free(sec_env[0]);
		sec_env[0] = gstat_in_env(sec_env[0]);
		linebuffer = rl_gets();
		if (linebuffer == NULL)
		{
			ft_putstr_fd(_ORANGE "GOODBYE !\n" _END, 2);
			free_and_exit(lst_token, lst_command, &linebuffer, sec_env);
		}
		g_status = check_error_input(linebuffer);
		if (g_status == 0)
		{
			g_status = 1;
			if (lexer(linebuffer, &lst_token) == -1)
				free_and_exit(lst_token, lst_command, &linebuffer, sec_env);
			if (ft_expand(lst_token, sec_env) == -1)
				free_and_exit(lst_token, lst_command, &linebuffer, sec_env);
			heredoc(lst_token, linebuffer, sec_env);
			if (syntaxe_error(lst_token) != 0)
			{
				if (parser(lst_token, &lst_command) == -1)
					free_and_exit(lst_token, lst_command, &linebuffer, sec_env);
				ft_lstclear(&lst_token, del_token);
				if (linebuffer != NULL)
					free(linebuffer);
				linebuffer = NULL;
				g_status = 0;
				g_status = exec(lst_command, &sec_env, prev_gstat);
			}
		}
		free_all(&lst_token, &lst_command, &linebuffer);
	}
	rl_clear_history();
	return (g_status);
}
