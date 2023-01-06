# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmery <lmery@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 08:26:27 by lmery             #+#    #+#              #
#    Updated: 2023/01/04 19:45:01 by gle-mini         ###   ########.fr        #
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
_WHITE		=	\e[37m
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

C_ROOT = main lexer expand syntaxe_error

C_TEST = lexer_test lexer

#   C_[NOM_DOSSIER] = [fichiers du dossier]


				
#----------------------Sources and objects-------------------

SRCS = $(addsuffix .c, $(C_ROOT) $(addprefix [nom_dossier]/, $(C_[NOM_DOSSIER])) )

SRCS_TEST = $(addsuffix .c, $(C_TEST) $(addprefix [nom_dossier]/, $(C_[NOM_DOSSIER])) )

OBJS	=	$(SRCS:.c=.o)
OBJS_TEST = $(SRCS_TEST:.c=.o)

LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft
LIB			=	make --silent -C libft 

#----------------------- Constant strings --------------------

COMPILER		=	cc

FLAGS			=	-Wall -Wextra -Werror -g3

INCLUDE			=	-Iinclude -Ilibft

NAME			=	minishell

#--------------------------- Messages ------------------------

READY			=	echo "$(_BLUE_LLD)$(_BOLD)\nMinishe$(_ORANGE)LLD $(_WHITE)ready !\n $(_END)"

LIBREADY		=	echo "$(_GR)$(_BOLD)Libft ready to use$(_END)\n"

LIBCOMP			=	echo "$(_GR)Compiling libft...$(_END)"

CLEANED			=	echo "$(_BBLUE)$(_BOLD)\n clean: $(_ORANGE)All objects files removed$(_END)\n"

FCLEANED		=	echo "$(_BBLUE)$(_BOLD)\n fclean: $(_ORANGE)Removed the executables and the objects files$(_END)\n"

NOBONUS			=	echo "$(_BRED)\n Bonus haven't been processed$(_END)\n"

#----------------------------- Rules -------------------------

all: $(NAME)

bonus: 
	@$(NOBONUS)

$(NAME): $(OBJS) 
	@$(LIBCOMP)
	@$(LIB) 
	@$(LIBREADY)
		$(COMPILER) $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline
	@$(READY)

test: $(OBJS_TEST)
	@$(LIBCOMP)
	@$(LIB) 
	@$(LIBREADY)
		$(COMPILER) $(FLAGS) $(OBJS_TEST) -o test $(LIBFT)

clean:
	rm -rf $(OBJS)
	@make fclean -C libft
	@$(CLEANED)

fclean: 
	rm -rf $(OBJS)
	rm -rf $(NAME)
	@make fclean -C libft
	@$(FCLEANED)

.c.o:
	$(COMPILER) $(FLAGS) $(INCLUDE) -c $< -o ${<:.c=.o}

re: fclean all

.PHONY: all clean fclean re libft
