# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmery <lmery@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 08:26:27 by lmery             #+#    #+#              #
#    Updated: 2023/03/12 03:09:08 by lmery            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Colors
_GREY		=	\e[30m
_RED		=	\e[31m
_GREEN		=	\e[32m
_YELLOW		=	\e[33m
_BLUE		=	\e[34m
_PURPLE		=	\e[35m
_CYAN		=	\e[36m
_W			=	\e[37m
_END		=	\e[0m
_BOLD		=	\e[1m
_HRED		=	\e[0;91m

# Colors LLD
_ORANGE		=	\e[38:5:208m
_ORANGE2	=	\e[38:5:202m
_BLUE_LLD	=	\e[38:5:25m
_GR			=	\e[38:5:29m

# Back colors
_BBLUE		=	\e[48:5:25m
_BRED		=	\e[48:5:202m
_BLKB 		=	\e[48:5:0m



#Files


#C_TEST = unit_test lexer expand

#   C_[NOM_DOSSIER] = [fichiers du dossier]

C_ROOT = main 

C_UTILS = main_utils 

C_LEXER = lexer lexer_utils lexer_tokens

C_EXPAND = expand trim custom_tokenizer merge_strings

C_HEREDOC = heredoc heredoc_utils

C_ERROR = syntaxe_error syntaxe_error_utils check_error_input free_and_exit

C_PARSER = parser parser_utils parser_utils_2

C_DEBUG = debug

C_UNIT_TEST = unit_test unit_test_parser unit_test_syntaxe_error

C_EXEC = exec  exec_utils exec_utils_2 exec_utils_3 exec_utils_4 \
builtin_utils builtin_echo builtin_cd builtin_pwd builtin_exit builtin_env \
builtin_export builtin_unset builtin_unset_utils builtin_cd_utils builtin_cd_utils_2

				
#----------------------Sources and objects-------------------

SRCS = $(addsuffix .c, $(C_ROOT) $(addprefix utils/, $(C_UTILS)) $(addprefix lexer/, $(C_LEXER)) $(addprefix expand/, $(C_EXPAND)) \
		$(addprefix error/, $(C_ERROR)) $(addprefix heredoc/, $(C_HEREDOC)) $(addprefix parser/, $(C_PARSER)) $(addprefix debug/, $(C_DEBUG)) $(addprefix exec/, $(C_EXEC)))

SRCS_TEST = $(addsuffix .c, $(addprefix unit_test/, $(C_UNIT_TEST)) $(addprefix lexer/, $(C_LEXER)) $(addprefix expand/, $(C_EXPAND)) $(addprefix error/, $(C_ERROR)) $(addprefix parser/, $(C_PARSER)) $(addprefix debug/, $(C_DEBUG)))

OBJS	=	$(SRCS:.c=.o)
OBJS_TEST = $(SRCS_TEST:.c=.o)

LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft
LIB			=	make --silent -C libft 

HEADER		=	./include/
HEADER_FILE		=	./include/minisheLLD.h
#----------------------- Constant strings --------------------

COMPILER		=	gcc

FLAGS			=	-Wall -Wextra -Werror -g3 -I $(HEADER)

INCLUDE			=	-Iinclude -Ilibft

NAME			=	minishell

#--------------------------- Messages ------------------------

READY			=	echo "$(_BLUE_LLD)$(_BOLD)\nMinishe$(_ORANGE)LLD $(_WHITE)ready !\n $(_END)"

LIBREADY		=	echo "$(_GR)$(_BOLD)Libft ready to use$(_END)\n"

LIBCOMP			=	echo "$(_GR)Compiling libft...$(_END)"

CLEANED			=	echo "$(_BBLUE)$(_BOLD)\n clean: $(_ORANGE)All objects files removed$(_END)\n"

FCLEANED		=	echo "$(_BBLUE)$(_BOLD)\n fclean: $(_ORANGE)Removed the executables and the objects files$(_END)\n"

NOBONUS			=	echo "$(_BRED)\n Bonus haven't been processed$(_END)\n"

TITLE			= 	@echo " \n *                      *                              *\n"\
					"	           *                                     *                             *\n"\
					"  * $(_ORANGE)██          ██$(_BLUE_LLD)█                  $(_W)*                                        \n"\
					"    $(_ORANGE)████    $(_W)* $(_ORANGE)████$(_BLUE_LLD)█  $(_W)*                                $(_W)*            $(_W)*                               $(_W)*\n"\
					"    $(_ORANGE)██$(_BLUE_LLD)█▀$(_ORANGE)██  ██$(_BLUE_LLD)█▀$(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█ $(_W)* $(_ORANGE)██      $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██████████$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█$(_W)*    $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██████████$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█         $(_ORANGE)██$(_BLUE_LLD)█      $(_W)*  $(_ORANGE)████████$(_BLUE_LLD)█\n"\
					"    $(_ORANGE)██$(_BLUE_LLD)█ ▀▀$(_ORANGE)██$(_BLUE_LLD)█▀▀ $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)████  $(_W)* $(_ORANGE)██$(_BLUE_LLD)█ $(_W)* $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█▀▀▀▀▀▀▀▀   $(_ORANGE)██$(_BLUE_LLD)█     $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█▀▀▀▀▀▀▀▀ $(_W)* $(_ORANGE)██$(_BLUE_LLD)█         $(_ORANGE)██$(_BLUE_LLD)█  $(_W)*      $(_ORANGE)██$(_BLUE_LLD)█▀▀▀$(_ORANGE)██$(_BLUE_LLD)█  $(_W)*\n"\
					"    $(_ORANGE)██$(_BLUE_LLD)█ $(_W)* $(_BLUE_LLD)▀▀▀   $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)█████   ██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█  $(_W)*$(_ORANGE)██$(_BLUE_LLD)█       $(_W)*   $(_ORANGE)██$(_BLUE_LLD)█     $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█ $(_W)*         $(_ORANGE)██$(_BLUE_LLD)█     $(_W)*   $(_ORANGE)██$(_BLUE_LLD)█         $(_ORANGE)██$(_BLUE_LLD)█    $(_ORANGE)██$(_BLUE_LLD)█\n"\
					" $(_W)*  $(_ORANGE)██$(_BLUE_LLD)█         $(_ORANGE)██$(_BLUE_LLD)█ $(_W)* $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█ $(_ORANGE)██  $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██████████$(_BLUE_LLD)█   $(_ORANGE)██████████$(_BLUE_LLD)█ $(_W)* $(_ORANGE)████████$(_BLUE_LLD)█     $(_ORANGE)██$(_BLUE_LLD)█  $(_W)*      $(_ORANGE)██$(_BLUE_LLD)█         $(_ORANGE)██$(_BLUE_LLD)█ $(_W)*  $(_ORANGE)██$(_BLUE_LLD)█\n"\
					"    $(_ORANGE)██$(_BLUE_LLD)█       $(_W)* $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█  $(_ORANGE)█████$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█   $(_BLUE_LLD)▀▀▀▀▀▀▀▀$(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█▀▀▀▀▀$(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█▀▀▀▀▀▀     $(_ORANGE)██$(_BLUE_LLD)█         $(_ORANGE)██$(_BLUE_LLD)█         $(_ORANGE)██$(_BLUE_LLD)█    $(_ORANGE)██$(_BLUE_LLD)█\n"\
					"    $(_ORANGE)██$(_BLUE_LLD)█         $(_ORANGE)██$(_BLUE_LLD)█  $(_W)*$(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)████$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█    $(_W)*      $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█  $(_W)*  $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█           $(_ORANGE)██$(_BLUE_LLD)█       $(_W)* $(_ORANGE)██$(_BLUE_LLD)█         $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█▀\n"\
					"    $(_ORANGE)██$(_BLUE_LLD)█         $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█     $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██████████$(_BLUE_LLD)█   $(_ORANGE)██$(_BLUE_LLD)█     $(_ORANGE)██$(_BLUE_LLD)█   $(_ORANGE)██████████$(_BLUE_LLD)█   $(_ORANGE)████████$(_BLUE_LLD)█   $(_ORANGE)████████$(_BLUE_LLD)█   $(_ORANGE)████████$(_BLUE_LLD)█\n"\
					"    $(_BLUE_LLD)▀▀▀ $(_W)*       $(_BLUE_LLD)▀▀▀   ▀▀▀   ▀▀▀ $(_W)*   $(_BLUE_LLD)▀▀▀   ▀▀▀ $(_W)* $(_BLUE_LLD)▀▀▀▀▀▀▀▀▀▀▀   ▀▀▀     ▀▀▀   ▀▀▀▀▀▀▀▀▀▀▀$(_W)*  $(_BLUE_LLD)▀▀▀▀▀▀▀▀▀   ▀▀▀▀▀▀▀▀▀   ▀▀▀▀▀▀▀▀▀  $(_W)*\n"\
					"   $(_W)*                                     $(_W)*                          *                                               $(_W)*                                     \n"\
					"                              $(_W)*                                                            $(_W)*                $(_W)*\n"\
					"                 *                                                           *                      *\n                                            *\n"\
					" 				         $(_PURPLE)~ Made with talent by gle-mini & lmery ~\n"


#----------------------------- Rules -------------------------

all: $(NAME) 

bonus: 
	@$(NOBONUS)

$(NAME): $(OBJS) $(HEADER_FILE)
	@$(LIBCOMP)
	@$(LIB) 
	@$(LIBREADY)
		$(COMPILER) $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline	
	@$(TITLE)
	@$(READY)


test: $(OBJS_TEST)
	@$(LIBCOMP)
	@$(LIB) 
	@$(LIBREADY)
		$(COMPILER) $(FLAGS)  $(OBJS_TEST) -o test $(LIBFT) -lreadline
clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS_TEST)
	@make fclean -C libft
	@$(CLEANED)

fclean: 
	rm -rf $(OBJS)
	rm -rf $(OBJS_TEST)
	rm -rf $(NAME)
	rm -rf test
	@make fclean -C libft
	@$(FCLEANED)

.c.o:
	$(COMPILER) $(FLAGS) $(INCLUDE) -c $< -o ${<:.c=.o}

re: fclean all

.PHONY: all clean fclean re libft
