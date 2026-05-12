/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 09:25:19 by yagunduz          #+#    #+#             */
/*   Updated: 2026/05/12 11:18:59 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if ((c == '"' || c == '\'') && !state->in_quote)
	{
		state->in_quote = 1;
		state->quote_char = c;
	}
	else if (c == state->quote_char && state->in_quote)
		state->in_quote = 0;
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	init_lex_state(t_lex_state *state, char *input)
{
	state->pos = 0;
	state->in_quote = 0;
	state->quote_char = 0;
	state->token_count = 0;
	state->input = input;
}
