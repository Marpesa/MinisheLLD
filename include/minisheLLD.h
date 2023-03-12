/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisheLLD.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:34:27 by lmery             #+#    #+#             */
/*   Updated: 2023/03/12 03:25:16 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELLD_H
# define MINISHELLD_H

/*----------------- Libraries ---------------- */

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

/*----------------- Global ---------------- */

extern int	g_status;

/*----------------- Structures ---------------- */

typedef enum s_bool
{
	false,
	true
}	t_bool;

typedef struct s_quotes {
	t_bool	in_s;
	t_bool	in_d;
	t_bool	s_in_d;
}	t_quotes;

typedef enum e_token_type {
	TOKEN_LIM,
	TOKEN_WORD,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_IGNORE,
	TOKEN_HEREDOC,
	TOKEN_REDIRECT_APPEND
}	t_token_type;

typedef struct s_token {
	t_token_type	type;
	char			*text;
}	t_token;

typedef struct s_lexer {
	t_token	*token;
	int		token_count;
	int		token_start;
	t_bool	in_word;
	int		i;
	t_list	*lst_token;
}	t_lexer;

typedef struct s_exec {
	t_list	*lst_token;
	t_list	*lst_command;
	char	**bufferline;
	char	**env;
}	t_exec;

typedef struct s_input {
	char 	*linebuffer;
	t_list	*lst_command;
	t_list	*lst_token;
}	t_input;

/*----------------- Colors LLD ---------------- */

# define _ORANGE		"\e[38:5:208m"
# define _ORANGE2	"\e[38:5:202m"
# define _BLUE_LLD	"\e[38:5:25m"
# define _WHITE		"\e[37m"
# define _END		"\e[0m"
# define _BOLD		"\e[1m"
# define HEREDOC_FILE	"/tmp/.miniheLLD_heredoc"

/*---------------- Main fonctions -----------------*/

void			ft_new_line(int signum, siginfo_t *info, void *context);
void			ignore_signal_for_shell(void);
char			*gstat_in_env(char *env);
void			ignore_sigint(void);
char			*rl_gets(void);
char			*gstat_in_env(char *env);

/*--------------------- Lexer ---------------------*/

int				lexer(char *input, t_list **lst_token);
char			**ft_get_env(char **env);

char			*ft_get_token_type(enum e_token_type type);
void			lexer_data_init(t_lexer *data);
int				lst_add_token(t_list **lst_token, void *content);
int				is_special(char c);
int				ft_word_in_quote(char *input, int i, int len, char quote);

int				token_word(char *input, int *i, t_lexer *data);
int				super_token(char *input, int *i, t_lexer *data);

/*-------------------- Expand ---------------------*/

int				ft_expand(t_list *lst_token, char **env);
char			*var_find(char *start, char *end, char **env, t_bool s_in_d);
int				is_special(char c);
void			trim(char **str);
int				custom_tokenizer(char *str, char **start, char **end, \
				t_quotes *quotes);
char			*m_s(char *str1, char *str2);
int				loop_expand(char *start, char *end, char **new_str, char **env);

/*-------------------- Heredoc --------------------*/

void			heredoc(t_list *lst_token, char **secret_env);
t_bool			is_heredoc(t_list *lst_token);
int				create_temporary_file(void);
void			sigint_handler(int signum);
void			set_heredoc_signal(void);

/*-------------------- Error ----------------------*/

int				syntaxe_error(t_list *lst_token);
int				closed_quotes(char *input, int *i);
t_token_type	return_token_type(t_list *lst_token);
char			*return_token_text(t_list *lst_token);
t_bool			start_or_finish_pipe(t_list *lst_token);
int				check_error_input(char *input);
void			free_and_exit(t_list *lst_token, t_list *lst_command, \
				char **linebuffer, char **env);
void			free_all(t_list **lst_token, t_list **lst_command, \
				char **linebuffer);
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
}	t_command;

int				parser(t_list *lst_token, t_list **lst_command);
void			lst_print_command(t_list *cmd);
void			free_map(char **map);
int				lst_add_command(t_list **lst_command, t_command *command);
int				add_str_to_map(char *str, char **map, char ***map_result);

