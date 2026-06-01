/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:57:06 by zkarali           #+#    #+#             */
/*   Updated: 2026/06/01 14:57:07 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*dq_dollar(char *t, int *j, t_ms *data)
{
	int		n;
	char	*e;

	n = 0;
	if (t[*j + 1] == '"' || t[*j + 1] == ' ' || t[*j + 1] == '/')
		return ((*j)++, ft_strdup("$"));
	e = find_part(t + *j, *(data->envp), data, &n);
	*j += n;
	return (e);
}

char	*reg_backslash(char *t, int *j, char *res)
{
	char	chr[2];
	char	*tmp;

	chr[1] = '\0';
	chr[0] = t[*j + 1];
	*j += 2;
	tmp = ft_strjoin(res, chr);
	free(res);
	return (tmp);
}

char	*exp_join(char *r, char *part)
{
	char	*tmp;

	tmp = ft_strjoin(r, part);
	free(r);
	free(part);
	return (tmp);
}

char	*single_quote(char *t, int *i)
{
	int		j;
	char	*r;

	j = *i;
	while (t[j] && t[j] != '\'')
		j++;
	r = ft_substr(t, *i, j - *i);
	*i = j;
	return (r);
}
