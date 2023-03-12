/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 04:30:12 by lmery             #+#    #+#             */
/*   Updated: 2023/03/12 04:30:59 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	init_value(char **linebuffer, t_list **lst_token, t_list **lst_command)
{
	rl_outstream = stderr;
	*linebuffer = NULL;
	*lst_token = NULL;
	*lst_command = NULL;
	ignore_signal_for_shell();
}

void	init_status_and_get_linebuffer(int *prev_gstat, char ***sec_env, \
		char **linebuffer)
{
	*prev_gstat = g_status;
	free((*sec_env)[0]);
	(*sec_env)[0] = gstat_in_env((*sec_env)[0]);
	*linebuffer = rl_gets();
}

void	exit_minishell(char **linebuffer, t_list **lst_token, \
		t_list **lst_command, char ***sec_env)
{
	if (*linebuffer == NULL)
	{
		ft_putstr_fd(_ORANGE "GOODBYE !\n" _END, 2);
		free_and_exit(*lst_token, *lst_command, linebuffer, *sec_env);
	}
}
