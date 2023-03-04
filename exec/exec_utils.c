/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:16:50 by lmery             #+#    #+#             */
/*   Updated: 2023/03/04 18:57:09 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

int	is_g_stat(char *cmd)
{
	int	len;
	if (!cmd)
		return (false);
	len = ft_strlen_secure(cmd);
	if ((ft_strncmp(cmd, "echo $?", len) == 0))
		return (1);
	return (0);
}

// void	g_stat_export(char *str, char ***env)
// {
// 	char	**new_env;
// 	char	**str_env;
// 	char	**cmd;
// 	// int		i;
// 	// int		j;

// 	// i = 0;
// 	// j = 0;
// 	cmd = malloc(sizeof (char *) * 2);
// 	if (!cmd)
// 		ft_print_error(_ORANGE2 "Malloc : Error\n" _END, NULL, NULL);
// 	cmd[0] = strdup(str);
// 	cmd[1] = NULL;
// 	// allready_in_env(&cmd, env, &j, i) == 1
// 	end_export(&new_env, &str_env, env, cmd[0]);
// 	free(cmd);
// }

void	get_g_status()
{
	char	*c;

	c = ft_itoa(g_status);
	// g_stat_export(c, env);
	ft_putstr_fd(c, 2);
	// ft_putstr_fd("\n", 2);

	free(c);
}

int	builtin_outpipe(t_command *command, char ***env, t_list	*lst_command)
{

	if (is_cd(command->word))
	{
		builtin_cd(command->word);
		return(g_status);
	}
	if (is_export(command->word))
	{
		builtin_export(command->word, env);
		return(g_status);
	}
	if (is_unset(command->word))
	{
		builtin_unset(command->word, env);
		return(g_status);
	}
	if (is_pwd(command->word))
	{
		builtin_pwd(command->word, env, lst_command);
		return(g_status);
	}
	return(-1);
}