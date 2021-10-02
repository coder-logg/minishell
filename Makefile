NAME	=	minishell
PARSER	=	$(addprefix parser/, parser.c)
SRCS	=	${PARSER} main.c
OBJS =		$(SRCS:.c=.o)
FLAGS	=	-Wall -Wextra -Werror
LIBFTMAKE =	$(MAKE) -C libft/

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