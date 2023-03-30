
PROG	= pipex


SRCS 	= pipex.c pipex_utils.c ft_split.c ft_substr.c check_cmd.c
OBJS 	= ${SRCS:.c=.o}
#MAIN	= pipex.c

SRCS_B	=	pipex_bonus/pipex_bonus.c \
		pipex_bonus/pipex_utils_bonus.c \
		pipex_bonus/here_doc.c \
		pipex_bonus/get_next_line/get_next_line.c \
		pipex_bonus/get_next_line/get_next_line_utils.c \

LIBS = pipex_bonus/libft/libft.a
OBJS_B	= ${SRCS_B:.c=.o}
PROG_B = pipex_bonuss

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -g3

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

all: 		${PROG}

${PROG}:	${OBJS}

					@gcc $(CFLAGS) ${OBJS} -o ${PROG}
					@echo "Pipex Compiled!\n"

bonus:		${PROG_B}

${PROG_B}:	${OBJS_B}
					@gcc $(CFLAGS) ${OBJS_B} ${LIBS}
					@make -C pipex_bonus/libft/
					@echo "pipex_bonus Compiled!\n"

clean:

					@rm -f ${OBJS} ${OBJS_B}

fclean: 	clean
					@rm -f $(NAME)
					@rm -f ${PROG}
					@rm -f ${PROG_B}
					@echo "\nDelete ALL!\n"

re:			fclean all

re_bonus:	fclean bonus

.PHONY: all clean fclean re bonus
