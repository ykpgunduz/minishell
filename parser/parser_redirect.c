/* ************************************************************************** */
/*                                                                            */
/*                                                           :::      ::::::: */
/*   parser_redirect.c                                     :+:      :+:    :+ */
/*                                                       +:+ +:+         +:+  */
/*   By: yagunduz <yagunduz@student.42istanbul.com.tr> +#+  +:+       +#+     */
/*                                                   +#+#+#+#+#+   +#+        */
/*   Created: 2026/03/14 09:25:19 by yagunduz             #+#    #+#          */
/*   Updated: 2026/04/23 12:48:48 by yagunduz            ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_input_redirect(t_cmd *cmd, char **tokens, int *i, t_ms *data)
{
	if (!tokens[*i + 1])
	{
		ft_putendl_fd("syntax error: expected filename after '<'", 2);
		return (-1);
	}
	cmd->type_in = REDIR_IN;
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = process_quotes_with_env(tokens[*i + 1], data);
	if (!cmd->infile)
		return (-1);
	(*i) += 2;
	return (1);
}

int	handle_output_redirect(t_cmd *cmd, char **tokens, int *i, t_ms *data)
{
	if (!tokens[*i + 1])
	{
		ft_putendl_fd("syntax error: expected filename after '>'", 2);
		return (-1);
	}
	cmd->type_out = REDIR_OUT;
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = process_quotes_with_env(tokens[*i + 1], data);
	if (!cmd->outfile)
		return (-1);
	(*i) += 2;
	return (1);
}

int	handle_append(t_cmd *cmd, char **tokens, int *i, t_ms *data)
{
	if (!tokens[*i + 1])
	{
		ft_putendl_fd("syntax error: expected filename after '>>'", 2);
		return (-1);
	}
	cmd->type_out = APPEND;
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = process_quotes_with_env(tokens[*i + 1], data);
	if (!cmd->outfile)
		return (-1);
	(*i) += 2;
	return (1);
}

static void	setup_heredoc_quote(t_cmd *cmd, char *delimiter, t_ms *data)
{
	int	has_quote;

	has_quote = is_quote(delimiter[0]) || ft_strchr(delimiter, '"')
		|| ft_strchr(delimiter, '\'');
	if (has_quote)
	{
		cmd->delimiter = process_quotes_with_env(delimiter, data);
		cmd->expand = 0;
	}
	else
	{
		cmd->delimiter = ft_strdup(delimiter);
		cmd->expand = 1;
	}
}

int	handle_heredoc(t_cmd *cmd, char **tokens, int *i, t_ms *data)
{
	if (!tokens[*i + 1])
	{
		ft_putendl_fd("syntax error: expected delimiter after '<<'", 2);
		return (-1);
	}
	cmd->type_in = HEREDOC;
	setup_heredoc_quote(cmd, tokens[*i + 1], data);
	if (!cmd->delimiter)
		return (-1);
	(*i) += 2;
	return (1);
}
