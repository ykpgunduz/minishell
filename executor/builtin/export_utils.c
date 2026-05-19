/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   export2.c                                            :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/04/04 23:24:54 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/18 14:25:12 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort(char **s, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(s[i], s[j]) > 0)
				swap(&s[i], &s[j]);
			j++;
		}
		i++;
	}
}

void	for_new_node(t_list **envp, char *key, char *val)
{
	t_env	*env;
	t_list	*node;

	env = malloc(sizeof(t_env));
	if (!env)
		return ;
	env->key = ft_strdup(key);
	if (val)
		env->value = ft_strdup(val);
	else
		env->value = NULL;
	node = ft_lstnew(env);
	ft_lstadd_back(envp, node);
}

int	check(char *c, t_ms *data)
{
	int	i;

	i = 0;
	if (c[0] == '-' && c[1] != '\0')
	{
		for_err("export", c, "invalid option");
		data->exit_num = 2;
		return (0);
	}
	if (!c || ft_isdigit(c[0]) || c[0] == '=')
	{
		for_err("export", c, "not a valid identifier");
		data->exit_num = 1;
		return (0);
	}
	while (c[i] && c[i] != '=')
	{
		if (!ft_isalnum(c[i]) && c[i] != '_')
		{
			for_err("export", c, "not a valid identifier");
			data->exit_num = 1;
			return (0);
		}
		i++;
	}
	return (1);
}
