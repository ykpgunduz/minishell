CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = parser.c lexer.c lexer_utils.c quote.c quote_utils.c special.c expander.c expander_utils.c parser_utils.c parser_redirect.c
OBJS = $(SRCS:.c=.o)
LIB = parser.a

all: $(LIB)

$(LIB): $(OBJS)
	ar rcs $(LIB) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIB)

re: fclean all

.PHONY: all clean fclean re
