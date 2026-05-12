/* ************************************************************************** */
/*                                                                            */
/*                                                           :::      ::::::: */
/*   quote.c                                               :+:      :+:    :+ */
/*                                                       +:+ +:+         +:+  */
/*   By: yagunduz <yagunduz@student.42istanbul.com.tr> +#+  +:+       +#+     */
/*                                                   +#+#+#+#+#+   +#+        */
/*   Created: 2026/03/14 09:25:19 by yagunduz             #+#    #+#          */
/*   Updated: 2026/04/23 12:48:48 by yagunduz            ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	handle_quote_removal(char *token, char *result)
{
	int	i;
	int	j;
	int	sing;
	int	doub;

	i = 0;
	j = 0;
	sing = 0;
	doub = 0;
	while (token[i])
	{
		if (token[i] == '\'' && !doub)
			sing = !sing;
		else if (token[i] == '"' && !sing)
			doub = !doub;
		else if (token[i] == '\\' && !sing && !doub && token[i + 1])
			result[j++] = token[++i];
		else
			result[j++] = token[i];
		i++;
	}
	result[j] = '\0';
}

char	*remove_quotes(char *token)
{
	char	*result;
	int		len;

	len = 0;
	count_real_len(token, &len);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	handle_quote_removal(token, result);
	return (result);
}

char	*process_quotes(char *token)
{
	return (process_quotes_with_env(token, NULL));
}

char	*process_quotes_with_env(char *token, t_ms *data)
{
	char	*removed;
	char	*expanded;

	if (!token)
		return (NULL);
	if (!is_quote_closed(token))
	{
		ft_putendl_fd("minishell: unclosed quote", 2);
		return (NULL);
	}
	if (needs_expansion(token))
	{
		expanded = for_expander(ft_strdup(token), *(data->envp), data);
		removed = remove_quotes(expanded);
		free(expanded);
		return (removed);
	}
	return (remove_quotes(token));
}
