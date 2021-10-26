# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/10 09:29:07 by gasselin          #+#    #+#              #
#    Updated: 2021/10/22 12:06:03 by gasselin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

SRCS	= ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_iswhitespace.c \
		ft_strchr.c \
		ft_strchr_rev.c \
		ft_strrchr.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_count_char.c \
		ft_abs.c \
		ft_strarr_dup.c \
		ft_strarr_free.c \
		ft_strarr_size.c \
		ft_strarr_sort.c \
		ft_strarr_index.c \
		ft_strarr_addback.c \
		ft_strjoin_triple.c

BONUS	= ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

HEADER	= .

OBJS	= ${SRCS:.c=.o}

OBJSBONUS = ${BONUS:.c=.o}

.c.o:
		${CC} ${CFLAGS} -I${HEADER} -c $< -o $@

${NAME}: ${OBJS}
		ar rcs ${NAME} ${OBJS}

all:	${NAME}

bonus:	${OBJS} ${OBJSBONUS}
		ar rcs ${NAME} ${OBJS} ${OBJSBONUS}

clean:
		${RM} ${OBJS} ${OBJSBONUS}

fclean: clean
		${RM} ${NAME}

re:		fclean bonus

.PHONY: all bonus clean fclean re
