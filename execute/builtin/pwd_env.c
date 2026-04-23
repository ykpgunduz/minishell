/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:07:21 by zkarali           #+#    #+#             */
/*   Updated: 2026/03/26 09:07:22 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	for_pwd(void)
{
	char	*b;

	b = getcwd(NULL, 0);
	if (b != NULL)
	{
		write(1, b, ft_strlen(b));
		write(1, "\n", 1);
		free(b);
	}
	else
		perror("minishell: pwd");
}

void	for_env(t_list *envp)
{
	t_env	*cont;
	t_list	*tmp;

	tmp = envp;
	while (tmp)
	{
		cont = (t_env *)tmp->content;
		if (cont->value != NULL)
		{
			write(1, cont->key, ft_strlen(cont->key));
			write(1, "=", 1);
			write(1, cont->value, ft_strlen(cont->value));
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
}
