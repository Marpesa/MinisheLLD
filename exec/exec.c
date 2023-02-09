#include "minisheLLD.h"


//PENSER A GERER LE CAS SI ON NE TROUVE PAS LE BINAIRE
static void	get_absolute_path(char **cmd)
{
	char	*path = NULL;
	char	*bin = NULL;
	char	*path_split = NULL;

	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		path = ft_strdup(getenv("PATH"));
		if (path == NULL)
			path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
		path_split = strtok(path, ":");
		while (path_split != NULL)
		{	
			bin = (char *)ft_calloc(sizeof(char), (ft_strlen(path_split) + 1 + ft_strlen(cmd[0]) + 1));
			if(bin == NULL)
				break ;
			ft_strncat(bin, path_split, ft_strlen_secure(bin) + ft_strlen_secure(path_split));
			ft_strncat(bin, "/", ft_strlen_secure(bin) + 1);
			ft_strncat(bin, cmd[0], ft_strlen_secure(bin) + ft_strlen_secure(cmd[0]));
			if(access(bin, F_OK) == 0)
				break ;
			path_split = strtok(NULL, ":");
			free(bin);
			bin = NULL;
		}
		free(path);
		path = NULL;
		free(cmd[0]);
		cmd[0] = NULL;
		cmd[0] = bin;
		free(path);
		path = NULL;

	}
}

/*
void execute_command_with_redirection(char **command, char **redirection, char **env, int output_fd, int input_fd, int child_pid)
{
    int redirect_index;

	get_absolute_path(command);
    if (child_pid == 0)
	{
        // Child process
        redirect_index = 0;
		
		//close(output_fd);
        while (redirection != NULL && redirection[redirect_index] != NULL) {
            if (ft_strncmp(redirection[redirect_index], "<", 1) == 0) {
                // Standard input redirection
                input_fd = open(redirection[redirect_index + 1], O_RDONLY);
                if (input_fd == -1)
				{
                    perror("open");
                }
                if (dup2(input_fd, STDIN_FILENO) == -1)
				{
                    perror("dup2");
                }
                if (close(input_fd) == -1)
				{
                    perror("close");
                }
                redirect_index += 2;
            }
			else if (ft_strncmp(redirection[redirect_index], ">", 1) == 0)
			{
                // Standard output redirection
            	output_fd = open(redirection[redirect_index + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (output_fd == -1) {
                    perror("open");
                }
                if (dup2(output_fd, STDOUT_FILENO) == -1) {
                    perror("dup2");
                }
                if (close(output_fd) == -1) {
                    perror("close");
                }
                redirect_index += 2;
            }

			else {
				// Invalid redirection
				printf("ERROR\n");
				fprintf(stderr, "Error: Invalid redirection operator '%s'\n", redirection[redirect_index]);
			}
		}
		execve(command[0], command, env);
	}
}

void	exec(t_list	*lst_command, char **env)
{
	int	fd[2];
    int pid;
	int stat_loc;
	int	index;
	t_list *head = lst_command;
	t_command	*command;

	index = 0;
    while (lst_command != NULL)
	{
		command = lst_command->content;
        if (pipe(fd) == -1) {
            perror("pipe");
            //exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            //exit(EXIT_FAILURE);
        }

        if (pid == 0) 
		{
			if (index == 0)
			{
				//close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
      			execute_command_with_redirection(command->word, command->redir, env, fd[1], STDIN_FILENO, pid);
			}
			else if (ft_lstsize(lst_command) == 1)
			{
				//close(fd[1]);
				dup2(fd[0], STDIN_FILENO);
      			execute_command_with_redirection(command->word, command->redir, env, STDOUT_FILENO, fd[1], pid);
			}
			else
			{
      			execute_command_with_redirection(command->word, command->redir, env, fd[1], fd[0], pid);
			}
        } 
		else 
		{
            // Parent process
            //close(fd[1]);
            //dup2(fd[0], STDIN_FILENO);
        }
		lst_command = lst_command->next;
		index++;
    }
	lst_command = head;
	while (lst_command != NULL)
	{
		waitpid(-1, &stat_loc, 0);
		lst_command = lst_command->next;
	}
	
}
*/

/*
void exec_pipe(int	pid, int *child_fd)
{
	if (pid == 0)
	{
		dup2(child_fd[1], STDOUT_FILENO);
		close(child_fd[0]);
		close(child_fd[1]);
	}
}
*/

void	create_pipe(int	*old_pipe_in, t_list *lst_current)
{
	int	new_pipe[2];
	(void) lst_current;

	
	dup2(*old_pipe_in, STDIN_FILENO);
	if (*old_pipe_in != 0)
		close(*old_pipe_in);
	if (ft_lstsize(lst_current) <= 1)
		return ;
	pipe(new_pipe);
	dup2(new_pipe[1], STDOUT_FILENO);
	close(new_pipe[1]);
	*old_pipe_in = dup(new_pipe[0]);
	close(new_pipe[0]);
}


void	exec(t_list	*lst_command, char **env)
{
	t_list 	*lst_current;
	t_command	*command;
	int	old_pipe_in;
	int	save_fd[2];
	int stat_loc;
	int	pid;

	old_pipe_in = 0;
	lst_current = lst_command;
	while (lst_current != NULL)
	{
		command = lst_current->content;
		
		save_fd[0] = dup(STDIN_FILENO);
		save_fd[1] = dup(STDOUT_FILENO);
			create_pipe(&old_pipe_in, lst_current);

		pid = fork();
		if (pid == 0)
		{
			get_absolute_path(command->word);
			execve(command->word[0], command->word, env);
		}
		waitpid(pid, &stat_loc, 0);
		dup2(save_fd[0], STDIN_FILENO);
		close(save_fd[0]);
		dup2(save_fd[1], STDOUT_FILENO);
		close(save_fd[1]);
		lst_current = lst_current->next;
	}	
	lst_current = lst_command;
	if (old_pipe_in != 0)
		close(old_pipe_in);
}
