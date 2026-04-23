#include "parser.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	is_quote_closed(char *token)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (token[i])
	{
		if (token[i] == '\\' && token[i + 1])
		{
			i += 2;
			continue ;
		}
		if (token[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (token[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (!in_single && !in_double);
}

int	count_real_len(char *token)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (token[i])
	{
		if (token[i] == '\\' && token[i + 1]
			&& (token[i + 1] == '"' || token[i + 1] == '\''))
		{
			i += 2;
			len++;
		}
		else if (token[i] == '"' || token[i] == '\'')
			i++;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

int	needs_expansion(char *token)
{
	int	i;
	int	in_single;

	i = 0;
	in_single = 0;
	while (token[i])
	{
		if (token[i] == '\\' && token[i + 1])
		{
			i += 2;
			continue ;
		}
		if (token[i] == '\'' && !in_single)
			in_single = 1;
		else if (token[i] == '\'' && in_single)
			in_single = 0;
		else if (token[i] == '$' && !in_single)
			return (1);
		i++;
	}
	return (0);
}
