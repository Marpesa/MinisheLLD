# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmery <lmery@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 08:26:27 by lmery             #+#    #+#              #
#    Updated: 2022/12/17 23:36:16 by lmery            ###   ########.fr        #
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

# Back colors
_BBLUE		=	\e[48:5:25m



#Files

SRCS_DIR		= ./

FILES = main.c \


				
#----------------------Sources and objects-------------------

SRCS = $(addprefix $(SRCS_DIR), $(FILES))

OBJS	=	$(SRCS:.c=.o)

LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft


LIB			=	make -C libft


#----------------------- Constant strings --------------------

COMPILER		=	cc

FLAGS			=	-Wall -Wextra -Werror

INCLUDE			=	-I include

NAME			=	minishell

#--------------------------- Messages ------------------------

READY	=	echo "$(_BLUE_LLD)$(_BOLD)\nMinishe$(_ORANGE)LLD $(_WHITE)ready !\n $(_END)"

CLEANED			=	echo "$(_BBLUE)$(_BOLD)$(_ORANGE)\nclean: All objects files removed$(_END)\n"

FCLEANED		=	echo "$(_BBLUE)$(_BOLD)$(_ORANGE)\nfclean: Removed the executables and the objects files\n$(_END)"

NOBONUS			=	echo "$(GREY)\n Bonus haven't been processed\n$(_END)"

#----------------------------- Rules -------------------------

all: $(NAME)

bonus: $(NOBONUS)

$(NAME): $(OBJS) 
	@$(LIB)
		$(COMPILER) $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline
	@$(READY)

clean:
	rm -rf $(OBJS)
	@make fclean -C libft
	@$(CLEANED)

fclean: clean
	rm -rf $(NAME)
	@make fclean -C libft
	@$(FCLEANED)

.c.o:
	${COMPILER} ${FLAGS} $(INCLUDE) -I minisheLLD.h -c $< -o ${<:.c=.o}

re: fclean all

.PHONY: all clean fclean re libft
