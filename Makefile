NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

READLINE_DIR = $(shell brew --prefix readline)
READLINE_INC = -I$(READLINE_DIR)/include
LDFLAGS      = -L$(READLINE_DIR)/lib -lreadline

LIBFT_SRCS   = execute/libft/ft_atoi.c \
               execute/libft/ft_bzero.c \
               execute/libft/ft_calloc.c \
               execute/libft/ft_isalnum.c \
               execute/libft/ft_isalpha.c \
               execute/libft/ft_isascii.c \
               execute/libft/ft_isdigit.c \
               execute/libft/ft_isprint.c \
               execute/libft/ft_itoa.c \
               execute/libft/ft_lstadd_back.c \
               execute/libft/ft_lstadd_front.c \
               execute/libft/ft_lstclear.c \
               execute/libft/ft_lstdelone.c \
               execute/libft/ft_lstiter.c \
               execute/libft/ft_lstlast.c \
               execute/libft/ft_lstmap.c \
               execute/libft/ft_lstnew.c \
               execute/libft/ft_lstsize.c \
               execute/libft/ft_memchr.c \
               execute/libft/ft_memcmp.c \
               execute/libft/ft_memcpy.c \
               execute/libft/ft_memmove.c \
               execute/libft/ft_memset.c \
               execute/libft/ft_putchar_fd.c \
               execute/libft/ft_putendl_fd.c \
               execute/libft/ft_putnbr_fd.c \
               execute/libft/ft_putstr_fd.c \
               execute/libft/ft_split.c \
               execute/libft/ft_strchr.c \
               execute/libft/ft_strdup.c \
               execute/libft/ft_striteri.c \
               execute/libft/ft_strjoin.c \
               execute/libft/ft_strlcat.c \
               execute/libft/ft_strlcpy.c \
               execute/libft/ft_strlen.c \
               execute/libft/ft_strmapi.c \
               execute/libft/ft_strncmp.c \
               execute/libft/ft_strnstr.c \
               execute/libft/ft_strrchr.c \
               execute/libft/ft_strtrim.c \
               execute/libft/ft_substr.c \
               execute/libft/ft_tolower.c \
               execute/libft/ft_toupper.c

BUILTIN_SRCS = execute/builtin/the.c \
               execute/builtin/echo.c \
               execute/builtin/pwd_env.c \
               execute/builtin/cd.c \
               execute/builtin/export.c \
               execute/builtin/export2.c \
               execute/builtin/unset.c \
               execute/builtin/exit.c

PARSER_SRCS  = parser/core/parser.c \
               parser/core/parser_utils.c \
               parser/core/parser_redirect.c \
               parser/lexer/lexer.c \
               parser/lexer/lexer_utils.c \
               parser/lexer/quote.c \
               parser/lexer/quote_utils.c \
               parser/lexer/special.c \
               parser/expander/expander.c \
               parser/expander/expander_utils.c

EXEC_SRCS    = execute/core/main.c \
               execute/core/exec.c \
               execute/core/exec2.c \
               execute/core/exec3.c \
               execute/core/heredoc.c \
               execute/utils/path.c \
               execute/utils/path_utils.c \
               execute/utils/utils.c \
               execute/utils/signal.c \
               execute/utils/free.c

ALL_SRCS     = $(LIBFT_SRCS) $(EXEC_SRCS) $(BUILTIN_SRCS) $(PARSER_SRCS)
ALL_OBJS     = $(ALL_SRCS:.c=.o)

INCLUDES     = -I./execute/includes -I./execute -I./execute/libft -I./execute/builtin -I./parser/includes $(READLINE_INC)

all: $(NAME)

$(NAME): $(ALL_OBJS)
	$(CC) $(CFLAGS) $(ALL_OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(ALL_OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
