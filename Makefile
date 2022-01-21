# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malouvar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 12:25:55 by malouvar          #+#    #+#              #
#    Updated: 2022/01/21 16:58:00 by malouvar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	srcs/main.c \
		srcs/utils.c

OBJS = ${SRCS:.c=.o}

NAME = pipex

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	@${MAKE} -C libft
	@echo "pipex : libft compiled."
	@${CC} -g ${FLAGS} -o ${NAME} ${OBJS} -Llibft -lft
	@echo "pipex : compiled."

clean:
			@${MAKE} -C libft clean
			@${RM} ${OBJS}
			@echo "pipex : \".o\" files were erased"

fclean:		clean
			@${MAKE} -C libft fclean
			@${RM} ${NAME}
			@echo "pipex : \".o\" and executables were erased"

re: fclean all

.PHONY:		all clean fclean re
