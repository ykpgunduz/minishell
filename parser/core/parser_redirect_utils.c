/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 12:23:46 by zkarali           #+#    #+#             */
/*   Updated: 2026/05/12 12:23:47 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_input_redirect(t_cmd *cmd, char **tokens, int *i, t_ms *data)
{
	int	fd;

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
	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		data->exit_num = 1;
		return (-1);
	}
	close(fd);
	(*i) += 2;
	return (1);
}
