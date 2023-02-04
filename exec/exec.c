#include "minisheLLD.h"

static void	pipe_checker(t_list	*lst_command, int *old_pipe_in)
{
	t_command	*command;
	
	while (lst_command)
	{
		command = lst_command->content;
		if (command->
	}
}

void	execute(t_list *lst_command)
{
	int	old_pipe_in;
	
	if (command == NULL)
		return ;
	*old_pipe_in = 0;
	pipe_checker(lst_command, &old_pipe_in);
	if (old_pipe_in != 0)
		close(old_pipe_in);
}
