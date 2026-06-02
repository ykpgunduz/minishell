/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:25:48 by zkarali           #+#    #+#             */
/*   Updated: 2026/06/02 09:17:44 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*for_key(t_list *envp, char *s)
{
	t_list	*tmp;
	t_env	*cont;

	tmp = envp;
	while (tmp)
	{
		cont = (t_env *)tmp->content;
		if (ft_strcmp(cont->key, s) == 0)
			return (cont->key);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	extra(t_list **envp, char *key, char *val)
{
	if (for_key(*envp, key))
	{
		if (key)
			env_node(envp, key, val);
	}
	else
		for_new_node(envp, key, val);
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
	extra(envp, key, val);
	free(key);
	if (val)
		free(val);
}

void	for_export(t_cmd *cmd, t_list **envp, t_ms *data)
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
		if (!check(cmd->args[i], data))
		{
			i++;
			continue ;
		}
		s = ft_strchr(cmd->args[i], '=');
		for_s(cmd->args[i], envp, s);
		data->exit_num = 0;
		i++;
	}
}
