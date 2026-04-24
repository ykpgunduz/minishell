NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

READLINE_DIR = $(shell brew --prefix readline)
READLINE_INC = -I$(READLINE_DIR)/include
LDFLAGS      = -L$(READLINE_DIR)/lib -lreadline

LIBFT_SRCS   = executor/libft/ft_atoi.c \
               executor/libft/ft_bzero.c \
               executor/libft/ft_calloc.c \
               executor/libft/ft_isalnum.c \
               executor/libft/ft_isalpha.c \
               executor/libft/ft_isascii.c \
               executor/libft/ft_isdigit.c \
               executor/libft/ft_isprint.c \
               executor/libft/ft_itoa.c \
               executor/libft/ft_lstadd_back.c \
               executor/libft/ft_lstadd_front.c \
               executor/libft/ft_lstclear.c \
               executor/libft/ft_lstdelone.c \
               executor/libft/ft_lstiter.c \
               executor/libft/ft_lstlast.c \
               executor/libft/ft_lstmap.c \
               executor/libft/ft_lstnew.c \
               executor/libft/ft_lstsize.c \
               executor/libft/ft_memchr.c \
               executor/libft/ft_memcmp.c \
               executor/libft/ft_memcpy.c \
               executor/libft/ft_memmove.c \
               executor/libft/ft_memset.c \
               executor/libft/ft_putchar_fd.c \
               executor/libft/ft_putendl_fd.c \
               executor/libft/ft_putnbr_fd.c \
               executor/libft/ft_putstr_fd.c \
               executor/libft/ft_split.c \
               executor/libft/ft_strchr.c \
               executor/libft/ft_strdup.c \
               executor/libft/ft_striteri.c \
               executor/libft/ft_strjoin.c \
               executor/libft/ft_strlcat.c \
               executor/libft/ft_strlcpy.c \
               executor/libft/ft_strlen.c \
               executor/libft/ft_strmapi.c \
               executor/libft/ft_strncmp.c \
               executor/libft/ft_strnstr.c \
               executor/libft/ft_strrchr.c \
               executor/libft/ft_strtrim.c \
               executor/libft/ft_substr.c \
               executor/libft/ft_tolower.c \
               executor/libft/ft_toupper.c

BUILTIN_SRCS = executor/builtin/the.c \
               executor/builtin/echo.c \
               executor/builtin/pwd_env.c \
               executor/builtin/cd.c \
               executor/builtin/export.c \
               executor/builtin/export2.c \
               executor/builtin/unset.c \
               executor/builtin/exit.c

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

EXEC_SRCS    = executor/core/main.c \
               executor/core/exec.c \
               executor/core/exec2.c \
               executor/core/exec3.c \
               executor/core/heredoc.c \
               executor/utils/path.c \
               executor/utils/path_utils.c \
               executor/utils/utils.c \
               executor/utils/signal.c \
               executor/utils/free.c

ALL_SRCS     = $(LIBFT_SRCS) $(EXEC_SRCS) $(BUILTIN_SRCS) $(PARSER_SRCS)
ALL_OBJS     = $(ALL_SRCS:.c=.o)

INCLUDES     = -I./executor/includes -I./executor -I./executor/libft -I./executor/builtin -I./parser/includes $(READLINE_INC)

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
