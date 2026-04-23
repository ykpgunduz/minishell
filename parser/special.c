/* ************************************************************************** */
/*                                                                            */
/*                                                           :::      ::::::: */
/*   special.c                                             :+:      :+:    :+ */
/*                                                       +:+ +:+         +:+  */
/*   By: yagunduz <yagunduz@student.42istanbul.com.tr> +#+  +:+       +#+     */
/*                                                   +#+#+#+#+#+   +#+        */
/*   Created: 2026/04/23 12:48:46 by yagunduz             #+#    #+#          */
/*   Updated: 2026/04/23 12:48:48 by yagunduz            ###   ########.tr    */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redirect(char *token)
{
	if (!token)
		return (0);
	if (ft_strncmp(token, "<", 1) == 0 && ft_strlen(token) == 1)
		return (1);
	if (ft_strncmp(token, "<<", 2) == 0 && ft_strlen(token) == 2)
		return (1);
	if (ft_strncmp(token, ">", 1) == 0 && ft_strlen(token) == 1)
		return (1);
	if (ft_strncmp(token, ">>", 2) == 0 && ft_strlen(token) == 2)
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
				ft_putendl_fd("syntax error near unexpected token `|'", 2);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

static int	check_redirect_args(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_redirect(tokens[i]))
		{
			if (!tokens[i + 1])
			{
				ft_putstr_fd("syntax error near unexpected token `", 2);
				ft_putstr_fd(tokens[i], 2);
				ft_putendl_fd("'", 2);
				return (0);
			}
			if (is_pipe(tokens[i + 1]) || is_redirect(tokens[i + 1]))
			{
				ft_putstr_fd("syntax error near unexpected token `", 2);
				ft_putstr_fd(tokens[i + 1], 2);
				ft_putendl_fd("'", 2);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	validate_syntax(char **tokens)
{
	if (!tokens || !tokens[0])
		return (1);
	if (is_pipe(tokens[0]))
	{
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
		return (0);
	}
	if (!check_consecutive_pipes(tokens))
		return (0);
	if (!check_redirect_args(tokens))
		return (0);
	return (1);
}
