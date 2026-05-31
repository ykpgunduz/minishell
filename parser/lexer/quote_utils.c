/* ************************************************************************** */
/*                                                                            */
/*                                                           :::      ::::::: */
/*   quote_utils.c                                         :+:      :+:    :+ */
/*                                                       +:+ +:+         +:+  */
/*   By: yagunduz <yagunduz@student.42istanbul.com.tr> +#+  +:+       +#+     */
/*                                                   +#+#+#+#+#+   +#+        */
/*   Created: 2026/03/14 09:25:19 by yagunduz             #+#    #+#          */
/*   Updated: 2026/04/23 12:48:48 by yagunduz            ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

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

void	count_real_len(char *token, int *len)
{
	int	sing;
	int	doub;

	sing = 0;
	doub = 0;
	while (*token)
	{
		if (*token == '\'' && !doub)
			sing = !sing;
		else if (*token == '"' && !sing)
			doub = !doub;
		else if (*token == '\\' && !sing && !doub && *(token + 1))
		{
			(*len)++;
			token++;
		}
		else
			(*len)++;
		token++;
	}
}

int	needs_expansion(char *token)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (token[i])
	{
		if (token[i] == '\\' && !in_single && token[i + 1])
		{
			i += 2;
			continue ;
		}
		if (token[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (token[i] == '"' && !in_single)
			in_double = !in_double;
		else if (token[i] == '$' && !in_single)
			return (1);
		i++;
	}
	return (0);
}
