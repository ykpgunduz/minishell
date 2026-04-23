NAME    = builtin.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
INCLUDES = -I../includes -I../libft

SRCS    = the.c echo.c pwd_env.c cd.c export.c export2.c unset.c exit.c
OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re