void			init_cmd(t_command	**command, t_list **lst_cmd, \
				t_token **token_prev);
int				first_command(t_command **command, t_list **lst_command);
t_bool			is_add_token(t_token *token);
t_bool			is_add_prev_token(t_token *token);

/*---------------------- Test --------------------- */

void			print_command(t_command *command, int fd);
void			print_lst_command_test(t_list *lst_command);
char			**create_map(int size, ...);
t_list			*create_lst_command_test(int size, ...);
void			print_lst_command_test(t_list *lst_command);
t_bool			lst_command_compare(t_list *lst_command1, t_list *lst_command2);
void			test_syntaxe_error(char **env);

/*----------------------Debug------------------------*/

void			print_map(char **map, int fd);
void			print_lst_command(t_list *lst_command, int fd);
void			print_lst_token(t_list *head);

/*----------------------Exec-------------------------*/

int				exec(t_list *lst_command, char ***env, int tmp);

void			cat_to_bin(char *bin, char *path_split, char *cmd);
int				get_valid_bin(char *path, char **cmd, char **bin_result);
int				dup_path(char ***env, char **path, int *error_status);
void			free_path_and_cmd(char *path, char *bin, char **cmd);
int				free_path_and_return_error(char *bin, char *path, \
				int *error_status);

void			redir_in(t_command *command, char **redirection, int *i);
void			redir_out(t_command *command, char **redirection, int *i);
void			redir_append_out(t_command *command, \
				char **redirection, int *i);
void			redir_heredoc(t_command *command, int *i);
void			redirection(t_command *command);

void			close_open_fd(t_command *command);
void			close_fd_and_free(t_command *command, char ***env, \
				t_list *lst_command_head);
int				execute_command(t_command *command, char ***env, \
				t_list *lst_command_head);
void			redir_child_pipe(t_command *command, int *prevpipe, \
				int *pipefd);
int				ft_pipe(t_command *command, char ***env, int *prevpipe, \
				t_list *lst_command_head);

int				execute_child_last(t_command *command, int prevpipe, \
				char ***env, t_list *lst_command_head);
int				ft_last(t_command *command, char ***env, int prevpipe, \
				t_list *lst_command_head);
int				get_command_path(t_command *command, int *error_status, \
				char **env);
int				check_valid_path(t_command *command, int error_status, \
				int prevpipe);

/*------------------Builtin-------------------------*/

t_bool			is_builtin(char **cmd);
int				builtin_outpipe(t_command *command, char ***env, \
				t_list *lst_command);
int				execute_builtin(char **cmd, char ***env, int fd, \
				t_list *lst_command);
int				builtin_echo(char **command, int fd, char ***env, \
				t_list *lst_command);
char			*get_env(char *var, char ***envp);
int				is_cd(char **cmd);
int				builtin_cd(char **cmd);
char			*ft_strldup_secure(char *dst, const char *src, size_t dstsize);
int				print_error_path(char **cmd, int path);
int				double_point(char **str, char **str2, int *path);
char			*ft_root_one(char *back);
void			builtin_pwd(char **cmd, char ***env, t_list *lst_command, \
				int fd_out);
int				is_pwd(char **cmd);
int				is_exit(char **cmd);
void			builtin_exit(char ***env, t_list *lst_command, char **cmd);
int				builtin_env(char **cmd, int fd, char ***env, \
				t_list *lst_command);
int				is_export(char **cmd);
int				is_export(char **cmd);
int				builtin_export(char **cmd, char ***env);
char			*until_equal(char *cmd);
int				index_in_env(char *cmd, char **env);
int				is_unset(char **cmd);
int				builtin_unset(char **cmd, char ***env);
int				is_in_env(char *cmd, char **env);
int				ft_is_there(char *str, char **cmd, int index);
int				check_occur(char **cmd, char **str_env, int *occur);
int				equal_sign(char *str, char *env);

int				allready_in_env(char ***cmd, char ***env, int *j, int i);
int				end_export(char ***new_env, char ***str_env, char ***env, \
				char *cmd);

#endif
