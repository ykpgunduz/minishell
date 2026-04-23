#include "parser.h"

static void	handle_quote_removal(char *token, char *result)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '\\' && token[i + 1]
			&& (token[i + 1] == '"' || token[i + 1] == '\''))
		{
			result[j++] = token[i + 1];
			i += 2;
		}
		else if (token[i] == '"' || token[i] == '\'')
			i++;
		else
			result[j++] = token[i++];
	}
	result[j] = '\0';
}

char	*remove_quotes(char *token)
{
	char	*result;

	result = malloc(count_real_len(token) + 1);
	if (!result)
		return (NULL);
	handle_quote_removal(token, result);
	return (result);
}

char	*process_quotes(char *token)
{
	return (process_quotes_with_env(token, NULL, 0));
}

char	*process_quotes_with_env(char *token, t_list *envp, int last_exit_code)
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
	removed = remove_quotes(token);
	if (!removed)
		return (NULL);
	if (needs_expansion(token))
	{
		expanded = expand_variables_with_exit(removed, envp, last_exit_code);
		free(removed);
		return (expanded);
	}
	return (removed);
}
