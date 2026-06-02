/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 09:17:50 by zkarali           #+#    #+#             */
/*   Updated: 2026/06/02 10:08:33 by zkarali          ###   ########.fr       */
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

void	if_null(t_list **envp)
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
	free_s(t_tmp);
}
