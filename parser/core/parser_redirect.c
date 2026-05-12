/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 09:25:19 by yagunduz          #+#    #+#             */
/*   Updated: 2026/05/12 12:06:21 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	for_outfiles_file(t_cmd *cmd)
{
	int	fd;

	fd = 0;
	if (cmd->outfile)
	{
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd != -1)
			close(fd);
		free(cmd->outfile);
	}
	return (fd);
}

int	handle_output_redirect(t_cmd *cmd, char **tokens, int *i, t_ms *data)
{
	int	fd;

	if (!tokens[*i + 1])
	{
		ft_putendl_fd("syntax error: expected filename after '>'", 2);
		return (-1);
	}
	fd = for_outfiles_file(cmd);
	cmd->type_out = REDIR_OUT;
	cmd->outfile = process_quotes_with_env(tokens[*i + 1], data);
	if (!cmd->outfile)
		return (-1);
	fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		data->exit_num = 1;
		return (-1);
	}
	close(fd);
	(*i) += 2;
	return (1);
}

int	handle_append(t_cmd *cmd, char **tokens, int *i, t_ms *data)
{
	int	fd;

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
	fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		data->exit_num = 1;
		return (-1);
	}
	close(fd);
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
		if (cmd->delimiter)
			free(cmd->delimiter);
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
