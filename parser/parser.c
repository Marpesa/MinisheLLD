/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:20:24 by lmery             #+#    #+#             */
/*   Updated: 2023/01/16 19:06:12 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

/*
cd
export
unset 
exit[___]
*/

t_command	*parser(t_list *lst_token)
{
	t_token	*token;
	t_command *command;
	int	i;
	int	j;

	j = 0;
	i = 0;
	command = malloc(sizeof(t_command));
	if (!command)
		return (0);
	command->cmd = malloc(sizeof(char *) * ft_lstsize(lst_token) + 1);
	if (! command->cmd)
		return (0);
	command->redir = malloc(sizeof(char *) * ft_lstsize(lst_token) + 1);
	if (! command->redir)
		return (0);
	// Gestion garbage collector 
	while (lst_token)
	{
		token = lst_token->content;
		if (token->type == TOKEN_WORD)
		{
			command->cmd[i] = ft_strdup(token->text);
			i++;
		}
		if (token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_REDIRECT_OUT)
		{
			command->redir[j] = ft_strdup(token->text);
			j++;
		}
		lst_token = lst_token->next;
	}
	command->cmd[i] = NULL;
	command->redir[j] = NULL;
	//printf (_BOLD "TEST = %s\n"_END, command->cmd[0]);
	return (command);
}