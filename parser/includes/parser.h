/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 09:25:19 by yagunduz          #+#    #+#             */
/*   Updated: 2026/06/02 12:48:23 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../types_etc.h"

typedef struct s_token
{
	char	*value;
	int		type;
}			t_token;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}			t_token_type;

typedef struct s_lex_state
{
	int		pos;
	int		in_quote;
	char	quote_char;
	int		token_count;
	char	*input;
}			t_lex_state;

typedef struct s_expand_ctx
{
	char	*str;
	t_ms	*data;
	char	name[256];
	char	*left;
	char	*mid;
	char	*value;
	char	*result;
}			t_expand_ctx;

t_list		*parse_input(char *input);
t_list		*parse_input_with_env(char *input, t_list *envp);
t_list		*parse_input_with_exit(char *input, t_ms *data);

char		**tokenize(char *input);
void		free_tokens(char **tokens);

int			is_quote(char c);
int			is_quote_closed(char *token);
void		skip_spaces(t_lex_state *state);
void		advance_quote_state(t_lex_state *state);
int			is_redirect(char **token, int i);
int			is_pipe(char *token);
int			validate_syntax(char **tokens, t_ms *data);

char		*process_quotes(char *token);
char		*process_quotes_with_env(char *token, t_ms *data);

t_cmd		*create_cmd(void);
int			add_command_arg(t_cmd *cmd, char *arg, int *count, t_ms *data);

int			dispatch_redirect(t_cmd *cmd, char **tokens, int *i, t_ms *data);
int			handle_input_redirect(t_cmd *cmd, char **tokens, int *i,
				t_ms *data);
int			handle_output_redirect(t_cmd *cmd, char **tokens, int *i,
				t_ms *data);
int			handle_append(t_cmd *cmd, char **tokens, int *i, t_ms *data);
int			handle_heredoc(t_cmd *cmd, char **tokens, int *i, t_ms *data);

int			ft_isspace(char c);

void		init_lex_state(t_lex_state *state, char *input);
int			is_redirect_char(char c);

void		count_real_len(char *token, int *len);
int			needs_expansion(char *token);
char		*remove_quotes(char *token);
char		*find_part(char *find, t_list *envp, t_ms *data, int *i);
char		*single_quote(char *t, int *i);
char		*reg_backslash(char *t, int *j, char *res);
char		*dq_dollar(char *t, int *j, t_ms *data);
char		*exp_join(char *r, char *part);
char		*finds_part(char *tmp, char *val);

#endif