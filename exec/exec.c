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

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(exit_failure);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", "-l", NULL);
    } 
    return 0;
}


void execute_command_with_redirection(char **command, char **redirection, char **env) {
	int	fd[2];	
	int stat_loc;
    int redirect_index;
    int child_pid;
	
	get_absolute_path(command);
	if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    child_pid = fork();
    if (child_pid == 0) {
        // Child process
        redirect_index = 0;
		
		close(fd[0]);
        while (redirection != NULL && redirection[redirect_index] != NULL) {
            if (ft_strncmp(redirection[redirect_index], "<", 1) == 0) {
                // Standard input redirection
                fd[1] = open(redirection[redirect_index + 1], O_RDONLY);
                if (fd[1] == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                if (dup2(fd[1], STDIN_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                if (close(fd[1]) == -1) {
                    perror("close");
                    exit(EXIT_FAILURE);
                }
                redirect_index += 2;
            } else if (ft_strncmp(redirection[redirect_index], ">", 1) == 0) {
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
            }
			/*
			else if (ft_strncmp(redirection[redirect_index], ">>", 3)) {
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
            } 
			*/
			else {
				// Invalid redirection
				fprintf(stderr, "Error: Invalid redirection operator '%s'\n", redirection[redirect_index]);
				exit(EXIT_FAILURE);
			}
		}
		execve(command[0], command, env);
	}
	waitpid(child_pid, &stat_loc, 0);
}


void	exec()
{
	fd[2];
    pid_t pid;
    int i;

	i = 0;
    while (i < command_count - 1)
	{
        if (pipe(fd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Child process
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);

            char *args[] = { command[i], NULL };
            execve(command[i], args, NULL);
        } else {
            // Parent process
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
        }
		i++;
    }

    // Execute the last command
    char *args[] = { command[i], NULL };
    execve(command[i], args, NULL);

    return 0;
}


