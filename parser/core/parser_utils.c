/* ************************************************************************** */
/*                                                                            */
/*                                                           :::      ::::::: */
/*   parser_utils.c                                        :+:      :+:    :+ */
/*                                                       +:+ +:+         +:+  */
/*   By: yagunduz <yagunduz@student.42istanbul.com.tr> +#+  +:+       +#+     */
/*                                                   +#+#+#+#+#+   +#+        */
/*   Created: 2026/03/14 09:25:19 by yagunduz             #+#    #+#          */
/*   Updated: 2026/04/23 12:48:48 by yagunduz            ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

t_list	*parse_input(char *input)
{
	return (parse_input_with_exit(input, NULL));
}

t_list	*parse_input_with_env(char *input, t_list *envp)
{
	(void)envp;
	return (parse_input_with_exit(input, NULL));
}

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->args = malloc(sizeof(char *) * 512);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	ft_memset(cmd->args, 0, sizeof(char *) * 512);
	return (cmd);
}

int	add_command_arg(t_cmd *cmd, char *arg, int *count, t_ms *data)
{
	char	*processed;
	int		for_quotes;

	for_quotes = is_quote(arg[0]) || ft_strchr(arg, '"')
		|| ft_strchr(arg, '\'');
	processed = process_quotes_with_env(arg, data);
	if (!processed)
		return (-1);
	if (*processed == '\0' && !for_quotes)
	{
		free(processed);
		processed = NULL;
		return (1);
	}
	cmd->args[*count] = processed;
	(*count)++;
	cmd->args[*count] = NULL;
	if (*count >= 511)
	{
		for_err("error", NULL, "too many arguments");
		return (-1);
	}
	return (1);
}
