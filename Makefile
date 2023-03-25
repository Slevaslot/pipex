
PROG	= pipex


SRCS 	= pipex.c pipex_utils.c ft_split.c ft_substr.c check_cmd.c
OBJS 	= ${SRCS:.c=.o}
#MAIN	= pipex.c

#SRCS_B	= srcs/pipex_bonus.c srcs/utils.c srcs/utils_bonus.c
#OBJS_B	= ${SRCS_B:.c=.o}
#MAIN_B	= pipex_bonus.c



CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -g3

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: 		${PROG}

${PROG}:	${OBJS}

					@$(CC) ${OBJS} -o ${PROG}
					@echo "Pipex Compiled!\n"


bonus:		${PROG_B}

${PROG_B}:	${OBJS_B}

					@echo "\Pipex Bonus Compiled! \n"

clean:

					@rm -f ${OBJS} ${OBJS_B}

fclean: 	clean
					@rm -f $(NAME)
					@rm -f ${PROG}
					@echo "\nDelete ALL!\n"

re:			fclean all

re_bonus:	fclean bonus

.PHONY: all clean fclean re
