#ifndef PARSER_H
# define PARSER_H

# include "../execute/mini.h"

typedef struct s_token
{
	char	*value;
	int		type;
}	t_token;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef struct s_lex_state
{
	int		pos;
	int		in_quote;
	char	quote_char;
	int		token_count;
	char	*input;
}	t_lex_state;

typedef struct s_expand_ctx
{
	char	*str;
	t_list	*envp;
	int		last_exit_code;
	char	name[256];
	char	*left;
	char	*mid;
	char	*value;
	char	*result;
}	t_expand_ctx;

t_list	*parse_input(char *input);
t_list	*parse_input_with_env(char *input, t_list *envp);
t_list	*parse_input_with_exit(char *input, t_list *envp, int exit_code);

char	**tokenize(char *input);
void	free_tokens(char **tokens);

int		is_quote(char c);
int		is_quote_closed(char *token);
void	skip_spaces(t_lex_state *state);
void	advance_quote_state(t_lex_state *state);
int		is_redirect(char *token);
int		is_pipe(char *token);
int		validate_syntax(char **tokens);

char	*process_quotes(char *token);
char	*process_quotes_with_env(char *token, t_list *envp, int exit_code);
char	*expand_variables(char *token, t_list *envp);
char	*expand_variables_with_exit(char *token, t_list *envp, int exit_code);

t_cmd	*create_cmd(void);
int		add_command_arg(t_cmd *cmd, char *arg, int *count);

int		dispatch_redirect(t_cmd *cmd, char **tokens, int *i);
int		handle_input_redirect(t_cmd *cmd, char **tokens, int *i);
int		handle_output_redirect(t_cmd *cmd, char **tokens, int *i);
int		handle_append(t_cmd *cmd, char **tokens, int *i);
int		handle_heredoc(t_cmd *cmd, char **tokens, int *i);

int		ft_isspace(char c);
int		is_escaped(char *input, int pos);
void	init_lex_state(t_lex_state *state, char *input);

char	*get_env_value(char *key, t_list *envp);
int		extract_var_name(char *start, char *name);
char	*expand_part(char *left, char *mid, char *right);
char	*expand_exit_status(char *str, int last_exit_code);

int		count_real_len(char *token);
int		needs_expansion(char *token);
char	*remove_quotes(char *token);

#endif
