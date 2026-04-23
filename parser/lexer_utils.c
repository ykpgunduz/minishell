#include "parser.h"

void	skip_spaces(t_lex_state *state)
{
	while (state->input[state->pos] && ft_isspace(state->input[state->pos]))
		state->pos++;
}

void	advance_quote_state(t_lex_state *state)
{
	char	c;

	c = state->input[state->pos];
	if ((c == '"' || c == '\'') && !state->in_quote
		&& !is_escaped(state->input, state->pos))
	{
		state->in_quote = 1;
		state->quote_char = c;
	}
	else if (c == state->quote_char && state->in_quote
		&& !is_escaped(state->input, state->pos))
		state->in_quote = 0;
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	is_escaped(char *input, int pos)
{
	int	count;

	if (pos == 0)
		return (0);
	count = 0;
	pos--;
	while (pos >= 0 && input[pos] == '\\')
	{
		count++;
		pos--;
	}
	return (count % 2);
}

void	init_lex_state(t_lex_state *state, char *input)
{
	state->pos = 0;
	state->in_quote = 0;
	state->quote_char = 0;
	state->token_count = 0;
	state->input = input;
}
