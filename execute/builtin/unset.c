/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:07:30 by zkarali           #+#    #+#             */
/*   Updated: 2026/03/26 09:07:31 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	del_node(t_list *node)
{
	t_env	*cont;

	cont = (t_env *)node->content;
	free(cont->key);
	free(cont->value);
	free(cont);
	free(node);
}

static void	for_remove(t_list *tmp, t_cmd *cmd, t_list **envp, int i)
{
	t_list	*node;
	t_env	*cont;

	node = NULL;
	while (tmp)
	{
		cont = (t_env *)tmp->content;
		if (ft_strcmp(cont->key, cmd->args[i]) == 0)
		{
			if (node == NULL) //ilk node
				*envp = tmp->next;
			else
				node->next = tmp->next;
			del_node(tmp);
			break ;
		}
		node = tmp;
		tmp = tmp->next;
	}
}

void	for_unset(t_cmd *cmd, t_list **envp)
{
	int		i;
	t_list	*tmp;

	i = 1;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '=')) //exit status 1, sinyallerle olan
		{
			write(2, "not a valid identifier\n", 23);
			i++;
			continue ;
		}
		tmp = *envp;
		for_remove(tmp, cmd, envp, i);
		i++;
	}
}
