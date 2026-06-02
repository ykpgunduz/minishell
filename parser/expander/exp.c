/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:57:11 by zkarali           #+#    #+#             */
/*   Updated: 2026/06/02 11:42:07 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*double_quote(char *t, int *j, t_ms *data)
{
	char	*e;
	char	*tmp;
	char	*res;
	char	chr[2];

	res = NULL;
	chr[1] = '\0';
	while (t[*j] && t[*j] != '"')
	{
		if (t[*j] == '$')
		{
			e = dq_dollar(t, j, data);
			tmp = ft_strjoin(res, e);
			free(res);
			free(e);
			res = tmp;
			continue ;
		}
		chr[0] = t[*j];
		tmp = ft_strjoin(res, chr);
		free(res);
		res = tmp;
		(*j)++;
	}
	return (res);
}

static char	*handle_dollar(char *t, int *i, t_ms *data)
{
	int		n;
	char	*e;

	n = 0;
	if (!t[*i + 1] || ft_isspace(t[*i + 1]) || t[*i + 1] == '/')
		return ((*i)++, ft_strdup("$"));
	e = find_part(t + *i, *(data->envp), data, &n);
	*i += n;
	return (e);
}

static char	*handle_quote(char *t, int *i, t_ms *data)
{
	if (t[*i] == '\'')
	{
		(*i)++;
		return (single_quote(t, i));
	}
	(*i)++;
	return (double_quote(t, i, data));
}

static char	*reg(char *t, int *i)
{
	int		j;
	char	*res;

	j = *i;
	res = NULL;
	while (t[j])
	{
		if (t[j] == '\\' && t[j + 1])
		{
			res = reg_backslash(t, &j, res);
			continue ;
		}
		if (t[j] == '\'' || t[j] == '"' || t[j] == '$')
			break ;
		j++;
	}
	if (!res)
		res = ft_substr(t, *i, j - *i);
	*i = j - 1;
	return (res);
}

char	*expanderish(char *t, t_ms *data)
{
	int		i;
	char	*r;

	i = 0;
	r = NULL;
	while (t[i])
	{
		if (t[i] == '\'' || t[i] == '"')
			r = exp_join(r, handle_quote(t, &i, data));
		else if (t[i] == '$')
		{
			r = exp_join(r, handle_dollar(t, &i, data));
			continue ;
		}
		else
			r = exp_join(r, reg(t, &i));
		i++;
	}
	return (r);
}
