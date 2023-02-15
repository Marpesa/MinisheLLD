/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisheLLD.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:34:27 by lmery             #+#    #+#             */
/*   Updated: 2023/02/12 16:15:46 by gle-mini         ###   ########.fr       */
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


/*----------------- Colors LLD ---------------- */
#define _ORANGE		"\e[38:5:208m"
#define _ORANGE2	"\e[38:5:202m"
#define _BLUE_LLD	"\e[38:5:25m"
#define _WHITE		"\e[37m"
#define _END		"\e[0m"
#define _BOLD		"\e[1m"


/*---------------- Main fonctions -----------------*/

void ignore_signal_for_shell();


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
void			exit_error(char *msg);
void			free_and_exit(t_list *lst_token, t_list *lst_command, char **linebuffer);
void			free_all(t_list **lst_token, t_list **lst_command, char **linebuffer);

/*-------------------- Parser ---------------------*/ 

typedef struct s_command {
	char	**word;
	char	**redir;
	pid_t	pid;
} t_command;
	
int		parser(t_list *lst_token, t_list **lst_command);
void	lst_print_command(t_list *cmd);


// Test
void	print_command(t_command *command);
void	print_lst_command_test(t_list *lst_command);
char	**create_map(int size, ...);
t_list	*create_lst_command_test(int size, ...);
void	print_lst_command_test(t_list *lst_command);
t_bool	lst_command_compare(t_list *lst_command1, t_list *lst_command2);
void	test_syntaxe_error(char **env);

/*------------------Debug------------------------*/
void	print_map(char **map);
void	print_lst_command(t_list *lst_command);
void	print_lst_token(t_list *head);

/*------------------Exec-------------------------*/
void	exec(t_list *lst_command, char **env);

#endif
