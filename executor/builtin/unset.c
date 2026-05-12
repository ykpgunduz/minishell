/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   unset.c                                              :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/04/09 09:44:36 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/15 13:02:48 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	del_node(t_list *node)
{
	t_env	*cont;

	cont = (t_env *)node->content;
	free(cont->key);
	if (cont->value)
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
			if (node == NULL)
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

static int	unset_check(char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i] && c[i] != '=')
	{
		if (!ft_isalnum(c[i]) && c[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	for_unset(t_cmd *cmd, t_list **envp, t_ms *data)
{
	int		i;
	t_list	*tmp;

	i = 1;
	data->exit_num = 0;
	while (cmd->args[i])
	{
		if (!unset_check(cmd->args[i]))
		{
			for_err("unset", cmd->args[i], "not a valid identifier");
			data->exit_num = 1;
		}
		else
		{
			tmp = *envp;
			for_remove(tmp, cmd, envp, i);
		}
		i++;
	}
}
