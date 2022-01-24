# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malouvar <malouvar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 12:25:55 by malouvar          #+#    #+#              #
#    Updated: 2022/01/24 16:52:47 by malouvar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	srcs/main.c \
		srcs/utils.c

SRCSBONUS = srcs_bonus/main_bonus.c \
			srcs_bonus/utils_bonus.c \
			srcs_bonus/utils_2_bonus.c

OBJS = ${SRCS:.c=.o}

OBJSBONUS = ${SRCSBONUS:.c=.o}

NAME = pipex

BONUS = pipex_bonus

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

bonus: $(OBJSBONUS)
	@${MAKE} -C libft
	@echo "pipex bonus: libft compiled."
	@${CC} -g ${FLAGS} -o ${BONUS} ${OBJSBONUS} -Llibft -lft
	@echo "pipex bonus: compiled."


clean:
			@${MAKE} -C libft clean
			@${RM} ${OBJS} ${OBJSBONUS}
			@echo "pipex : \".o\" files were erased"

fclean:		clean
			@${MAKE} -C libft fclean
			@${RM} ${NAME} ${BONUS}
			@echo "pipex : \".o\" and executables were erased"

re: fclean all

.PHONY:		all clean fclean re
