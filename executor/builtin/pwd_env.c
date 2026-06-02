/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 09:35:08 by zkarali           #+#    #+#             */
/*   Updated: 2026/06/02 09:03:18 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	for_pwd(t_ms *data)
{
	char	*b;

	b = getcwd(NULL, 0);
	if (b != NULL)
	{
		ft_putendl_fd(b, 1);
		free(b);
		data->exit_num = 0;
	}
	else
	{
		b = for_env_value(*(data->envp), "PWD");
		if (b)
		{
			ft_putendl_fd(b, 1);
			data->exit_num = 0;
		}
		else
		{
			for_err("pwd", NULL, strerror(errno));
			data->exit_num = 1;
		}
	}
}

void	for_env(t_list **envp, t_ms *data, t_cmd *cmd)
{
	t_env	*cont;
	t_list	*tmp;

	tmp = *envp;
	if (cmd->args[1] != NULL)
	{
		data->exit_num = 127;
		for_err("env", cmd->args[1], "No such file or directory");
		return ;
	}
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
	data->exit_num = 0;
}
