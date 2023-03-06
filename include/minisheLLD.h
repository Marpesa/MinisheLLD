/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisheLLD.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:34:27 by lmery             #+#    #+#             */
/*   Updated: 2023/03/05 21:11:02 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELLD_H
# define MINISHELLD_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <errno.h>
# include <signal.h>
# include <stdarg.h>
# include <string.h>
# include <sys/wait.h>
# include <pwd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <limits.h>

extern int	g_status;

typedef enum s_bool
{
	false,
	true
} t_bool;

typedef enum e_token_type {
	TOKEN_LIM,				// heredoc limitor 
	TOKEN_WORD,				// A word
	TOKEN_REDIRECT_IN,		// < redirection
	TOKEN_REDIRECT_OUT,		// > redirection
	TOKEN_PIPE,				// | symbol
	TOKEN_AND,				//  & symbol
	TOKEN_IGNORE,			// Every special char to ignore (; \)
	TOKEN_HEREDOC,			// <<
	TOKEN_REDIRECT_APPEND	// >>
} t_token_type;

typedef struct s_token {
	t_token_type type;
	char *text;
} t_token;

typedef struct s_lexer {
	t_token *token;
	int token_count;
	int	token_start;
	t_bool in_word;
	int i;
	t_list *lst_token;
} t_lexer;

typedef struct s_exec {
	t_list *lst_token;
	t_list *lst_command;
	char 	**bufferline;
	char	**env;
} t_exec;


/*----------------- Colors LLD ---------------- */
#define _ORANGE		"\e[38:5:208m"
#define _ORANGE2	"\e[38:5:202m"
#define _BLUE_LLD	"\e[38:5:25m"
#define _WHITE		"\e[37m"
#define _END		"\e[0m"
#define _BOLD		"\e[1m"
# define HEREDOC_FILE	"/tmp/.miniheLLD_heredoc"


/*---------------- Main fonctions -----------------*/

void	ft_new_line();
void 	ignore_signal_for_shell();
char	*gstat_in_env();
void	ignore_sigint();

/*--------------------- Lexer ---------------------*/ 

int		lexer(char *input, t_list **lst_token);
char 	**ft_get_env(char **env);

char	*ft_get_token_type(enum e_token_type type);
void	lexer_data_init(t_lexer *data);
int		lst_add_token(t_list **lst_token, void *content);
int		is_special(char c);

/*-------------------- Expand ---------------------*/ 

int	ft_expand(t_list *lst_token, char **env);
int		is_special(char c);
void	trim(char **str);
int		custom_tokenizer(char *str, char **start, char **end, t_bool *in_d_quote);
char 	*merge_strings(char *str1, char *str2);

/*-------------------- Heredoc --------------------*/

void	heredoc(t_list *lst_token);

/*-------------------- Error ----------------------*/

int				syntaxe_error(t_list *lst_token);
t_token_type	return_token_type(t_list *lst_token);
char			*return_token_text(t_list *lst_token);
t_bool			start_or_finish_pipe(t_list *lst_token);
int				check_error_input(char *input);
void			free_and_exit(t_list *lst_token, t_list *lst_command, char **linebuffer, char **env);
void			free_all(t_list **lst_token, t_list **lst_command, char **linebuffer);
void			ft_free_map(char **map);
void			del_command(void *content);
void			del_token(void *content);
int				ft_print_error(char *msg, char *data, char *end);



/*-------------------- Parser ---------------------*/ 

typedef struct s_command {
	int		fd_in;
	int		fd_out;
	char	**word;
	char	**redir;
} t_command;
	
int		parser(t_list *lst_token, t_list **lst_command);
void	lst_print_command(t_list *cmd);
void	free_map(char **map);


// Test
void	print_command(t_command *command, int fd);
void	print_lst_command_test(t_list *lst_command);
char	**create_map(int size, ...);
t_list	*create_lst_command_test(int size, ...);
void	print_lst_command_test(t_list *lst_command);
t_bool	lst_command_compare(t_list *lst_command1, t_list *lst_command2);
void	test_syntaxe_error(char **env);

/*------------------Debug------------------------*/
void	print_map(char **map, int fd);
void	print_lst_command(t_list *lst_command, int fd);
void	print_lst_token(t_list *head);

/*------------------Exec-------------------------*/
int		exec(t_list *lst_command, char ***env);
int		is_g_stat(char *cmd);
void	get_g_status(void);

/*------------------Builtin-------------------------*/
t_bool	is_builtin(char *value);
int		builtin_outpipe(t_command *command, char ***env, t_list *lst_command);
void	execute_builtin(char **cmd, char ***env, int fd, t_list *lst_command);
int		builtin_echo(char **command, int fd, char ***env, t_list *lst_command);
char	*get_env(char *var, char ***envp);
int		is_cd(char **cmd);
int		builtin_cd(char **cmd);
char	*ft_strldup_secure(char *dst, const char *src, size_t dstsize);
void	double_point(char **str, char **str2, int *path);
char	*ft_root_one(char *back);
void	builtin_pwd(char **cmd, char ***env, t_list *lst_command);
int		is_pwd(char **cmd);
int		is_exit(char **cmd);
void	builtin_exit(char ***env, t_list *lst_command, char **cmd);
int		builtin_env(char **cmd, int fd, char ***env, t_list *lst_command);
int		is_export(char **cmd);
void	builtin_export(char **cmd, char ***env);
char	*until_equal(char *cmd);
int		index_in_env(char *cmd, char **env);
int		is_unset(char **cmd);
void	builtin_unset(char **cmd, char ***env);
int		is_in_env(char *cmd, char **env);
int		ft_is_there(char *str, char **cmd, int index);
int		check_occur(char **cmd, char **str_env, int *occur);
int		until_equal_sign(char *str, char *env);

int		allready_in_env(char ***cmd, char ***env, int *j, int i);
int		end_export(char ***new_env, char ***str_env, char ***env, char *cmd);





#endif
