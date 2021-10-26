# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/15 10:45:54 by gasselin          #+#    #+#              #
#    Updated: 2021/10/26 14:11:18 by gasselin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCS	= srcs/main.c srcs/error.c srcs/builtins/cd.c srcs/builtins/echo.c \
			srcs/builtins/env.c srcs/builtins/exit.c srcs/builtins/export.c \
			srcs/builtins/pwd.c srcs/builtins/unset.c srcs/builtins/ft_getenv.c \
			srcs/execute/exec_utils.c srcs/parsing/dlist_utils.c \
			srcs/parsing/parse_args.c srcs/parsing/syntax_errors.c srcs/free_stuff.c

OBJS	= ${SRCS:.c=.o}

INC		= includes
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -I${INC}
RM		= rm -rf
MK		= mkdir -p
ECHO	= echo

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all :		${NAME}

${NAME} :	${OBJS}
			$(MAKE) bonus -C ./libft
			${CC} ${CFLAGS} -Llibft -lft -Llib -lreadline -lhistory -lcurses ${OBJS} -o ${NAME}
			@${ECHO} "\n\033[0;32mMinishell-1.0 Compiled!\n\033[0m"

clean :
			$(MAKE) clean -C ./libft
			${RM} ${OBJS}

fclean : clean
			$(MAKE) fclean -C ./libft
			${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re bonus