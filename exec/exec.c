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


void execute_command_with_redirection(char **command, char **redirection, char **env) {
	int stat_loc;
    int child_pid = fork();
	get_absolute_path(command);
	/*
	if (child_pid == 0)
	{
		execve(command[0], command, env);
		
		exit(0);
	}
	waitpid(child_pid, &stat_loc, 0);
	*/
	//printf("%d", child_pid);

    if (child_pid == 0) {
		printf("in child\n");
        // Child process
        int redirect_index = 0;
        while (redirection[redirect_index] != NULL) {
			printf("test\n");
            if (redirection[redirect_index][0] == '<') {
				printf("test1\n");
                // Standard input redirection
                int input_fd = open(redirection[redirect_index + 1], O_RDONLY);
                if (input_fd == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                if (dup2(input_fd, STDIN_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                if (close(input_fd) == -1) {
                    perror("close");
                    exit(EXIT_FAILURE);
                }
                redirect_index += 2;
            } else if (redirection[redirect_index][0] == '>') {
				printf("test2\n");
                // Standard output redirection
                int output_fd = open(redirection[redirect_index + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (output_fd == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                if (dup2(output_fd, STDOUT_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                if (close(output_fd) == -1) {
                    perror("close");
                    exit(EXIT_FAILURE);
                }
                redirect_index += 2;
            } else {
				printf("test3\n");
				// Invalid redirection
				fprintf(stderr, "Error: Invalid redirection operator '%s'\n", redirection[redirect_index]);
				exit(EXIT_FAILURE);
			}
			printf("end redirection\n");
		}
		printf("execve\n");
		execve(command[0], command, env);
	}
	waitpid(child_pid, &stat_loc, 0);
}

