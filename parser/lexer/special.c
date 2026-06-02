/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 09:25:19 by yagunduz          #+#    #+#             */
/*   Updated: 2026/06/02 11:11:32 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redirect(char **token, int i)
{
	if (!token)
		return (0);
	if (ft_strncmp(token[i], "<", 1) == 0 && ft_strlen(token[i]) == 1)
		return (1);
	if (ft_strncmp(token[i], "<<", 2) == 0 && ft_strlen(token[i]) == 2)
		return (1);
	if (ft_strncmp(token[i], ">", 1) == 0 && ft_strlen(token[i]) == 1)
		return (1);
	if (ft_strncmp(token[i], ">>", 2) == 0 && ft_strlen(token[i]) == 2)
		return (1);
	return (0);
}

int	is_pipe(char *token)
{
	if (!token)
		return (0);
	if (ft_strncmp(token, "|", 1) == 0 && ft_strlen(token) == 1)
		return (1);
	return (0);
}

static int	check_consecutive_pipes(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_pipe(tokens[i]))
		{
			if (!tokens[i + 1] || is_pipe(tokens[i + 1]))
			{
				for_err(NULL, NULL, "syntax error near unexpected token `|'");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

static int	check_redirect_args(char **tokens, t_ms *data)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_redirect(tokens, i))
		{
			if (!tokens[i + 1])
			{
				ft_putendl_fd("minishell: syntax error near\
 unexpected token `newline'", 2);
				data->exit_num = 2;
				return (0);
			}
			if (is_pipe(tokens[i + 1]) || is_redirect(tokens, i + 1))
			{
				ft_putstr_fd("minishell: syntax error near\
 unexpected token `", 2);
				ft_putstr_fd(tokens[i + 1], 2);
				ft_putendl_fd("\'", 2);
				data->exit_num = 2;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	validate_syntax(char **tokens, t_ms *data)
{
	if (!tokens || !tokens[0])
		return (1);
	if (is_pipe(tokens[0]))
	{
		for_err(NULL, NULL, "syntax error near unexpected token `|'");
		return (0);
	}
	if (!check_consecutive_pipes(tokens))
	{
		data->exit_num = 2;
		return (0);
	}
	if (!check_redirect_args(tokens, data))
		return (0);
	return (1);
}
