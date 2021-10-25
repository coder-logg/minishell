NAME	=	minishell

PARSER	=	$(addprefix parser/, parser.c string.c read_env.c)
BUILTIN	=	$(addprefix builtins_and_cmd/, env.c pwd.c run_cmd.c distribution.c cd.c \
			command.c pipe.c echo.c export.c exit.c)

SRCS	=	${PARSER} ${BUILTIN} main.c\
			util/errors.c util/utils.c util/strarr_utils.c

OBJS		=	$(SRCS:.c=.o)
FLAGS		=	-Wall -Wextra -Werror
LIBFTMAKE 	=	$(MAKE) -C libft/

%.o: %.c
	cd $(@D) && $(CC) $(FLAGS) -c $(<F)

all: libft/libft.a $(NAME)

libft/libft.a:
	@$(LIBFTMAKE)

$(NAME): $(OBJS)
	$(CC) -o $@ $(OBJS) libft/libft.a -lreadline

clean:
	rm -f  $(OBJS)
	$(LIBFTMAKE) clean

fclean:
	rm -f $(NAME) $(OBJS)
	$(LIBFTMAKE) fclean

re: fclean all

.PHONY:	all clean fclean re libft/libft.a