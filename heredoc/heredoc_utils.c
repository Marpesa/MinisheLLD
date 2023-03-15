/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 03:06:28 by lmery             #+#    #+#             */
/*   Updated: 2023/03/15 11:43:05 by gle-mini         ###   ########.fr       */
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

void	set_heredoc_signal(void)
{
	struct sigaction	lazy_action;

	ft_memset(&lazy_action, 0, sizeof(lazy_action));
	lazy_action.sa_handler = SIG_IGN;
	sigaction(SIGTSTP, &lazy_action, NULL);
	sigaction(SIGQUIT, &lazy_action, NULL);
	sigaction(SIGINT, &lazy_action, NULL);
}

void	heredoc_routine(char *input, char *lim, int *fd)
{
	set_heredoc_signal();
	*fd = create_temporary_file();
	while (true)
	{
		if (manage_heredoc(input, lim, *fd))
			break ;
	}
}
