NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

READLINE_DIR = $(shell brew --prefix readline)
READLINE_INC = -I$(READLINE_DIR)/include
LDFLAGS      = -L$(READLINE_DIR)/lib -lreadline

LIBFT_PATH  = ./execute/libft
LIBFT       = $(LIBFT_PATH)/libft.a

BUILTIN_PATH = ./execute/builtin
BUILTIN_LIB  = $(BUILTIN_PATH)/builtin.a

PARSER_PATH = ./parser
PARSER_LIB  = $(PARSER_PATH)/parser.a

EXEC_SRCS   = execute/main.c execute/exec.c execute/exec2.c execute/exec3.c execute/path.c execute/path_utils.c execute/heredoc.c execute/utils.c execute/signal.c execute/free.c
EXEC_OBJS   = $(EXEC_SRCS:.c=.o)

INCLUDES    = -I./execute -I./execute/includes -I$(LIBFT_PATH) -I$(BUILTIN_PATH) -I./parser $(READLINE_INC)

all: $(NAME)

$(NAME): $(LIBFT) $(BUILTIN_LIB) $(PARSER_LIB) $(EXEC_OBJS)
	$(CC) $(CFLAGS) $(EXEC_OBJS) $(PARSER_LIB) $(BUILTIN_LIB) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(BUILTIN_LIB):
	@make -C $(BUILTIN_PATH)

$(PARSER_LIB):
	@make -C $(PARSER_PATH)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(EXEC_OBJS)
	@make -C $(LIBFT_PATH) clean
	@make -C $(BUILTIN_PATH) clean
	@make -C $(PARSER_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@make -C $(BUILTIN_PATH) fclean
	@make -C $(PARSER_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
