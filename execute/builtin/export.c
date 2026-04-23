/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:07:12 by zkarali           #+#    #+#             */
/*   Updated: 2026/03/26 09:07:13 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	**for_loop(t_list *tmp, char **t_tmp)
{
	t_env	*cont;
	char	*s1;
	char	*s2;
	int		i;

	i = 0;
	while (tmp)
	{
		cont = (t_env *)tmp->content;
		if (cont->value == NULL)
			t_tmp[i] = ft_strdup(cont->key);
		else
		{
			s1 = ft_strjoin(cont->key, "=\"");
			s2 = ft_strjoin(s1, cont->value);
			t_tmp[i] = ft_strjoin(s2, "\"");
			free(s1);
			free(s2);
		}
		i++;
		tmp = tmp->next;
	}
	t_tmp[i] = NULL;
	sort(t_tmp, i);
	return (t_tmp);
}

static void	if_null(t_list **envp)
{
	t_list	*tmp;
	char	**t_tmp;
	int		i;

	tmp = *envp;
	t_tmp = malloc(sizeof(char *) * (ft_lstsize(*envp) + 1));
	if (!t_tmp)
		return ;
	t_tmp = for_loop(tmp, t_tmp);
	i = 0;
	while (t_tmp[i])
	{
		printf("declare -x %s\n", t_tmp[i]);
		i++;
	}
	free_s(t_tmp, 2);
}

static void	extra(t_list **envp, char *s, char *key, char *val)
{
	if (for_env_value(*envp, key))
	{
		if (s)
			env_node(envp, key, val);
	}
	else
		for_new_node(envp, key, val);
	free(key);
	if (val)
		free(val);
}

static void	for_s(char *c, t_list **envp, char *s)
{
	char	*key;
	char	*val;

	if (s)
	{
		key = ft_substr(c, 0, s - c);
		val = ft_strdup(s + 1);
	}
	else
	{
		key = ft_strdup(c);
		val = NULL;
	}
	extra(envp, s, key, val);
}

void	for_export(t_cmd *cmd, t_list **envp)
{
	char	*s;
	int		i;

	if (cmd->args[1] == NULL)
	{
		if_null(envp);
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		if (!check(cmd->args[i]))
		{
			i++;
			continue ;
		}
		s = ft_strchr(cmd->args[i], '=');
		for_s(cmd->args[i], envp, s);
		i++;
	}
}
