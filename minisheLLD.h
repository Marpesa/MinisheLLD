/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisheLLD.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:34:27 by lmery             #+#    #+#             */
/*   Updated: 2022/12/21 01:17:54 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <pwd.h>
#include <sys/types.h>
#include <fcntl.h>


typedef enum {
	false,
	true
} t_bool;

enum e_token_type {
  TOKEN_EOF,          // End of file
  TOKEN_WORD,         // A word
  TOKEN_REDIRECT_IN,  // < redirection
  TOKEN_REDIRECT_OUT, // > redirection
  TOKEN_PIPE,         // | symbol
  TOKEN_AND,		      //  & symbol
  TOKEN_QUOTE,	      // " symbol
  TOKEN_IGNORE,       // Every special char to ingore (; \)
  TOKEN_ENV           // $
};

typedef struct s_token {
  enum e_token_type type;
  char *text;
} t_token;

typedef struct s_lexer {
	t_token *token;
    int token_count;
	int	token_start;
    t_bool in_quote;
	t_bool in_word;
	int i;
	t_list *lst_token;
} t_lexer;


// Colors LLD
#define _ORANGE		"\e[38:5:208m"
#define _ORANGE2	"\e[38:5:202m"
#define _BLUE_LLD	"\e[38:5:25m"
#define _WHITE		"\e[37m"
#define _END		"\e[0m"
#define _BOLD		"\e[1m"

t_list	*lexer(char *input);
char  **ft_get_env(char **env);
void	lst_print_token(t_list *head);
void  ft_expand(t_list *lst_token, char **env);
int		is_special(char c);
