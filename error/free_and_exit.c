/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:29:09 by lmery             #+#    #+#             */
/*   Updated: 2023/02/18 18:33:13 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	if (map == NULL)
		return ;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

void	del_token(void *content)
{
	t_token *token;

	token = content;
	if (token->text)
		free(token->text);
	token->text = NULL;
	free(token);
	token = NULL;
}

void	del_command(void *content)
{
	t_command	*cmd;

	cmd = content;
	ft_free_map(cmd->word);
	ft_free_map(cmd->redir);
	free(cmd);
	cmd = NULL;
}

void	free_all(t_list **lst_token, t_list **lst_command, char **linebuffer)
{
	if(lst_token)
		ft_lstclear(lst_token, del_token);
	if(lst_command != NULL)
		ft_lstclear(lst_command, del_command);
	if (*linebuffer != NULL)
		free(*linebuffer);
	*linebuffer = NULL;
}

void	free_and_exit(t_list *lst_token, t_list *lst_command, char **linebuffer, char **env)
{
	ft_lstclear(&lst_token, del_token);
	ft_lstclear(&lst_command, del_command);
	ft_free_map(env);
	if (*linebuffer != NULL)
		free(*linebuffer);
	*linebuffer = NULL;
	rl_clear_history();
	exit(0);
}
