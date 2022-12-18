/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisheLLD.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:34:27 by lmery             #+#    #+#             */
/*   Updated: 2022/12/18 06:40:31 by lmery            ###   ########.fr       */
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
} bool;

enum TokenType {
  TOKEN_EOF,          // End of file
  TOKEN_WORD,         // A word
  TOKEN_REDIRECT_IN,  // < redirection
  TOKEN_REDIRECT_OUT, // > redirection
  TOKEN_PIPE,         // | symbol
  TOKEN_AND,   // & symbol
  TOKEN_QUOTE		  // " symbol
};

typedef struct s_token {
  enum TokenType type;
  char *text;
} t_token;

typedef struct s_lexer {
    int token_count;
	int	token_start;
    bool in_quote;
	bool in_word;
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

int	lexer(char *input);