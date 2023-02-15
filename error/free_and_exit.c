/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:29:09 by lmery             #+#    #+#             */
/*   Updated: 2023/02/13 20:56:07 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static void	free_map(char **map)
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

static void	del_token(void *content)
{
	t_token *token;

	token = content;
	if (token->text)
		free(token->text);
	token->text = NULL;
	free(token);
	token = NULL;
}

static void	del_command(void *content)
{
	t_command	*cmd;

	cmd = content;
	free_map(cmd->word);
	free_map(cmd->redir);
	free(cmd);
	cmd = NULL;
}

void	free_and_exit(t_list *lst_token, t_list *lst_command, char **linebuffer)
{
	ft_lstclear(&lst_token, del_token);
	ft_lstclear(&lst_command, del_command);
	if (*linebuffer != NULL)
		free(*linebuffer);
	*linebuffer = NULL;
}