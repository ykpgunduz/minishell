NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

# Readline kütüphanesini buraya ekliyoruz
# Okuldaysan bazen -L/usr/local/lib eklemek gerekebilir
READLINE_INC = -I/usr/local/include
LDFLAGS      = -lreadline 

LIBFT_PATH  = ./libft
LIBFT       = $(LIBFT_PATH)/libft.a

BUILTIN_PATH = ./builtin
BUILTIN_LIB  = $(BUILTIN_PATH)/builtin.a

SRCS        = main.c exec.c exec2.c exec3.c path.c heredoc.c utils.c signal.c
OBJS        = $(SRCS:.c=.o)

INCLUDES    = -I./includes -I$(LIBFT_PATH) -I$(BUILTIN_PATH) $(READLINE_INC)

all: $(NAME)

$(NAME): $(LIBFT) $(BUILTIN_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(BUILTIN_LIB) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(BUILTIN_LIB):
	@make -C $(BUILTIN_PATH)

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_PATH) clean
	@make -C $(BUILTIN_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@make -C $(BUILTIN_PATH) fclean

re: fclean all

.PHONY: all clean fclean re