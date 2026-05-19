/* ************************************************************************** */
/*                                                                            */
/*                                                           :::      ::::::: */
/*   lexer.c                                               :+:      :+:    :+ */
/*                                                       +:+ +:+         +:+  */
/*   By: yagunduz <yagunduz@student.42istanbul.com.tr> +#+  +:+       +#+     */
/*                                                   +#+#+#+#+#+   +#+        */
/*   Created: 2026/03/14 09:25:19 by yagunduz             #+#    #+#          */
/*   Updated: 2026/04/23 12:48:48 by yagunduz            ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	for_check_loop(t_lex_state *st, int start)
{
	while (st->input[st->pos])
	{
		advance_quote_state(st);
		if (!st->in_quote)
		{
			if (ft_isspace(st->input[st->pos]))
				break ;
			if (st->pos == start && is_redirect_char(st->input[st->pos]))
			{
				st->pos++;
				if (st->input[st->pos] == st->input[st->pos - 1]
					&& st->input[st->pos] != '|')
					st->pos++;
				break ;
			}
			if (st->pos > start && is_redirect_char(st->input[st->pos]))
				break ;
		}
		st->pos++;
	}
}

static int	count_tokens(char *input)
{
	t_lex_state	state;
	int			start;

	init_lex_state(&state, input);
	while (state.input[state.pos])
	{
		skip_spaces(&state);
		if (state.input[state.pos])
		{
			start = state.pos;
			state.token_count++;
		}
		state.in_quote = 0;
		state.quote_char = '\0';
		for_check_loop(&state, start);
	}
	return (state.token_count);
}

static char	*extract_token(t_lex_state *st)
{
	int		start;
	int		len;
	char	*token;

	skip_spaces(st);
	start = st->pos;
	st->in_quote = 0;
	st->quote_char = '\0';
	for_check_loop(st, start);
	len = st->pos - start;
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, st->input + start, len + 1);
	return (token);
}

static int	fill_tokens(char **tokens, t_lex_state *st)
{
	int	j;

	j = 0;
	while (j < st->token_count)
	{
		tokens[j] = extract_token(st);
		if (!tokens[j])
		{
			free_tokens(tokens);
			return (0);
		}
		if (!is_quote_closed(tokens[j]))
		{
			for_err(NULL, NULL, "unclosed quote");
			free_tokens(tokens);
			return (0);
		}
		j++;
	}
	tokens[j] = NULL;
	return (1);
}

char	**tokenize(char *input)
{
	char		**tokens;
	t_lex_state	st;

	if (!input || !*input)
		return (NULL);
	init_lex_state(&st, input);
	st.token_count = count_tokens(input);
	if (st.token_count == 0)
		return (NULL);
	tokens = malloc(sizeof(char *) * (st.token_count + 1));
	if (!tokens)
		return (NULL);
	ft_memset(tokens, 0, sizeof(char *) * (st.token_count + 1));
	if (!fill_tokens(tokens, &st))
		return (NULL);
	return (tokens);
}
