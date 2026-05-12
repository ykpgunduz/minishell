/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 12:23:59 by zkarali           #+#    #+#             */
/*   Updated: 2026/05/12 12:24:00 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*for_expander_part(char *left, char *mid, char *right)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(left, mid);
	free(left);
	free(mid);
	res = ft_strjoin(tmp, right);
	free(tmp);
	free(right);
	return (res);
}

static char	*for_find(char *find, t_list *envp, t_ms *data, int *i)
{
	char	*tmp;
	char	*val;

	if (find[1] == '?')
	{
		*i = 2;
		return (ft_itoa(data->exit_num));
	}
	*i = 1;
	while (find[*i] && (ft_isalnum(find[*i]) || find[*i] == '_'))
		(*i)++;
	tmp = ft_substr(find, 1, *i - 1);
	val = for_env_value(envp, tmp);
	free(tmp);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

static int	check_exp_free(char **str, char *s, int i)
{
	if (i == 1 && (!str[0] || !str[1]))
	{
		free(str[0]);
		free(str[1]);
		free(s);
		return (1);
	}
	else if (i == 2 && !str[2])
	{
		free(str[0]);
		free(str[1]);
		free(s);
		return (1);
	}
	return (0);
}

char	*for_expander(char *s, t_list *envp, t_ms *data)
{
	int		i;
	char	*find;
	char	*str[3];

	while (1)
	{
		find = ft_strchr(s, '$');
		if (!find || !find[1] || ft_isspace(find[1])
			|| find[1] == '"' || find[1] == '\'')
			break ;
		str[0] = ft_substr(s, 0, find - s);
		str[1] = for_find(find, envp, data, &i);
		if (check_exp_free(str, s, 1))
			return (NULL);
		str[2] = ft_strdup(find + i);
		if (check_exp_free(str, s, 2))
			return (NULL);
		free(s);
		s = for_expander_part(str[0], str[1], str[2]);
		if (!s)
			return (NULL);
	}
	return (s);
}
