/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 03:06:28 by lmery             #+#    #+#             */
/*   Updated: 2023/03/12 03:10:43 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

t_bool	is_heredoc(t_list *lst_token)
{
	t_token	*token;
	t_token	*token_next;

	if (lst_token == NULL || lst_token->next == NULL)
		return (false);
	token = lst_token->content;
	token_next = lst_token->next->content;
	if (token->type == TOKEN_HEREDOC && token_next->type == TOKEN_LIM)
		return (true);
	return (false);
}

int	create_temporary_file(void)
{
	int	fd;

	fd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror("open");
	return (fd);
}

void	sigint_handler(int signum)
{
	(void) signum;
	exit(0);
}

void	set_heredoc_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
