/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 03:11:42 by lmery             #+#    #+#             */
/*   Updated: 2023/03/12 03:11:55 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

void	print_map(char **map, int fd)
{
	size_t		i;

	i = 0;
	if (map == NULL)
		return ;
	while (i < ft_maplen_secure(map))
	{
		ft_putstr_fd(map[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	ft_putstr_fd("\n", fd);
}

void	print_command(t_command *command, int fd)
{
	ft_putstr_fd(_BOLD _BLUE_LLD"\n------- WORD --------\n"_END, fd);
	print_map(command->word, fd);
	ft_putstr_fd(_BOLD _BLUE_LLD"\n------- REDIR -------\n" _END, fd);
	print_map(command->redir, fd);
}

void	print_lst_command(t_list *lst_command, int fd)
{
	t_command	*command;

	while (lst_command != NULL)
	{
		command = lst_command->content;
		print_command(command, fd);
		lst_command = lst_command->next;
		ft_putstr_fd("__________________\n", fd);
	}
}

void	print_lst_token(t_list *head)
{
	t_token	*token;

	while (head)
	{
		token = head->content;
		printf("token type: %s\ntoken text: %s\n", \
		ft_get_token_type(token->type), token->text);
		head = head->next;
	}
}
